file(GLOB_RECURSE SRC_FILES "main.cpp" "vendor/imgui/*.cpp" "vendor/implot/*.cpp")

add_executable(example ${SRC_FILES})

target_include_directories(example PRIVATE vendor)

target_link_libraries(example PRIVATE MassSpringSystem -lglfw3 -lGLEW -lGL -ldl -lX11 -lpthread -lgmp)