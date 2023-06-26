{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/23.05";
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
          overlays = [inputs.nixgl.overlay];
        };

        formatter = pkgs.alejandra;

        devShells.default = pkgs.mkShell.override {
            stdenv = pkgs.lowPrio pkgs.llvmPackages_15.stdenv;
          } {
            buildInputs = with pkgs; [
              ### opengl and x11
              xorg.libX11
              xorg.libXrandr
              xorg.libXinerama
              xorg.libXcursor
              xorg.libXi
              libxkbcommon
              libGL
              libglvnd

              pkgs.nixgl.auto.nixGLDefault
              llvmPackages_15.bintools
              clang-tools_15
              cmake
              pkg-config

              just
              ninja
              meson

              openssl
              python311
              gtkmm4
            ];

            env = {
              CLANGD_PATH = "${pkgs.clang-tools_15}/bin/clangd";
              ASAN_SYMBOLIZER_PATH = "${pkgs.llvmPackages_15.bintools-unwrapped}/bin/llvm-symbolizer";
            };
          };
      };
    };
}
