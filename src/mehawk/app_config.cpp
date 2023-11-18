#include <filesystem>
#include <istream>
#include <sstream>

#include <spdlog/spdlog.h>

#include <mehawk/app_config.hpp>

auto AppConfig::write(std::ostream& config_stream) -> void
{
  config_stream << serialize_to_toml();
}

auto AppConfig::read(std::istream& config_stream, AppConfig defaults) -> AppConfig
{
  auto config = toml::parse(config_stream);

  return AppConfig {
    .log_to_file = config["log_to_file"].value_or(static_cast<bool>(defaults.log_to_file)),
  };
}

auto AppConfig::serialize_to_toml() -> toml::table
{
  return toml::table {
    { "log_to_file", static_cast<bool>(log_to_file) }
  };
}
