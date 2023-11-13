#include <spdlog/spdlog.h>

#include <mehawk/app.hpp>

auto App::run(int argc, char** argv) -> int
{
  spdlog::info("Hello, World!");
  return 0;
}
