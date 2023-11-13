#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include <tl/expected.hpp>

#include <mehawk/os_detection.hpp>

class StandardPaths
{
public:
  enum class Scope
  {
    User,
    System
  };

  enum class RetrievalError
  {
#ifndef OS_WINDOWS
    NoHomeVariable,
#endif
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
   *
   * @description
   * Type config:
   *  - Linux: $XDG_CONFIG_HOME (defaults to $HOME/.config) (only User)
   *  - Mac: $HOME/Library/Preferences (only User)
   *  - Windows:
   *    - User: %APPDATA%
   *    - System: %ProgramData%
   *
   * Type data:
   *  - Linux: $XDG_DATA_HOME (defaults to $HOME/.local/share)
   *  - Mac: $Home/Library/Application Support (only User)
   *  - Windows:
   *    - User: %APPDATA%
   *    - System: %ProgramData%
   *
   * Type cache:
   *  - Linux: $XDG_CACHE_HOME (defaults to $HOME/.cache) (only User)
   *  - Mac: $HOME/Library/Cache (only User)
   *  - Windows:
   *    - User: %LOCALAPPDATA%
   *    - System: %ProgramData%
   */
  static auto get(Scope const scope) -> GetResult;
};
