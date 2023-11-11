#include <unordered_map>
#include <string_view>
#include <filesystem>
#include <algorithm>
#include <utility>
#include <string>
#include <ranges>

#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include "mehawk/standard_paths.hpp"
#include "mehawk/os_detection.hpp"

namespace
{

auto safe_getenv(char const* name) -> tl::optional<std::string_view>
{
  auto const result = std::getenv(name);

  if(result) return { result };
  else return {};
}

#ifdef OS_LINUX
auto get_linux_standard_paths() -> hm::StandardPaths::GetResult
{
  namespace fs = std::filesystem;
  using enum hm::StandardPaths::RetrievalError;

  static auto const home = safe_getenv("HOME");

  if(not home)
    return tl::unexpected(NoHomeVariable);

  static auto const config_path = safe_getenv("XDG_CONFIG_HOME").conjunction(fs::path(*home) / ".config");
  static auto const data_path = safe_getenv("XDG_DATA_HOME").conjunction(fs::path(*home) / ".local/share");
  static auto const cache_path = safe_getenv("XDG_CACHE_HOME").conjunction(fs::path(*home) / ".cache");

  return {
    hm::StandardPaths::Paths {
      .config = *config_path,
      .data = *data_path,
      .cache = *cache_path,
    },
  };
}

#elif defined(OS_MAC)

auto get_mac_standard_paths() -> hm::StandardPaths::GetResult
{
  namespace fs = std::filesystem;
  using enum hm::StandardPaths::RetrievalError;

  static auto const home = safe_getenv("HOME");

  if(not home)
    return tl::unexpected(NoHomeVariable);

  static auto const config_path = fs::path(*home) / "Library/Preferences";
  static auto const data_path = fs::path(*home) / "Library/Application Support";
  static auto const cache_path = fs::path(*home) / "Library/Caches";

  return { hm::StandardPaths::Paths {
    .config = config_path,
    .data = data_path,
    .cache = cache_path,
  } };
}

#elif defined(OS_WINDOWS)
auto get_windows_standard_paths(std::string_view scope) -> hm::StandardPaths::GetResult
{
  using enum hm::StandardPaths::RetrievalError;

  static auto const app_data = safe_getenv("APPDATA");
  if(not app_data) return tl::unexpected(NoAppDataVariable);

  static auto const local_app_data = safe_getenv("LOCALAPPDATA");
  if(not local_app_data) return tl::unexpected(NoLocalAppDataVariable);

  static auto const program_data = safe_getenv("PROGRAMDATA");
  if(not program_data) return tl::unexpected(NoProgramDataVariable);

  switch(scope) {
  }

  // return { hm::StandardPaths::Paths {
  //   .config = *config_path,
  //   .data = *data_path,
  //   .cache = *cache_path,
  // } };
}
#endif

} // namespace

namespace hm
{

auto StandardPaths::get(Scope scope, Type type) -> GetResult
{
  using enum hm::OperatingSystem;

#ifdef OS_LINUX
  return get_linux_standard_paths();
#elif defined(OS_MAC)
  return get_mac_standard_paths();
#else
  return get_windows_standard_paths(scope, type);
#endif
}

} // namespace hm
