# Mehawk

Mehawk is a general overlay for different services (discord, matrix and such).

The application is highly WIP, there's not much functional code in place yet.

Check out [technicalities.md](./docs/technicalities.md) for general overview and vague architecture.

## Build

Install [`just`](https://github.com/casey/just) and [`meson`](https://github.com/mesonuild/meson) and simply run:
- `just {s,c}r` to setup and build the release version.
- `just {s,c}d` to setup and build the debug version.

`just rr` will run the release version. `just rd` will run the debug version.

If you don't want to install `just`, simply follow the steps from Justfile in this order:
1. `setup-debug/release`
2. `compile-debug/release`
3. `run-debug/release`

No convenient and official method of building consists at the moment (like `nix build`) because of the WIP state.

## Installation

Nothing yet :)

## TBD :)
