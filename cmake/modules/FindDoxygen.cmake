find_program(DOXYGEN_EXECUTABLE
  NAMES doxygen doxygen.exe
  HINTS
    "$ENV{ProgramFiles}/doxygen/bin"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\doxygen_is1;Inno Setup: App Path]/bin"
  DOC "Doxygen documentation generation tool (http://www.doxygen.org)")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Doxygen DEFAULT_MSG DOXYGEN_EXECUTABLE)

mark_as_advanced(DOXYGEN_EXECUTABLE)
