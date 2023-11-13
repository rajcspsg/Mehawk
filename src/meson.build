sources = files(
  'glad/glad.c',

  'mehawk/main.cpp'
)

executable(
  'mehawk',
  sources: sources,
  dependencies: mehawk_dep,
  override_options: mehawk_compilation_options,
  cpp_pch: 'mehawk/pch.hpp',
  install: true
)
