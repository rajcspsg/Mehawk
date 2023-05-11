meson-exists:
	@if ! which meson 1>/dev/null 2>&1; then echo 'Cannot find meson executable'; exit 1; fi

release_build_dir := "build_release"
debug_build_dir := "build_debug"

alias sr := setup-release
setup-release: meson-exists
	meson setup {{ release_build_dir }}

alias sd := setup-debug
setup-debug: meson-exists
	meson setup {{ debug_build_dir }}

alias d := debug
debug: meson-exists setup-debug
	meson configure --buildtype debug --debug -Db_lundef=false --optimization 0 -Dcpp_debugstl=true -Db_sanitize=address,undefined --warnlevel 3 {{ debug_build_dir }}
	meson compile -C {{ debug_build_dir }}

alias r := release
release: meson-exists setup-release
	meson configure --buildtype release -Db_sanitize=none --optimization 3 -Db_lto=true -Dcpp_debugstl=false {{ release_build_dir }}
	meson compile -C {{ release_build_dir }}

# vim: ft=make
