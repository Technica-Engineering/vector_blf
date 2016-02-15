find_path(ZLIB_INCLUDE_DIRS
  NAMES zlib.h
  HINTS
    "$ENV{ProgramFiles}/zlib/include"
  DOC "zlib (http://www.zlib.net.net)")

find_library(ZLIB_LIBRARY
  NAMES z zdll
  HINTS
    "$ENV{ProgramFiles}/zlib/lib"
  DOC "zlib (http://www.zlib.net.net)")

mark_as_advanced(ZLIB_LIBRARY ZLIB_INCLUDE_DIRS)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZLIB DEFAULT_MSG ZLIB_LIBRARY ZLIB_INCLUDE_DIRS)
