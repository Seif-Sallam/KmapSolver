cmake_minimum_required(VERSION 3.16)

FILE(GLOB_RECURSE SOURCES ./src/*.cpp)

FILE(GLOB_RECURSE HEADERS ./headers/*.h)

add_executable(
    KMapSolver
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    KMapSolver
    PRIVATE
    ./headers/
)

target_link_libraries(KMapSolver
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_compile_definitions(KMapSolver
    PRIVATE
    RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)