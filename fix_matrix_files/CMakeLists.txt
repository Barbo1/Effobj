file (GLOB_RECURSE FILES_FIXMAT_BASIC "basic_operations/*.cpp")
file (GLOB_RECURSE FILES_FIXMAT_BINARY "binary_operations/*.cpp")
file (GLOB_RECURSE FILES_FIXMAT_UNITARY "unitary_operations/*.cpp")
file (GLOB_RECURSE FILES_FIXMAT_INFO "information/*.cpp")
file (GLOB_RECURSE FILES_FIXMAT_MANI "manipulation/*.cpp")

add_library (fixmat_component OBJECT)
target_include_directories (fixmat_component PUBLIC ..)
target_sources (fixmat_component PRIVATE 
  ${FILES_FIXMAT_INFO}
  ${FILES_FIXMAT_MANI}
  ${FILES_FIXMAT_UNITARY}
  ${FILES_FIXMAT_BASIC}
  ${FILES_FIXMAT_BINARY}
)
