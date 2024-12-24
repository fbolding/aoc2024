# Get the name of the current directory (e.g., 'dayX')
get_filename_component(DAY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Specify the source file for this day's problem (e.g., 'dayX.cpp')
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Create an executable named 'dayX' from the source file
add_executable(${DAY_NAME} ${SOURCE_FILES})

# Link the 'util' library to this day's executable
target_link_libraries(${DAY_NAME} util)

# Copy input.txt and sample.txt to the build directory
add_custom_command(
    TARGET ${DAY_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/sample.txt
        $<TARGET_FILE_DIR:${DAY_NAME}>
)