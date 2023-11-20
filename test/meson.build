catch2 = dependency('catch2', method: 'auto', required: false)
# if not expected.found()
#   catch2_sub = cmake.subproject('', options: build_type_opts, required: true)
#   catch2 = catch2_sub.dependency('catch2-with-main')
# endif

local_deps = [
  catch2
]

test_sources = files()

test_exe = executable(
  'mehawk_test',
  test_sources,
  include_directories: include_directories('.'),
  dependencies: [ mehawk_dep, local_deps ],
  override_options: mehawk_compilation_options,
)

tests = []

foreach test : tests
  test(test, test_exe)
endforeach
