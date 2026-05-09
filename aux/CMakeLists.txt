add_executable (fin ./proofs.cpp)
target_include_directories (fin PRIVATE ..)
target_link_libraries (fin PRIVATE
  fixmat_component
  operations_component
)
