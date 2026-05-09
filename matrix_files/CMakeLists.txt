file (GLOB_RECURSE FILES_MATRIX_INT_FLOAT "Xmatrixif.cpp")
file (GLOB_RECURSE FILES_MATRIX_FUNCTION "function_definition.cpp")
file (GLOB_RECURSE FILES_MATRIX_FLOAT "float/*.cpp")
file (GLOB_RECURSE FILES_MATRIX_BOOLEAN "boolean/*.cpp")
file (GLOB_RECURSE FILES_MATRIX_GENERIC "generic/*.cpp")

add_library (matrix_component OBJECT)
target_include_directories (matrix_component PUBLIC ..)
target_sources (matrix_component PRIVATE 
  ${FILES_MATRIX_FUNCTION} ${FILES_MATRIX_INT_FLOAT} ${FILES_MATRIX_FLOAT}
  ${FILES_MATRIX_BOOLEAN} ${FILES_MATRIX_GENERIC}
)
