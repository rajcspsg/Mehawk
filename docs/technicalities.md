# Haumea technicalities

## Tools used

- **Programming language** - C++20 with:
  - dpp 10.0.23 (for discord, a patched version that allows for self-botting)
  - spdlog 1.11.0 (for logging)
  - gtkmm-4.0 (for GUI)
  - catch2 3.2.0 (for unit tests)
  - libassert (for awesome asserts)

- **Build system** - Meson >= 0.56.0

- **Utility**:
  - Nix 23.05 (reproducibility, environments and such)
  - Just 1.13.0 (command runner)

## Key features

- Overlay for given text/voice chats
  - Ability to filter messages and users in the overlay
  - Potentially ability to display images/gifs/files in /some/ way
  - Better notifications, also ability to set *watches* (that is - notifications for new messages in certain channels)
  - Moving the overlay
  - Overlay is transparent generally but can be enabled to be not-transparent and clickable
  - Vim keybinds
