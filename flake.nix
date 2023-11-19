{
  description = "Development flake for Mehawk, an overlay app for many services.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/23.05";
    nixpkgs-unstable.url = "github:NixOS/nixpkgs/nixos-unstable";

    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = ["x86_64-linux"];
      perSystem = {
        config,
        self',
        inputs',
        pkgs,
        system,
        ...
      }: let
        mehawkBuildInputs = [
          pkgs.lld
          pkgs.cmake
          pkgs.pkg-config

          pkgs.just
          pkgs.ninja
          pkgs.meson
          pkgs.git
        ];
      in {
        _module.args.pkgs = import inputs.nixpkgs {
          inherit system;
          overlays = [
            (new: prev: { gf = inputs'.nixpkgs-unstable.legacyPackages.gf; })
          ];
        };

        formatter = pkgs.alejandra;

        packages.default = pkgs.stdenv.mkDerivation {
          name = "mehawk";
          version = "git";

          src = builtins.filterSource (path: type:
            baseNameOf path
            != ".git"
            && baseNameOf path != ".direnv"
            && baseNameOf path != ".github"
            && baseNameOf path != ".tests"
            && baseNameOf path != "docs"
            && baseNameOf path != "build_debug"
            && baseNameOf path != "build_release") ./.;

          buildInputs = mehawkBuildInputs;

          configurePhase = ''
            just sr
          '';

          buildPhase = ''
            just cr
          '';

          installPhase = ''
            mkdir $out/bin
            cp build_release/mehawk/mehawk
          '';
        };

        devShells.default =
          pkgs.mkShell.override {
            stdenv = pkgs.clang15Stdenv;
          } {
            buildInputs =
              mehawkBuildInputs
              ++ [
                pkgs.gf
              ];

            env = {
              CLANGD_PATH = "${pkgs.clang-tools_15}/bin/clangd";
              ASAN_SYMBOLIZER_PATH = "${pkgs.llvmPackages_15.bintools-unwrapped}/bin/llvm-symbolizer";
              CXX_LD = "lld";
            };
          };
      };
    };
}
