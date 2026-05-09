file (GLOB_RECURSE FILES_XPRES_VALSTR "validate_string_expresion.cpp")
file (GLOB_RECURSE FILES_XPRES_BASIC_IT "basic_iterator/*.cpp")
file (GLOB_RECURSE FILES_XPRES_BASIC_OP "basic_operations/*.cpp")
file (GLOB_RECURSE FILES_XPRES_EVAL "evaluation/*.cpp")
file (GLOB_RECURSE FILES_XPRES_MODIFY "modifications/*.cpp")
file (GLOB_RECURSE FILES_XPRES_NODE_MAN "node_manipulations/*.cpp")
file (GLOB_RECURSE FILES_XPRES_NODE_VAL "node_value/*.cpp")
file (GLOB_RECURSE FILES_XPRES_OPERATIONS "operations/*.cpp")
file (GLOB_RECURSE FILES_XPRES_PRINT "print/*.cpp")
file (GLOB_RECURSE FILES_XPRES_USEFUL_OP "useful_operations/*.cpp")

add_library (xpres_component OBJECT)
target_include_directories (xpres_component PUBLIC ..)
target_sources (xpres_component PRIVATE 
  ${FILES_XPRES_VALSTR}
  ${FILES_XPRES_BASIC_IT}
  ${FILES_XPRES_BASIC_OP}
  ${FILES_XPRES_EVAL}
  ${FILES_XPRES_MODIFY}
  ${FILES_XPRES_NODE_MAN}
  ${FILES_XPRES_NODE_VAL}
  ${FILES_XPRES_OPERATIONS}
  ${FILES_XPRES_PRINT}
  ${FILES_XPRES_USEFUL_OP}
)










