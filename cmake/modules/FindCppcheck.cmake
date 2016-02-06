find_program(CPPCHECK_EXECUTABLE
  NAMES cppcheck cppcheck.exe
  HINTS
    "$ENV{ProgramFiles}/Cppcheck"
  DOC "Cppcheck (http://cppcheck.sourceforge.net)")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cppcheck DEFAULT_MSG CPPCHECK_EXECUTABLE)

mark_as_advanced(CPPCHECK_EXECUTABLE)
