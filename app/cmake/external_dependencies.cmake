set(cl_ver "vc140")

 if(WIN32) 
   set(os "win")
else()
   set(os "nix")
endif()

message("Searching for external dependecies ...")

#gl3w
find_path(GL3W_INCLUDE_PATH GL/gl3w.h PATHS "${CMAKE_SOURCE_DIR}/../sdk/gl3w/include")
#message("gl3w INCLUDE PATH - ${GL3W_INCLUDE_PATH}")
#if("${GL3W_INCLUDE_PATH}" STREQUAL "")
if(DEFINED GL3W_INCLUDE_PATH)
   message(STATUS "gl3w      [+]")
else()
   message(STATUS "gl3w      [-]")
endif()

#glm
set(GLM_VERSION 0.9.8.5)
find_path(GLM_INCLUDE_PATH glm/glm.hpp PATHS "${CMAKE_SOURCE_DIR}/../sdk/glm-${GLM_VERSION}/include")
#message("GLM INCLUDE PATH - ${GLM_INCLUDE_PATH}")
#if("${GLM_INCLUDE_PATH}" STREQUAL "")
if(DEFINED GLM_INCLUDE_PATH)
   message(STATUS "glm       [+]")
else()
   message(STATUS "glm       [-]")
endif()

#assimp
set(ASSIMP_VERSION 3.3.1)
find_path(ASSIMP_INCLUDE_PATH assimp/version.h PATHS "${CMAKE_SOURCE_DIR}/../sdk/assimp-${ASSIMP_VERSION}/include")
#debug lib
find_library(ASSIMP_LIBRARY_DEBUG NAMES "assimp-${cl_ver}-mt" PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/assimp-${ASSIMP_VERSION}/lib/${os}/debug")
 
#releae lib
find_library(ASSIMP_LIBRARY_REL NAMES "assimp-${cl_ver}-mt" PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/assimp-${ASSIMP_VERSION}/lib/${os}/release")
 
get_filename_component(ASSIMP_LIBRARY_PATH ${ASSIMP_LIBRARY_DEBUG} DIRECTORY) 

#message("ASSIMP INCLUDE PATH - ${GLM_INCLUDE_PATH}")
#message("ASSIMP LIBRARY PATH DBG - ${ASSIMP_LIBRARY_DEBUG}")
#message("ASSIMP LIBRARY PATH REL - ${ASSIMP_LIBRARY_REL}")
 
if(DEFINED GLM_INCLUDE_PATH AND DEFINED ASSIMP_LIBRARY_DEBUG AND DEFINED ASSIMP_LIBRARY_REL)
   message(STATUS "assimp    [+]")
else()                       
   message(STATUS "assimp    [-]")
endif()

#pugixml
set(PUGIXML_VERSION 1.9)
find_path(PUGIXML_INCLUDE_PATH pugixml.hpp PATHS "${CMAKE_SOURCE_DIR}/../sdk/pugixml-${PUGIXML_VERSION}/include")
#debug lib
find_library(PUGIXML_LIBRARY_DEBUG NAMES pugixml PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/pugixml-${PUGIXML_VERSION}/lib/${os}/debug")
 
#releae lib
find_library(PUGIXML_LIBRARY_REL NAMES pugixml PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/pugixml-${PUGIXML_VERSION}/lib/${os}/release")
 
#message("PUGIXML INCLUDE PATH - ${PUGIXML_INCLUDE_PATH}")
#message("PUGIXML LIBRARY PATH DBG - ${PUGIXML_LIBRARY_DEBUG}")
#message("PUGIXML LIBRARY PATH REL - ${PUGIXML_LIBRARY_REL}")

if(DEFINED PUGIXML_INCLUDE_PATH AND DEFINED PUGIXML_LIBRARY_DEBUG AND DEFINED PUGIXML_LIBRARY_REL)
   message(STATUS "pugixml   [+]")
else()
   message(STATUS "pugixml   [-]")
endif()

#SOIL - Simple OpenGL Image Library
set(SOIL_VERSION 1.16)
find_path(SOIL_INCLUDE_PATH SOIL.h PATHS "${CMAKE_SOURCE_DIR}/../sdk/soil-${SOIL_VERSION}/include")
#debug lib
find_library(SOIL_LIBRARY_DEBUG NAMES SOIL PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/soil-${SOIL_VERSION}/lib/${os}/debug")
 
#releae lib
find_library(SOIL_LIBRARY_REL NAMES SOIL PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/soil-${SOIL_VERSION}/lib/${os}/release")
 
#message("SOIL INCLUDE PATH - ${SOIL_INCLUDE_PATH}")
#message("SOIL LIBRARY PATH DBG - ${SOIL_LIBRARY_DEBUG}")
#message("SOIL LIBRARY PATH REL - ${SOIL_LIBRARY_REL}")

if(DEFINED SOIL_INCLUDE_PATH AND DEFINED SOIL_LIBRARY_DEBUG AND DEFINED SOIL_LIBRARY_REL)
   message(STATUS "SOIL      [+]")
else()                       
   message(STATUS "SOIL      [-")
endif()

#glfw - opengl windows & context
set(GLFW_VERSION 3.2.1)
find_path(GLFW_INCLUDE_PATH GLFW/glfw3.h PATHS "${CMAKE_SOURCE_DIR}/../sdk/glfw-${GLFW_VERSION}/include")
#debug lib
find_library(GLFW_LIBRARY_DEBUG NAMES glfw3 PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/glfw-${GLFW_VERSION}/lib/${os}/debug")
 
#releae lib
find_library(GLFW_LIBRARY_REL NAMES glfw3 PATHS
 "${CMAKE_SOURCE_DIR}/../sdk/glfw-${GLFW_VERSION}/lib/${os}/release")
 
#message("GLFW INCLUDE PATH - ${GLFW_INCLUDE_PATH}")
#message("GLFW LIBRARY PATH DBG - ${GLFW_LIBRARY_DEBUG}")
#message("GLFW LIBRARY PATH REL - ${GLFW_LIBRARY_REL}")

if(DEFINED GLFW_INCLUDE_PATH AND DEFINED GLFW_LIBRARY_DEBUG AND DEFINED GLFW_LIBRARY_REL)
   message(STATUS "glfw      [+]")
else()                       
   message(STATUS "glfw      [-")
endif()

#glew - replacement for gl3w
#set(GLFW_VERSION 3.2.1)
#find_path(GLFW_INCLUDE_PATH GLFW/glfw3.h PATHS "${CMAKE_SOURCE_DIR}/../sdk/glfw-${GLFW_VERSION}/include")
##debug lib
#find_library(GLFW_LIBRARY_DEBUG NAMES glfw3 PATHS
# "${CMAKE_SOURCE_DIR}/../sdk/glfw-${GLFW_VERSION}/lib/${os}/debug")
# 
##releae lib
#find_library(GLFW_LIBRARY_REL NAMES glfw3 PATHS
# "${CMAKE_SOURCE_DIR}/../sdk/glfw-${GLFW_VERSION}/lib/${os}/release")
# 
##message("GLFW INCLUDE PATH - ${GLFW_INCLUDE_PATH}")
##message("GLFW LIBRARY PATH DBG - ${GLFW_LIBRARY_DEBUG}")
##message("GLFW LIBRARY PATH REL - ${GLFW_LIBRARY_REL}")
#
#if(DEFINED GLFW_INCLUDE_PATH AND DEFINED GLFW_LIBRARY_DEBUG AND DEFINED GLFW_LIBRARY_REL)
#   message(STATUS "glfw      [+]")
#else()                       
#   message(STATUS "glfw      [-")
#endif()
