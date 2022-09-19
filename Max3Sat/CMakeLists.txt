cmake_minimum_required (VERSION 3.0)
project ("Max3Sat" VERSION 1.0)
set_property(GLOBAL PROPERTY USE_FOLDERS On)

file(GLOB SOURCES "src/*")
file(GLOB INCLUDE "include/*")

source_group("include" FILES ${INCLUDE})
source_group("src" FILES ${SOURCES})

add_executable(max3sat
${SOURCES}
${INCLUDE}              # for visibility of header files in VS IDE
)

target_include_directories(max3sat PUBLIC include)
set_property(TARGET max3sat PROPERTY CXX_STANDARD 11)