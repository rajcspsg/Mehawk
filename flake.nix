{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
      };
    in {
      formatter = pkgs.alejandra;

      devShells.default = with pkgs; mkShell.override {
          stdenv = lowPrio llvmPackages_15.stdenv;
        } {
          buildInputs = [
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
          };
        };

    });
}
