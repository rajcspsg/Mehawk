# Mehawk technicalities

## Tools used

- **Programming language** - C++20 with:
  - dpp 10.0.23 (for discord, a [**patched version**](../subprojects/packagefiles/dpp/dpp-selfbot.patch) that allows for self-botting)
  - spdlog 1.11.0 (for logging)
  - opengl:
    - glfw 3.3.8
    - glad 0.1.36 (gl 3.3, compatibility)
  - catch2 3.2.0 (for unit tests)
  - libassert v1.1 (for awesome asserts)

- **Build system** - Meson >= 0.63.0

- **Utility**:
  - Nix 2.16.1 (reproducibility, environments and such)
  - Just 1.13.0 (command runner)

## Key features

- Overlay for given text/voice chats
- System for changing the layout of the application and being able to add several sources of messages and stuff (like being able to have voice chat from discord, matrix chat along discord chat etc.)
- Ability to filter messages and users in the overlay
- Embeds, videos, images and stuff are supposed to be concealed by default, but potentially they could be also shown somehow
- Better notifications, also ability to set *watches* (that is - notifications for new messages in certain channels)
- Some global keybind to toggle the passthrough of the window
- Vim keybinds (clicking links, stuff)
- Ability to type a message possibly
