project(
  'haumea',
  'cpp',
  version : '0.1.0',
  license: 'mit'
)

if(meson.get_compiler('cpp').get_id() == 'msvc') # have to do that to avoid MSVC breaking code with their min/max macros
  add_project_arguments('-DNOMINMAX', language: 'cpp')
endif

local_deps = [
  dependency('fmt', required: true),
  dependency('gtkmm4', required: true),
  dependency('dpp', required: true),
]

compilation_options = [
  'cpp_std=c++20'
]

include_dirs = [
  include_directories('include')
]

sources = files(
  'src/main.cpp',
)

executable(
  'haumea',
  sources,
  dependencies: local_deps,
  include_directories: include_dirs,
  override_options: compilation_options,
)
