# Mehawk technicalities

## Naming

The name is chosen after `Messenger Hawk` from the Avatar: The Last Airbender animated series.

Messenger hawks are merely proxies between two communicating parties, which perfectly describes the purpose of Mehawk:  
A proxy which displays in a specific way the information sent by another people.

## Tools used

- **Programming language** - C++20 with:
  - dpp 10.0.23 ([**patched version**](../subprojects/packagefiles/dpp/dpp-selfbot.patch) that allows for self-botting)
  - spdlog 1.11.0
  - opengl 4.6:
    - glfw 3.3.8
    - glad 0.1.36
  - catch2 3.2.0
  - libassert v1.1

- **Build system** - Meson >= 0.63.0

- **Utility**:
  - Nix 2.16.1
  - Just 1.13.0

## Libraries overview

The rendering parts of the app are handled by **glfw** and **glad**. There's no GUI library, all rendering
is done by hand using OpenGL with these two libraries.

The discord communication is done with a patched version of **dpp**, although there are plans to move to a
custom, smaller version.

Testing is done via **catch2**.

Other utility libraries include:
  - **spdlog** for nice logs
  - **libassert** for nice asserts
  - **expected** for C++23's actually working `<expected>`
  - **optional** for a better optional with monadic operations
  - **magic_enum** for useful enum operations, mostly used in tests

## Overview

### General

Mehawk is supposed to be an overlay application for many services.
For now only IRC, Discord and Matrix are planned.

### Interface

The main mehawk interface of mehawk is supposed to be the GUI.
It is however supposed to be possible to carry out some actions using the command-line interface.

For now:
  - Executing some queries and mofifications on the config.
  - Sending commands to the running notification and overlay daemon.

### Plugin support

For now it is unclear if support for each platform is going to be implemented with plugins (luajit) or directly in C++.

### Hot-reloadable config

Mehawk should have a hot-reloadable config in form of a `TOML` file.
The config should be editable from an additionally spawned GUI window,
but there is also supposed to be a watch, which would reload on config file changes
(assuming the config is correct, if not, an error should arise).

### UI

The UI is supposed to be transparent and oblivious to mouse input, unless a certain global key combination is pressed.
If it is, input mode is activated, in which the window is focused and responds to both mouse and key inputs.

In the input mode, the user would be able to use vim-like keybindings to navigate the view.

#### Layouts

The UI is supposed to be flexible and allow the user for creating it's own layouts (for example, the user may wish to
see active participants in currently joined discord voice chat on the left,
as well as a matrix chat along some discord channel chat).

#### Embeddables

Images, gifs, videos, files, and all other embeds are together called **embeddables**.
By default they are hidden behind their own label (\<image>, \<gif>, etc.), but can be enabled to be displayed
in the settings.

#### Formatting

All formatting should be respected.

#### Themes

Some parts of the rendered output can also be altered by custom themes provided by the user.

### Notifications

Mehawk should be also able spawn a custom notification daemon.
It is useful if, for example, someone wishes to have **Do Not Disturb** status on discord,
which completely removes notifications, but waits for response/message from some channels.

The notifications should be highly customizable.

### Message ???

It is still undecided, but mehawk will possibly have an ability to type and send basic messages for various sources.

### Other niceities

Pings should reside at the top of the overlay for a chosen period of time.

## Architecture

This is only a vague overview of the architecture and some matters I need to figure out myself.
The general plan and specifics are subject to constant changes.

Main `Mehawk` class  

Figure out:
  - [ ] Extreme programming, CI and open source
  - [ ] The kernel architecture and plugin systems.
  - [ ] File watching.
  - [ ] Hot-reloading.
  - [ ] Font rendering.
  - [ ] Layout system.
