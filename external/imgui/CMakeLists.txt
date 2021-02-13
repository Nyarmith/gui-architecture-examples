# collect all .cpp files
file(GLOB imgui_SRCS "*.cpp")
add_library(imgui)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
target_include_directories(imgui SYSTEM PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(imgui PRIVATE glad glfw)
target_sources(imgui PRIVATE ${imgui_SRCS})
