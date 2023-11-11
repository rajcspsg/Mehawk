#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include <tl/expected.hpp>

namespace hm
{

class StandardPaths
{
public:
  enum class Scope
  {
    User,
    System
  };

  enum class Type
  {
    Config,
    Data,
    Cache
  };

  enum class RetrievalError
  {
    NoHomeVariable,

    NoProgramDataVariable,
    NoAppDataVariable,
    NoLocalAppDataVariable,
  };

  struct Paths
  {
    std::filesystem::path config;
    std::filesystem::path data;
    std::filesystem::path cache;
  };

  using GetResult = tl::expected<Paths, RetrievalError>;

  /**
   * @brief Returns a standard log path for host os
   *
   * @param scope If the path should be for an user or the entire system
   * @param type The type of the path
   *
   * @description
   * Type config:
   *  - Linux: $XDG_CONFIG_HOME (defaults to $HOME/.config) (for both User and System)
   *  - Mac: $HOME/Library/Preferences (for both User and System)
   *  - Windows:
   *    - User: %APPDATA%
   *    - System: %ProgramData%
   *
   * Type data:
   *  - Linux: $XDG_DATA_HOME (defaults to $HOME/.local/share)
   *  - Mac: $Home/Library/Application Support (for both User and System)
   *  - Windows:
   *    - User: %APPDATA%
   *    - System: %ProgramData%
   *
   * Type cache:
   *  - Linux: $XDG_CACHE_HOME (defaults to $HOME/.cache) (for both User and System)
   *  - Mac: $HOME/Library/Cache (for both User and System)
   *  - Windows:
   *    - User: %LOCALAPPDATA%
   *    - System: %ProgramData%
   */
  static auto get(Scope scope, Type type) -> GetResult;
};

} // namespace hm
