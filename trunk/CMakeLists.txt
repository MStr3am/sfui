
cmake_minimum_required(VERSION 2.6)

# Project configuration
project(SFUI)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# Sources for TinyXML
file(
  GLOB_RECURSE
  tinyxml_src
  extlibs/TinyXML/*
)

# Sources for SFUI
file(
  GLOB_RECURSE
  sfui_src
  src/*.cpp
  include/*.hpp
)

# Include dir
include_directories(extlibs)
include_directories(include)

# External links
link_directories(lib)

add_library(
  TinyXML
  STATIC
  ${tinyxml_src}
)

add_library(
  sfui-s
  STATIC
  ${sfui_src}
)

add_library(
  sfui
  SHARED
  ${sfui_src}
)

target_link_libraries(
  sfui-s
  TinyXML
  sfml-graphics
  sfml-window
  sfml-system
)

target_link_libraries(
  sfui
  TinyXML
  sfml-graphics
  sfml-window
  sfml-system
)


# Install part
install(TARGETS sfui sfui-s
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)



