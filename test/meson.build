local_deps = [
  dependency('catch2-with-main', required: true),
]

test_sources = files('env.cpp')

test_exe = executable(
  'mehawk_test',
  test_sources,
  include_directories: include_directories('.'),
  dependencies: [ mehawk_dep, local_deps ],
  override_options: mehawk_compilation_options,
  cpp_pch: '../src/mehawk/pch.hpp'
)

tests = [
  'Empty optional on non-existent env variable',
]

foreach test : tests
  test(test, test_exe)
endforeach
