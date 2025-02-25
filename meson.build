project(
  'mehawk',
  [ 'c', 'cpp' ],
  version : '0.1.0',
  meson_version : '>= 0.63.0',
  license: 'mit'
)

# have to do that to avoid MSVC breaking code with their min/max macros
if(meson.get_compiler('cpp').get_id() == 'msvc')
  add_project_arguments('-DNOMINMAX', language: 'cpp')
endif

if(meson.get_compiler('cpp').get_id() == 'clang')
  add_project_arguments(['-stdlib=libc++'], language: 'cpp')
endif

cmake = import('cmake')

build_type_opts = cmake.subproject_options()
build_type_opts.add_cmake_defines({ 'CMAKE_BUILD_TYPE': get_option('buildtype').to_upper() } )

libassert = dependency('libassert', method: 'auto', required: false)
if not libassert.found()
  libassert_sub = cmake.subproject('libassert', options: build_type_opts, required: true)
  libassert = libassert_sub.dependency('assert')
endif

optional = dependency('optional', method: 'auto', required: false)
if not optional.found()
  optional_sub = cmake.subproject('optional', options: build_type_opts, required: true)
  optional = optional_sub.dependency('optional')
endif

expected = dependency('expected', method: 'auto', required: false)
if not expected.found()
  expected_sub = cmake.subproject('expected', options: build_type_opts, required: true)
  expected = expected_sub.dependency('expected')
endif

local_deps = [
  dependency('threads', required: true),

  libassert,
  optional,
  expected,

  dependency('tomlplusplus', required: true),
  dependency('magic_enum', required: true),
  dependency('fmt', required: true),
  dependency('spdlog', required: true),
]

mehawk_compilation_options = [
  'cpp_std=c++20'
]

include_dirs = [
  include_directories('src')
]

sources = files(
  'src/mehawk/standard_paths.cpp',
  'src/mehawk/app_config.cpp',
  'src/mehawk/env.cpp',
  'src/mehawk/app.cpp'
)

mehawk_dep = declare_dependency(
  sources: sources,
  dependencies: local_deps,
  include_directories: include_dirs,
)

subdir('src')
subdir('test')
