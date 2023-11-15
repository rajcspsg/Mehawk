release_build_dir := "build_release"
debug_build_dir := "build_debug"

default:
	@just --list

meson-exists:
	@if ! which meson 1>/dev/null 2>&1; then echo 'Cannot find meson executable'; exit 1; fi

nixgl-exists:
	@if ! which nixGL 1>/dev/null 2>&1; then echo 'Cannot find nixGL executable'; exit 1; fi

alias sr := setup-release
setup-release: meson-exists
	meson setup {{ release_build_dir }}

alias sd := setup-debug
setup-debug: meson-exists
	meson setup {{ debug_build_dir }}

alias cd := compile-debug
compile-debug: meson-exists setup-debug
	meson configure --buildtype debug --debug -Db_lundef=false --optimization 0 -Dcpp_debugstl=true -Db_sanitize=address,undefined --warnlevel 3 {{ debug_build_dir }}
	meson compile -C {{ debug_build_dir }} mehawk

alias cr := compile-release
compile-release: meson-exists
	meson configure --buildtype release -Db_sanitize=none --optimization 3 -Db_lto=true -Dcpp_debugstl=false {{ release_build_dir }}
	meson compile -C {{ release_build_dir }} mehawk

alias rd := run-debug
run-debug: nixgl-exists
	nixGL {{ debug_build_dir }}/src/mehawk

alias rr := run-release
run-release: nixgl-exists
	nixGL {{ release_build_dir }}/src/mehawk

alias t := test
test: meson-exists setup-debug
	./build_debug/test/mehawk_test

alias ct := compile-and-test
compile-and-test: meson-exists compile-debug && test

# vim: ft=make
