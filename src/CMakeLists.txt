add_executable(imgui_sample imgui_sample.cc)
target_link_libraries(imgui_sample PRIVATE glfw OpenGL::GL glad imgui project_options project_warnings)
