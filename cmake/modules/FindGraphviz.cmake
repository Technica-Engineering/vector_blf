find_program(GRAPHVIZ_DOT_EXECUTABLE
  NAMES dot dot.exe
  PATHS
    "$ENV{ProgramFiles}/Graphviz/bin"
    "C:/Program Files/Graphviz/bin"
    "$ENV{ProgramFiles}/ATT/Graphviz/bin"
    "C:/Program Files/ATT/Graphviz/bin"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\ATT\\Graphviz;InstallPath]/bin"
  DOC "Graphviz Dot tool for using Doxygen")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Graphviz_dot DEFAULT_MSG GRAPHVIZ_DOT_EXECUTABLE)
get_filename_component(GRAPHVIZ_DOT_PATH "${GRAPHVIZ_DOT_EXECUTABLE}" PATH CACHE)

mark_as_advanced(
  GRAPHVIZ_DOT_EXECUTABLE
  GRAPHVIZ_DOT_PATH)
