{
  description = "Development flake for Mehawk, an overlay app for many services.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/23.05";
    nixpkgs-unstable.url = "github:NixOS/nixpkgs/nixos-unstable";

    flake-parts.url = "github:hercules-ci/flake-parts";

    nixgl.url = "github:guibou/nixGL";
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
      }: {
        _module.args.pkgs = import inputs.nixpkgs {
          inherit system;
          overlays = [
            inputs.nixgl.overlay
            (new: prev: { gf = inputs'.nixpkgs-unstable.legacyPackages.gf; })
          ];
        };

        formatter = pkgs.alejandra;

        devShells.default =
          pkgs.mkShell.override {
            stdenv = pkgs.clang16Stdenv;
          } {
            buildInputs = with pkgs; [
              xorg.libX11
              xorg.libXrandr
              xorg.libXinerama
              xorg.libXcursor
              xorg.libXi
              libxkbcommon
              libGL
              libglvnd

              pkgs.nixgl.auto.nixGLDefault
              llvmPackages_16.bintools
              clang-tools_16
              cmake
              pkg-config

              gf

              just
              ninja
              meson

              openssl
              python311
              zlib
            ];

            env = {
              CLANGD_PATH = "${pkgs.clang-tools_16}/bin/clangd";
              ASAN_SYMBOLIZER_PATH = "${pkgs.llvmPackages_16.bintools-unwrapped}/bin/llvm-symbolizer";
              CXX_LD = "lld";
            };
          };
      };
    };
}
