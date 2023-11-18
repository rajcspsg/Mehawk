#pragma once

#include <toml++/toml.h>

#include <mehawk/prelude.hpp>

struct AppConfig
{
public:
  MustInit<bool> log_to_file;

  auto write(std::ostream& config_stream) -> void;

  static auto read(std::istream& config_stream, AppConfig defaults) -> AppConfig;

private:
  auto serialize_to_toml() -> toml::table;
};
