include(CMakeGenericSystem)

find_path(ZLIB_INCLUDE_DIR
  NAMES zlib.h
  HINTS
    "${CMAKE_GENERIC_PROGRAM_FILES}/zlib/include"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]/include"
  DOC "zlib (http://www.zlib.net.net)")

find_library(ZLIB_LIBRARY
  NAMES z zlib zlibd
  HINTS
    "${CMAKE_GENERIC_PROGRAM_FILES}/zlib/lib"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]/lib"
  DOC "zlib (http://www.zlib.net.net)")

mark_as_advanced(ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZLIB DEFAULT_MSG ZLIB_LIBRARY ZLIB_INCLUDE_DIR)
