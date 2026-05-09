file (GLOB_RECURSE FILES_RANDOM_VARIABLE "variable/*.cpp")
file (GLOB_RECURSE FILES_RANDOM_FIX "fixed/*.cpp")

add_library (random_component OBJECT)
target_include_directories (random_component PUBLIC ..)
target_sources (random_component PRIVATE 
  ${FILES_RANDOM_VARIABLE} ${FILES_RANDOM_FIX} 
)
