{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  } @ inputs:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
      };

      libPath = with pkgs; libmakeLibraryPath [
        shared-mime-info
        gtkmm4
      ];
    in {
      formatter = pkgs.alejandra;

      devShells.default = with pkgs;
        mkShell.override {
          stdenv = lowPrio llvmPackages_15.stdenv;
        } {
          packages = [
            ### cpp general
            clang-tools_16
            pkgconfig

            #### this project specific
            gtkmm4
            just
            ninja
            meson
            python311
            shared-mime-info
          ];
        };

        LD_LIBRARY_PATH = libPath;
        CLANGD_PATH = "${pkgs.clang-tools_16}/bin/clangd";
    });
}
