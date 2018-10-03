project (engine)

#private
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB PUBLIC_HEADERS 
"${CMAKE_SOURCE_DIR}/include/engine/*.h"
)

##entities
file(GLOB SHARED_ENTITIES_IFC_HEADERS "entities/ifc/*.h")

#camera
file(GLOB CAMERA_SOURCES "camera/*.cpp")
file(GLOB CAMERA_HEADERS "camera/*.h")

source_group("Headers\\entities\\ifc" FILES ${SHARED_ENTITIES_IFC_HEADERS})

source_group("Sources\\camera" FILES ${CAMERA_SOURCES})
source_group("Headers\\camera" FILES ${CAMERA_HEADERS})

include_directories(${GLM_INCLUDE_PATH})
include_directories(${GL3W_INCLUDE_PATH})
include_directories(${GLFW_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ASSIMP_INCLUDE_PATH})
include_directories(${PUGIXML_INCLUDE_PATH})
include_directories(${SOIL_INCLUDE_PATH})

add_library(engine SHARED 
${SOURCES} ${HEADERS} 
${PUBLIC_HEADERS} 
${SHARED_ENTITIES_IFC_HEADERS}
${CAMERA_SOURCES} ${CAMERA_HEADERS}
)
set_target_properties(tools PROPERTIES DEBUG_POSTFIX "d")

target_link_libraries (engine tools ${ASSIMP_LIBRARY_DEBUG} ${GLFW_LIBRARY_DEBUG} ${PUGIXML_LIBRARY_DEBUG} ${SOIL_LIBRARY_DEBUG} gl3w)