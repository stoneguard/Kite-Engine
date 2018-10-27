project (tools)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB PUBLIC_HEADERS 
"${CMAKE_SOURCE_DIR}/include/tools/*.h"
)

source_group("Sources" FILES ${SOURCES})
source_group("Headers" FILES ${HEADERS})

source_group("Public Headers" FILES ${PUBLIC_HEADERS})

include_directories(${GL3W_INCLUDE_PATH})
include_directories(${GLM_INCLUDE_PATH})
include_directories(${SOIL_INCLUDE_PATH})
include_directories(${ASSIMP_INCLUDE_PATH})
include_directories(${GLFW_INCLUDE_PATH})

add_library(tools SHARED ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})
set_target_properties(tools PROPERTIES DEBUG_POSTFIX "d")

target_link_libraries(tools ${SOIL_LIBRARY} ${ASSIMP_LIBRARY} ${GLFW_LIBRARY} gl3w)
  

