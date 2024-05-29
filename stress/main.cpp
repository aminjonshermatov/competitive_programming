#include <iostream>
#include <format>
#include <expected>

#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>

#include "config.hpp"

namespace bp = boost::process;

using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace std::chrono_literals;

using i32 = int32_t;

constexpr auto kExitSuccessCode = 0u;

std::expected<void, std::string> compile() {
  auto compileCommandGenerator = [](const std::filesystem::path& path) {
    return std::format("g++ --std=c++23 -O2 {} -DLOCAL -o {}"sv,
                       path.string(),
                       path.stem().string());
  };

  std::array cmds{
    compileCommandGenerator(path::cpp::kGen),
    compileCommandGenerator(path::cpp::kSlow),
    compileCommandGenerator(path::cpp::kFast),
  };

  constexpr std::size_t nCmds = cmds.size();
  std::array<std::future<std::string>, nCmds> stdErr;
  std::array<std::future<i32>, nCmds> exitCodes;

  std::vector<bp::child> ch;
  boost::asio::io_context ioc;
  for (std::size_t i{}; i < nCmds; ++i) {
    ch.emplace_back(cmds[i],
                    bp::std_in.close(),
                    bp::std_out > bp::null,
                    bp::std_err > stdErr[i],
                    bp::on_exit = exitCodes[i],
                    ioc);
  }
  ioc.run();

  for (std::size_t i{}; i < nCmds; ++i) {
    if (exitCodes[i].get() != kExitSuccessCode) {
      return std::unexpected(stdErr[i].get());
    }
  }
  return {};
}

std::expected<void, std::string> runTest() {
  boost::asio::io_context ioc;

  std::future<std::string> genStdOut, genStdErr;
  std::future<i32> genExitCode;
  bp::child gen(std::format("./{}"sv, path::cpp::kGen.stem().string()),
                bp::std_in.close(),
                bp::std_out > genStdOut,
                bp::std_err > genStdErr,
                bp::on_exit = genExitCode,
                ioc);

  ioc.run();
  if (auto&& exitCode = genExitCode.get(); exitCode != kExitSuccessCode) {
    return std::unexpected(std::format("generator: {}"sv, genStdErr.get()));
  }

  auto&& data = genStdOut.get();
  bp::async_pipe slowPipe(ioc), fastPipe(ioc);

  using namespace boost::asio::experimental::awaitable_operators;
  auto WriteToPipes = [&]() -> boost::asio::awaitable<void> {
    co_await (boost::asio::async_write(slowPipe, boost::asio::buffer(data),
                                       boost::asio::use_awaitable) &&
              boost::asio::async_write(fastPipe, boost::asio::buffer(data),
                                       boost::asio::use_awaitable));
  };
  boost::asio::co_spawn(ioc, WriteToPipes, boost::asio::detached);
  ioc.run();
  ioc.reset();

  std::future<std::string> slowStdErr, slowStdOut;
  std::future<i32> slowExitCode;
  std::vector<bp::child> ch;
  ch.emplace_back(std::format("./{}"sv, path::cpp::kSlow.stem().string()),
                  bp::std_in < slowPipe,
                  bp::std_out > slowStdOut,
                  bp::std_err > slowStdErr,
                  bp::on_exit = slowExitCode,
                  ioc);
  std::future<std::string> fastStdErr, fastStdOut;
  std::future<i32> fastExitCode;
  ch.emplace_back(std::format("./{}"sv, path::cpp::kFast.stem().string()),
                  bp::std_in < fastPipe,
                  bp::std_out > fastStdOut,
                  bp::std_err > fastStdErr,
                  bp::on_exit = fastExitCode,
                  ioc);
  ioc.run();

  if (auto&& exitCode = slowExitCode.get(); exitCode != kExitSuccessCode) {
    return std::unexpected(std::format("slow: {}"sv, slowStdErr.get()));
  }
  if (auto&& exitCode = fastExitCode.get(); exitCode != kExitSuccessCode) {
    return std::unexpected(std::format("fast: {}"sv, fastStdErr.get()));
  }

  if (auto&& slowData = slowStdOut.get(), && fastData = fastStdOut.get();
    slowData != fastData) {
    return std::unexpected(std::format("Fail: {}slow: {}fast: {}"sv,
                                       data, slowData, fastData));
  }
  return {};
}

template <std::size_t kIter, bool kSync>
std::expected<void, std::string> runTests() {
  if constexpr (kSync) {
    for (std::size_t i{}; i < kIter; ++i) {
      if (auto&& ret = runTest(); !ret) {
        return std::unexpected(ret.error());
      }
      std::println(std::cerr, "done: {}", i);
      std::cerr.flush();
    }
    return {};
  } else {
    static_assert(false, "To be done");
    return {};
  }
}

int main() {
  std::cout << compile()
    .and_then(runTests</*kIter=*/1000000u, /*kSync=*/true>)
    .error_or("Successfully done"s) << std::endl;
}