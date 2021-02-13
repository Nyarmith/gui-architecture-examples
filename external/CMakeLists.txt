# gl loaders
add_subdirectory(glad)

# build glfw if not on system
if (NOT TARGET glfw)
    message(STATUS "GLFW 3.3 not found; using internal version")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    add_subdirectory(glfw)
endif()

# imgui proper
add_subdirectory(imgui)
