project(
  'haumea',
  'cpp',
  version : '0.1.0',
  license: 'mit'
)

# have to do that to avoid MSVC breaking code with their min/max macros
if(meson.get_compiler('cpp').get_id() == 'msvc')
  add_project_arguments('-DNOMINMAX', language: 'cpp')
endif

cmake = import('cmake')

dpp_sub_opts = cmake.subproject_options()
if host_machine.system() == 'linux' and meson.get_compiler('cpp').has_argument('-pthread')
  # a quickfix for dpp not having -pthread for some reason
  dpp_sub_opts.append_link_args('-pthread')
endif

# unsafely assuming only 'release' and 'debug' are used, let the world burn
if get_option('buildtype') == 'release'
  dpp_sub_opts.add_cmake_defines( { 'CMAKE_BUILD_TYPE': 'RELEASE' } )
else
  dpp_sub_opts.add_cmake_defines( { 'CMAKE_BUILD_TYPE': 'DEBUG' } )
endif

cmd = run_command('sh', '-c', 'echo $OPUS_INCLUDE_DIRS')
OPUS_INCLUDE_DIRS = cmd.stdout().strip()

cmd = run_command('sh', '-c', 'echo $OPUS_LIBRARIES')
OPUS_LIBRARIES = cmd.stdout().strip()

dpp_sub_opts.add_cmake_defines( { 'OPUS_INCLUDE_DIRS': OPUS_INCLUDE_DIRS } )
dpp_sub_opts.add_cmake_defines( { 'OPUS_LIBRARIES': OPUS_LIBRARIES } )
dpp_sub = cmake.subproject('dpp', options: dpp_sub_opts, required: true)

local_deps = [
  dependency('threads'),

  dpp_sub.dependency('dpp'),

  dependency('fmt', required: true),
  dependency(
    'gtkmm-4.0',
    required: true,
    allow_fallback: true
  ),
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
