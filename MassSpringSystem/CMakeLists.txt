file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(MassSpringSystem STATIC ${SOURCES})

target_include_directories(MassSpringSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)