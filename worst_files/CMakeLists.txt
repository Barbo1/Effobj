file (GLOB_RECURSE FILES_WORST_BASIC_IT "basic_iterator/*.cpp")
file (GLOB_RECURSE FILES_WORST_BASIC_OP "basic_operations/*.cpp")
file (GLOB_RECURSE FILES_WORST_BINARY "binary_operations/*.cpp")
file (GLOB_RECURSE FILES_WORST_UNITARY "unitary_operations/*.cpp")
file (GLOB_RECURSE FILES_WORST_NODE "node_manipulation/*.cpp")

add_library (worst_component OBJECT)
target_include_directories (worst_component PUBLIC ..)
target_sources (worst_component PRIVATE 
  ${FILES_WORST_BASIC_IT}
  ${FILES_WORST_BASIC_OP}
  ${FILES_WORST_BINARY}
  ${FILES_WORST_UNITARY}
  ${FILES_WORST_NODE}
)
