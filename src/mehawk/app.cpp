#include <filesystem>

#include <spdlog/spdlog.h>

#include <efsw/efsw.hpp>

#include <mehawk/prelude.hpp>
#include <mehawk/app.hpp>

namespace
{

// NOTE: This is a very simple test implementation
// TODO: Decouple this bitch from efs
class SingleFileWatcher
{
  struct Listener : efsw::FileWatchListener
  {
    auto handleFileAction(
      [[maybe_unused]] efsw::WatchID watchid,
      [[maybe_unused]] std::string const& dir,
      [[maybe_unused]] std::string const& filename,
      efsw::Action action,
      [[maybe_unused]] std::string oldFilename
    ) -> void override
    {
      switch(action) {
        case efsw::Action::Add:
        case efsw::Action::Delete:
        case efsw::Action::Modified:
        case efsw::Action::Moved:
        default:
          MH_UNIMPLEMENTED;
      }
    }
  };

public:
  /// File doesn't exist
  struct FileNotFoundError final : std::exception
  {};

  /// It's probably a symlink
  struct FileOutOfScopeError final : std::exception
  {};

  /// Path not readable, probably lacking permissions
  struct FileNotReadableError final : std::exception
  {};

  /// File system watcher failed to watch for changes.
  struct WatcherError final : std::exception
  {};

  /// Other unspecified errror
  struct UnspecifiedError final : std::exception
  {};

  explicit SingleFileWatcher(std::filesystem::path const& file)
  {
    watch_single_file(file);
  }

private:
  using WatchID = DISTINCT(efsw::WatchID);

  auto watch_single_file(std::filesystem::path const& file) -> WatchID
  {
    auto const directory = file.parent_path();

    auto const result = impl.addWatch(
      directory.string(),
      &listener
    );

    return process_result(result, directory);
  }

  auto process_result(efsw::WatchID const result, std::filesystem::path const& directory) -> WatchID
  {
    switch(result) {
      using namespace efsw::Errors;
      case NoError: return WatchID(result);
      case FileRemote: {
        // This bool sets turns on the generic watcher
        impl = efsw::FileWatcher(true);
        return watch_single_file(directory);
      }
      case FileRepeated: MH_TRAP("This fires when a file is already added to watch.");
      case FileNotFound: throw FileNotFoundError();
      case FileOutOfScope: throw FileOutOfScopeError();
      case FileNotReadable: throw FileNotReadableError();
      case WatcherFailed: throw WatcherError();
      default:
      case Unspecified: throw UnspecifiedError();
    };
  }

  efsw::FileWatcher impl;
  WatchID watch_id;

  [[no_unique_address]] Listener listener;
};

} // namespace

auto App::run(
  [[maybe_unused]] int argc,
  [[maybe_unused]] char** argv
) -> int
{
  // Setup logs
  // Setup paths
  // Setup file watcher
  // Read config
  // ?
  spdlog::info("App started.");
  auto x = SingleFileWatcher("");

  return 0;
}
