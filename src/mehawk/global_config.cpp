#include <cstdlib>
#include <filesystem>

#include <assert.hpp>
#include <tl/optional.hpp>
#include <tl/expected.hpp>

namespace hm::config
{

auto app_name() -> std::string;

} // namespace hm::config

namespace
{

auto get_env_var(char const* const name) -> tl::optional<std::string>
{
  auto const var = std::getenv(name);

  if(not var) {
    return {};
  } else {
    return { var };
  }
}

auto get_linux_log_path() -> tl::expected<std::filesystem::path, std::string>
{
  namespace fs = std::filesystem;

  static auto const linux_home = get_env_var("HOME");

  if(not linux_home) {
    return tl::unexpected("Cannot get access to the $HOME environment variable.");
  }

  static auto const path = get_env_var("XDG_CONFIG_HOME").value_or(fs::path(*linux_home) / ".config");

  return path;
}

auto get_windows_log_path() -> tl::expected<std::filesystem::path, std::string>
{
  namespace fs = std::filesystem;

  static auto const appdata = get_env_var("APPDATA");

  if(not appdata) {
    return tl::unexpected("Cannot get access to the %APPDATA% environment variable.");
  }

  static auto const path = get_env_var("XDG_CONFIG_HOME").value_or(fs::path(*appdata) / hm::config::app_name());

  return path;
}

auto get_mac_log_path() -> tl::expected<std::filesystem::path, std::string>
{
  namespace fs = std::filesystem;

  static auto const appdata = get_env_var("APPDATA");

  if(not appdata) {
    return tl::unexpected("Cannot get access to the %APPDATA% environment variable.");
  }

  static auto const path = get_env_var("XDG_CONFIG_HOME").value_or(fs::path(*appdata) / hm::config::app_name());

  return path;
}

} // namespace

namespace hm::config
{

auto app_name() -> std::string
{
  return "mehawk";
}

auto log_filename_format() -> std::filesystem::path
{
}

namespace paths
{

auto log_path() -> tl::expected<std::filesystem::path, std::string>
{
  switch(Current) {
    using enum hm::OperatingSystem;
    case Linux: return get_linux_log_path();
    case Mac: return "Mac";
    case Windows: return "Windows";
  }
}

} // namespace paths

} // namespace hm::config
