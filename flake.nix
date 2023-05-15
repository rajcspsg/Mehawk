{
  description = "Fill this later, please.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
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
      }: {
        formatter = pkgs.alejandra;

        devShells.default = with pkgs;
          mkShell.override {
            stdenv = lowPrio llvmPackages_16.stdenv;
          } {
            buildInputs = [
              clang-tools_16
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
              CLANGD_PATH = "${pkgs.clang-tools_16}/bin/clangd";
            };
          };
      };
    };
}
