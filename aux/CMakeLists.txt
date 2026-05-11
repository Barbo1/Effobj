add_executable (fin ./tests/polynomial/prueba_9.cpp)
target_include_directories (fin PRIVATE ..)
target_link_libraries (fin PRIVATE
  poly_component
  matrix_component
  operations_component
)
