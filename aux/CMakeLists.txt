add_executable (fin ./tests/polynomial/prueba_2.cpp)
target_include_directories (fin PRIVATE ..)
target_link_libraries (fin PRIVATE
  poly_components
  operations_component
)
