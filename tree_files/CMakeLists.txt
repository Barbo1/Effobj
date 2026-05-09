file (GLOB_RECURSE FILES_AVL "avl_tree/*.cpp")

add_library (trees_component OBJECT)
target_include_directories (trees_component PUBLIC ..)
target_sources (trees_component PRIVATE ${FILES_AVL})
