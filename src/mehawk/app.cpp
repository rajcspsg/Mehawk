#include <fstream>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

#include <magic_enum.hpp>

#include <mehawk/enum_formatter.hpp>
#include <mehawk/standard_paths.hpp>
#include <mehawk/static_config.hpp>
#include <mehawk/app_config.hpp>
#include <mehawk/app.hpp>

namespace
{

enum class ShouldLogToFile
{
  Yes,
  No
};

auto setup_logs(auto const& log_path, ShouldLogToFile should_log_to_file) -> void
{
  try {
    auto sinks = std::vector<spdlog::sink_ptr>();

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    sinks.push_back(std::move(console_sink));

    if(should_log_to_file == ShouldLogToFile::Yes) {
      auto constexpr rotation_hour = 23;
      auto constexpr rotation_minute = 59;
      auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
        static_cast<std::filesystem::path>(log_path),
        rotation_hour,
        rotation_minute
      );

      daily_sink->set_level(spdlog::level::info);
      sinks.push_back(std::move(daily_sink));
    }

    spdlog::set_default_logger(
      std::make_unique<spdlog::logger>("console_and_daily", sinks.begin(), sinks.end())
    );
  } catch(spdlog::spdlog_ex const& ex) {
    spdlog::error(R"X(Couldn't retrieve user log path. "{}")X", ex.what());
    return;
  }

  spdlog::set_pattern(static_config::global_logger_pattern());
}

auto create_config_file(std::filesystem::path const& config_path, AppConfig defaults)
{
  namespace fs = std::filesystem;

  fs::create_directories(config_path.parent_path());

  auto file = std::ofstream(config_path);
  file.exceptions(std::ios_base::badbit | std::ios_base::failbit);

  defaults.write(file);

  return defaults;
}

auto create_config(std::filesystem::path const& config_path, AppConfig defaults)
{
  spdlog::info("Config directory doesn't exist. Creating one.");

  try {
    return create_config_file(config_path, defaults);
  } catch(std::filesystem::filesystem_error const& fs_error) {
    auto const& code = fs_error.code();

    spdlog::error(
      R"(Couldn't create default config. OS Error for path "{}" with code "{}", message "{}".)",
      fs_error.path1().string(),
      code.value(),
      code.message()
    );

  } catch(std::exception const& ex) {
    spdlog::error(R"(Couldn't create default config: "{}".)", ex.what());
  }

  return defaults;
}

auto read_existing_config(std::filesystem::path const& config_path, AppConfig defaults)
{
  try {
    auto file = std::ifstream(config_path);
    file.exceptions(std::ios_base::badbit | std::ios_base::failbit);

    return AppConfig::read(file, defaults);
  } catch(toml::parse_error const& parse_error) {
    spdlog::error(R"(Parsing error while reading existing config. "{}")", parse_error.what());
  } catch(std::exception const& ex) {
    spdlog::error(R"(Couldn't read existing config: "{}".)", ex.what());
  }

  return defaults;
}

auto read_config(std::filesystem::path const& config_path, AppConfig defaults)
{
  namespace fs = std::filesystem;

  if(not fs::exists(config_path)) {
    return create_config(config_path, defaults);
  }

  return read_existing_config(config_path, defaults);
}

} // namespace

auto App::run(
  [[maybe_unused]] int argc,
  [[maybe_unused]] char** argv
) -> int
{
  spdlog::set_pattern(static_config::global_logger_pattern());

  auto const standard_paths = StandardPaths::get(StandardPaths::IncludeAppFolder);
  if(not standard_paths) {
    spdlog::error(R"(Cannot read standard paths! "{}".)", magic_enum::enum_name(standard_paths.error()));
  } else {
    auto const config_path = standard_paths.value().config / static_config::config_filename();

    spdlog::info(R"(Reading config file from "{}".)", config_path.string());

    auto config = read_config(
      config_path,
      AppConfig { .log_to_file = true }
    );

    auto const log_filepath = standard_paths.value().data / static_config::app_name();
    auto const log_to_file = config.log_to_file ? ShouldLogToFile::Yes : ShouldLogToFile::No;
    setup_logs(log_filepath, log_to_file);

    spdlog::info("Logs set up [{}].", log_to_file);
  }

  return 0;
}
