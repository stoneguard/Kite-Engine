project (game)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_executable(game ${SOURCES} ${HEADERS})

target_link_libraries (game tools)