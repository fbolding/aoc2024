# Collect all the source files in the util/src directory
file(GLOB UTIL_SOURCES "${CMAKE_SOURCE_DIR}/util/src/*.cpp")

# Create a static library named 'util' from the source files
add_library(util STATIC ${UTIL_SOURCES})

# Add the 'include' directory to the public include directories of the 'util' library
target_include_directories(util PUBLIC "${CMAKE_SOURCE_DIR}/util/include")