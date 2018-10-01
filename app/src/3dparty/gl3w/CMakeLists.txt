project (gl3w)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${GL3W_INCLUDE_PATH})

add_library(gl3w ${SOURCES} ${HEADERS})
set_target_properties(gl3w PROPERTIES DEBUG_POSTFIX "d")