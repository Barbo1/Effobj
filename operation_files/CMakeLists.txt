file (GLOB_RECURSE FILES_OPERATION_BIT "bit_functions/*.cpp")
file (GLOB_RECURSE FILES_OPERATION_MATH "math_functions/*.cpp")
file (GLOB_RECURSE FILES_OPERATION_SORT "sorting/*.cpp")
file (GLOB_RECURSE FILES_OPERATION_SUCCESSION "successions/*.cpp")

add_library (operations_component OBJECT)
target_include_directories (operations_component PUBLIC ..)
target_sources (operations_component PRIVATE 
  ${FILES_OPERATION_BIT} ${FILES_OPERATION_MATH} 
  ${FILES_OPERATION_SORT} ${FILES_OPERATION_SUCCESSION}
)
