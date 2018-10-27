set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" )
# default configurations postfix
set(CMAKE_DEBUG_POSTFIX   "-debug")
set(CMAKE_RELEASE_POSTFIX "")

set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS Debug) 

project(kite)

cmake_minimum_required(VERSION 3.10)
set (kite_VERSION_MAJOR 1)
set (kite_VERSION_MINOR 0)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/external_dependencies.cmake)

include_directories(include)

add_subdirectory(src/kite)    
add_subdirectory(src/tools)
add_subdirectory(src/engine)     
add_subdirectory(src/3dparty/gl3w)

if(CMAKE_SIZEOF_VOID_P GREATER 4)
  set(Arg amd64)
else()
  set(Arg x84)
endif()

file(
  WRITE ${CMAKE_BINARY_DIR}/kite.bat
  "@echo off\n"
  "call \"%vs140comntools%/vsvars32.bat\"\n"
  "set PATH=${ASSIMP_LIBRARY_PATH};%PATH%\n"
  "start devenv.exe kite.sln\n"
)    
