#include <string>

namespace static_config
{

auto constexpr app_name() -> std::string
{
  return "mehawk";
}

auto constexpr global_logger_pattern() -> char const*
{
  // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
  // [Logger type/Thread id] Year-Month-Day Time.Nanoseconds => Actual Message
  return "[%Y-%m-%d %T/%t] %^%=5l%$ %v";
}

auto constexpr config_filename() -> char const*
{
  return "config.toml";
}

} // namespace static_config
