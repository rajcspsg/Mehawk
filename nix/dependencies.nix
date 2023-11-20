{pkgs, ...}: let
  tl-optional = pkgs.stdenv.mkDerivation rec {
    pname = "optional";
    version = "1.1.0";

    revision = "v${version}";

    src = pkgs.fetchFromGitHub {
      owner = "TartanLlama";
      repo = "optional";
      rev = revision;
      sha256 = "sha256-WPTXTQmzJjAIJI1zM6svZZTO8gP/jt5xDHHRCCu9cmI=";
    };

    nativeBuildInputs = [pkgs.cmake];

    postInstall = ''
      mkdir -p $out/lib/pkgconfig
      substituteAll ${./pkg-config/optional.pc} $out/lib/pkgconfig/optional.pc
    '';
  };

  tl-expected = pkgs.stdenv.mkDerivation rec {
    pname = "expected";
    version = "1.1.0";

    revision = "v${version}";

    src = pkgs.fetchFromGitHub {
      owner = "TartanLlama";
      repo = "expected";
      rev = revision;
      sha256 = "sha256-AuRU8VI5l7Th9fJ5jIc/6mPm0Vqbbt6rY8QCCNDOU50=";
    };

    nativeBuildInputs = [pkgs.cmake];

    postInstall = ''
      mkdir -p $out/lib/pkgconfig
      substituteAll ${./pkg-config/expected.pc} $out/lib/pkgconfig/expected.pc
    '';
  };

  libassert = pkgs.stdenv.mkDerivation rec {
    pname = "libassert";
    version = "1.1";

    revision = "v${version}";

    src = pkgs.fetchFromGitHub {
      owner = "jeremy-rifkin";
      repo = "libassert";
      rev = revision;
      sha256 = "sha256-yXFeDIquQ+MTWRLHGQwhRK26xcwfWoejRzs+vmyZgQA=";
    };

    nativeBuildInputs = [pkgs.cmake];

    installPhase = ''
      mkdir -p $out/include $out/lib/pkgconfig
      cp $src/include/assert.hpp $out/include
      substituteAll ${./pkg-config/libassert.pc} $out/lib/pkgconfig/libassert.pc
    '';
  };
in [
  tl-optional
  tl-expected
  libassert
]
