#include <Vultr.hpp>
#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <core/component_renderer.h>
#include <gui/framework/basic.h>
#include <gui/layouts/test_layout.h>

void *LoadDLL(const std::string &path)
{
#ifdef _WIN32
    return LoadLibrary(path.c_str());
#else
    return dlopen(path.c_str(), RTLD_NOW);
#endif
}

void *GetFunctionPointer(void *dll, const std::string &name)
{
#ifdef _WIN32
    return GetProcAddress((HMODULE)dll, name.c_str());
#else
    return dlsym(dll, name.c_str());
#endif
}

namespace Vultr
{

void Engine::Init(bool debug)
{
    if (!glfwInit())
    {

        printf("Failed to initialize glfw\n");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#ifndef _WIN32
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (debug)
    {
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    }
#ifdef _WIN32
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    this->window =
        glfwCreateWindow(mode->width, mode->height, "VultrEditor", nullptr, nullptr);
#else
    this->window =
        glfwCreateWindow(mode->width, mode->height, "VultrEditor", nullptr, nullptr);
#endif

    if (window == nullptr)
    {
        printf("Failed to initialize glfw window\n");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize glad\n");
        return;
    }

    this->debug = debug;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(ErrorHandler::ErrorCallback, 0);
    if (debug)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable
        // Multi - Viewport /
        // Platform Windows
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
        ImGui::StyleColorsDark();
    }
}

void Engine::RegisterComponents()
{
    World::RegisterComponent<StaticMeshComponent>();
    World::RegisterComponent<MaterialComponent>(false);
    World::RegisterComponent<TransformComponent>();
    World::RegisterComponent<LightComponent>();
    World::RegisterComponent<CameraComponent>();
    World::RegisterComponent<ControllerComponent>();
    World::RegisterComponent<SkyBoxComponent>();
}

void Engine::InitSystems()
{

    MeshLoaderSystem::RegisterSystem();
    ShaderLoaderSystem::RegisterSystem();
    TextureLoaderSystem::RegisterSystem();
    ControllerSystem::RegisterSystem();
    CameraSystem::RegisterSystem();
    LightSystem::RegisterSystem();
    RenderSystem::RegisterSystem();
    GUISystem::RegisterSystem();
    InputSystem::RegisterSystem();
    FontSystem::RegisterSystem();
    FontSystem::Init();
    InputSystem::Init(window);

    ControllerSystem::Init(window);
    glfwSetWindowFocusCallback(window, ControllerSystem::WindowFocusCallback);

    glm::vec2 dimensions = RenderSystemProvider::GetDimensions(GAME);
    GUISystem::Init(TestLayout());
}

void Engine::LoadGame(const std::string &path)
{
    void *DLL = LoadDLL(path);

    typedef Game *(*GameInit_f)(Engine *);
    typedef void (*GameDestroy_f)(Game *);
    GameInit_f init = (GameInit_f)GetFunctionPointer(DLL, "init");
    GameDestroy_f destroy = (GameDestroy_f)GetFunctionPointer(DLL, "flush");

    game = init(this);
    game->Init();
}
void Engine::LoadGame(Game *p_game)
{
    game = p_game;
    game->Init();
}

void Engine::UpdateGame(float &last_time)
{
    should_close = glfwWindowShouldClose(window);

    float t = glfwGetTime();
    float deltaTime = t - last_time;
    last_time = t;
    UpdateTick tick = UpdateTick(deltaTime, this->debug);

    if (game != nullptr)
        game->Update(tick);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Only continuously update the meshes if we are planning on changing these
    // components at random (really will only happen in the editor)
    // If you need to change these components at runtime, destroy and then readd the
    // components
    if (debug)
    {
        ShaderLoaderSystem::Update();
        TextureLoaderSystem::Update();
        MeshLoaderSystem::Update();
        ControllerSystem::Update(tick.m_delta_time);
    }
    InputSystem::Update();
    RenderSystem::Update(tick);
    glfwPollEvents();
}

double Engine::GetElapsedTime()
{
    return glfwGetTime();
}

void Engine::Destroy()
{
}
} // namespace Vultr
