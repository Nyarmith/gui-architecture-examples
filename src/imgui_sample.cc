#include <glad/glad.h>
#include <imgui.h>
#include <imfilebrowser.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <iostream>

constexpr unsigned int VIEWER_WIDTH = 800;
constexpr unsigned int VIEWER_HEIGHT = 600;


void draw_stuff()
{
    static bool pressed = false;
    ImGui::Text("Hello lassies!");
    pressed = pressed || ImGui::Button("Do NOT Press!");
    if (pressed) ImGui::Text("I told you bro, I warned you!");
}

static void glfw_error_callback(int error, const char* description)
{
        std::cerr << "GLFW error: " << error << ", " << description << std::endl;
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw\n";
        return -1;
    }

    // direct opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *displayWin = glfwCreateWindow(VIEWER_WIDTH, VIEWER_HEIGHT, "Cam View", NULL, NULL);
    if (!displayWin)
    {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
    }

    glfwMakeContextCurrent(displayWin);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwTerminate();
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cerr << "OpenGL version from glad: " << GLVersion.major << "." << GLVersion.minor << "\n";

    // init - imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    ImGui::StyleColorsDark();
    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    // ImGuiStyle& style = ImGui::GetStyle();

    // Imgui - setup platform and renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(displayWin, true);
    ImGui_ImplOpenGL3_Init("#version 150"); //3.2 glsl

    // render loop
    while (!glfwWindowShouldClose(displayWin))
    {
        //poll events
        glfwPollEvents();

        // Start new imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        draw_stuff();

        // Render
        ImGui::Render();

        if (io.KeysDown[256]) // escape key
            glfwSetWindowShouldClose(displayWin, GLFW_TRUE);

        // see if window size changed
        int display_w, display_h;
        glfwGetFramebufferSize(displayWin, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(displayWin);
    }

    // shutdown - imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    
    return 0;
}
