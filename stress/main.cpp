#include <iostream>
#include <format>
#include <expected>

#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <boost/fiber/all.hpp>

#include "config.hpp"

namespace bp = boost::process;
using namespace std::string_literals;
using namespace std::string_view_literals;

constexpr auto kExitSuccessCode = 0uz;

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
  std::array<std::future<int>, nCmds> exitCodes;

  std::vector<bp::child> ch;
  boost::asio::io_service ios;
  for (std::size_t i{}; i < nCmds; ++i) {
    ch.emplace_back(cmds[i],
                    bp::std_in.close(),
                    bp::std_out > bp::null,
                    bp::std_err > stdErr[i],
                    bp::on_exit = exitCodes[i],
                    ios);
  }
  ios.run();

  for (std::size_t i{}; i < nCmds; ++i) {
    if (exitCodes[i].get() != kExitSuccessCode) {
      return std::unexpected(stdErr[i].get());
    }
  }
  return {};
}

std::expected<void, std::string> runTest() {
  boost::asio::io_service ios;

  std::future<std::string> genStdOut, genStdErr;
  std::future<int> genExitCode;
  bp::child gen(std::format("./{}"sv, path::cpp::kGen.stem().string()),
                bp::std_in.close(),
                bp::std_out > genStdOut,
                bp::std_err > genStdErr,
                bp::on_exit = genExitCode,
                ios);

  ios.run();
  if (auto&& exitCode = genExitCode.get(); exitCode != kExitSuccessCode) {
    return std::unexpected(std::format("generator: {}"sv, genStdErr.get()));
  }

  auto&& data = genStdOut.get();
  auto dataBuffer = boost::asio::buffer(data);
  bp::async_pipe slowPipe(ios), fastPipe(ios);
  slowPipe.write_some(dataBuffer);
  fastPipe.write_some(dataBuffer);

  std::future<std::string> slowStdErr, slowStdOut;
  std::future<int> slowExitCode;
  bp::child slow(std::format("./{}"sv, path::cpp::kSlow.stem().string()),
                 bp::std_in < slowPipe,
                 bp::std_out > slowStdOut,
                 bp::std_err > slowStdErr,
                 bp::on_exit = slowExitCode,
                 ios);
  ios.reset();

  std::future<std::string> fastStdErr, fastStdOut;
  std::future<int> fastExitCode;
  bp::child fast(std::format("./{}"sv, path::cpp::kFast.stem().string()),
                 bp::std_in < fastPipe,
                 bp::std_out > fastStdOut,
                 bp::std_err > fastStdErr,
                 bp::on_exit = fastExitCode,
                 ios);
  ios.run();

  if (auto&& exitCode = slowExitCode.get(); exitCode != kExitSuccessCode) {
    return std::unexpected(std::format("slow: {}"sv, slowStdErr.get()));
  }
  if (auto&& exitCode = fastExitCode.get(); exitCode != kExitSuccessCode) {
    return std::unexpected(std::format("fast: {}"sv, fastStdErr.get()));
  }

  if (auto&& slowData = slowStdOut.get(), fastData = fastStdOut.get();
    slowData != fastData) {
    return std::unexpected(std::format("Fail: {}slow: {}fast: {}"sv,
                                       data, slowData, fastData));
  }

  return {};
}

constexpr auto kIter = 100'500uz;

template <bool kSync>
std::expected<void, std::string> runTests() {
  if constexpr (kSync) {
    for (std::size_t i{}; i < kIter; ++i) {
      if (auto&& ret = runTest(); !ret) {
        return std::unexpected(ret.error());
      }
    }
    return {};
  } else {
    static_assert(false);
  }
}

int main() {
  std::cout << compile()
    .and_then(runTests</*kSync=*/true>)
    .error_or("Successfully done"s) << std::endl;
}