
cmake_minimum_required(VERSION 2.6)

# --- PROJECT ---
project(SFUI)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# - Sources for TinyXML
file(
  GLOB_RECURSE
  tinyxml_src
  extlibs/TinyXML/*
)

# - Sources for SFUI
file(
  GLOB_RECURSE
  sfui_src
  src/*.cpp
  include/*.hpp
)


# - Include dir
include_directories(extlibs)
include_directories(include)

# - External links
link_directories(lib)

# - Libraries
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

# - Linker
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

#  --- DEMOS ---

set(CMAKE_SAMPLES_DIR "samples")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SAMPLES_DIR}/bin)

set(demo_names

  "1_Init"
  "2_FirstWidget"
  "3_BasicWidgets"
)

foreach(demo ${demo_names})

  set(demo_path ${CMAKE_SAMPLES_DIR}/${demo})

  file(
    GLOB
    demo_src
    ${demo_path}/*.cpp
    ${demo_path}/*.hpp
  )

  add_executable(
    ${demo}
    ${demo_src}
  ) 

  target_link_libraries(
    ${demo}
    sfui
    sfml-graphics
    sfml-window
    sfml-system
  )

endforeach()

#  --- INSTALL PART ---

# - libraries
install(TARGETS sfui sfui-s
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

# - headers for development
file(
  GLOB_RECURSE
  sfui_headers
  include/SFUI/*.hpp
)

install(FILES include/SFUI.hpp DESTINATION include)
install(FILES ${sfui_headers} DESTINATION include/SFUI/)

