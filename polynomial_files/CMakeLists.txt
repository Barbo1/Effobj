file (GLOB_RECURSE FILES_PLOY_BASIC "basic_operations/*.cpp")
file (GLOB_RECURSE FILES_PLOY_BINARY "binary_operations/*.cpp")
file (GLOB_RECURSE FILES_PLOY_UNITARY "unitary_operations/*.cpp")

add_library (poly_component OBJECT)
target_include_directories (poly_component PUBLIC ..)
target_sources (poly_component PRIVATE 
  ${FILES_PLOY_BASIC} 
  ${FILES_PLOY_BINARY} 
  ${FILES_PLOY_UNITARY}
)
