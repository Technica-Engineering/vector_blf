find_path(ZLIB_INCLUDE_DIR
  NAMES zlib.h
  PATHS
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
    "$ENV{PROGRAMFILES}/zlib"
  PATH_SUFFIXES include
  DOC "zlib (http://www.zlib.net.net)")

find_library(ZLIB_LIBRARY
  NAMES z zlib zlibd
  PATHS
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
    "$ENV{PROGRAMFILES}/zlib"
  PATH_SUFFIXES lib
  DOC "zlib (http://www.zlib.net.net)")

mark_as_advanced(ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZLIB DEFAULT_MSG ZLIB_LIBRARY ZLIB_INCLUDE_DIR)
