file (GLOB_RECURSE FILES_GRAPH_BASIC "basic_operations/*.cpp")
file (GLOB_RECURSE FILES_GRAPH_EDGE "edge_operations/*.cpp")
file (GLOB_RECURSE FILES_GRAPH_OPER "operations/*.cpp")
file (GLOB_RECURSE FILES_GRAPH_VERT "vertex_operations/*.cpp")
file (GLOB_RECURSE FILES_GRAPH_FIND "finds/*.cpp")

add_library (graph_component OBJECT)
target_include_directories (graph_component PUBLIC ..)
target_sources (graph_component PRIVATE 
  ${FILES_GRAPH_BASIC}
  ${FILES_GRAPH_EDGE}
  ${FILES_GRAPH_OPER}
  ${FILES_GRAPH_VERT}
  ${FILES_GRAPH_FIND}
)
