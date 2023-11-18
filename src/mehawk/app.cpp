#include <memory>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

#include <magic_enum.hpp>

#include <mehawk/standard_paths.hpp>
#include <mehawk/app.hpp>

namespace
{

/// Set's up all the logging functionalities, like rotating file logs,
/// application log format, etc..
auto setup_logs() -> void
{
  auto standard_paths = StandardPaths::get(StandardPaths::IncludeAppFolder);

  if(not standard_paths.has_value()) {
    auto const error = standard_paths.error();

    spdlog::error(R"X(Couldn't retrieve user log path: {})X", magic_enum::enum_name(error));
    return;
  }

  auto const log_path = standard_paths.value().data;

  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    auto constexpr rotation_hour = 23;
    auto constexpr rotation_minute = 59;
    auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_path, rotation_hour, rotation_minute);

    console_sink->set_level(spdlog::level::info);

    auto list = spdlog::sinks_init_list { console_sink, daily_sink };
    auto default_logger = std::make_unique<spdlog::logger>(
      "console_and_daily",
      list.begin(),
      list.end()
    );

    spdlog::set_default_logger(std::move(default_logger));
  } catch(spdlog::spdlog_ex const& ex) {
    spdlog::error(R"X(Couldn't retrieve user log path. "{}")X", ex.what());
    return;
  }
  // After the above code everything is applied to default_logger

  // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
  // [Logger type/Thread id] Year-Month-Day Time.Nanoseconds => Actual Message
  spdlog::set_pattern("[%^%L%$/%t] %Y-%m-%d %T.%f => %v");
}

} // namespace

auto App::run(
  [[maybe_unused]] int argc,
  [[maybe_unused]] char** argv
) -> int
{
  setup_logs();
  // Setup logs
  // Setup paths
  // Setup file watcher
  // Read config
  // ?
  spdlog::info("App started.");

  return 0;
}
