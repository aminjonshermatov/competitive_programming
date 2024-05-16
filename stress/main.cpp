#include <iostream>
#include <format>
#include <expected>

#include <boost/process.hpp>
#include <boost/asio.hpp>

#include "config.hpp"

std::expected<bool, std::string> compile() {
  auto commandGenerator = [](const std::filesystem::path& path) {
    return std::format("g++ --std=c++23 -O2 {} -DLOCAL -o {}",
                       path.string(),
                       path.stem().string());
  };

  namespace bp = boost::process;

  std::array cmds{
    commandGenerator(path::cpp::kGen),
    commandGenerator(path::cpp::kSlow),
    commandGenerator(path::cpp::kFast),
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
  for (auto&& p : ch) {
    p.detach();
  }
  ios.run();
  constexpr auto kExitSuccessCode = 0uz;

  for (std::size_t i{}; i < nCmds; ++i) {
    if (exitCodes[i].get() != kExitSuccessCode) {
      return std::unexpected(stdErr[i].get());
    }
  }
  return true;
}

int main() {
  using namespace std::chrono_literals;
  std::cout << compile().error_or("Successfully compiled") << '\n';

  constexpr auto kIter = 1'000uz;
  for (std::size_t i{}; i < kIter; ++i) {

  }
}