release_build_dir := "build_release"
debug_build_dir := "build_debug"

default:
	@just --list

alias sr := setup-release
setup-release:
	meson setup {{ release_build_dir }}

alias sd := setup-debug
setup-debug:
	meson setup {{ debug_build_dir }}

alias cd := compile-debug
compile-debug: setup-debug
	meson configure --buildtype debug --debug -Db_lundef=false --optimization 0 -Dcpp_debugstl=true -Db_sanitize=address,undefined --warnlevel 3 {{ debug_build_dir }}
	meson compile -C {{ debug_build_dir }} mehawk

alias cr := compile-release
compile-release:
	meson configure --buildtype release -Db_sanitize=none --optimization 3 -Db_lto=true -Dcpp_debugstl=false {{ release_build_dir }}
	meson compile -C {{ release_build_dir }} mehawk

alias rd := run-debug
run-debug:
	nixGL {{ debug_build_dir }}/src/mehawk

alias rr := run-release
run-release:
	nixGL {{ release_build_dir }}/src/mehawk

alias t := test
test:
	meson test -C build_debug --no-suite catch2 --no-suite spdlog

# vim: ft=make
