#include <sandbox_test.h>
#include <components/test_component.h>
#include <systems/test_system.h>

void SandboxTest::Init()
{
    World::ChangeWorld(World::Init());

    engine.RegisterComponents();
    Vultr::Engine::RegisterComponent<TestComponent>();

    engine.InitSystems();
    TestSystem::RegisterSystem();

    Entity camera = Entity::New();
    CameraComponent camera_component = CameraComponent::Create();
    camera.AddComponent(camera_component);
    camera.AddComponent(ControllerComponent::Create());

    camera.AddComponent(TransformComponent::Create(
        glm::vec3(0, 0, 0), glm::quat(1, 0, 0, 0), glm::vec3(5, 5, 5)));
    camera.AddComponent(SkyBoxComponent::Create(
        "default", "res/textures/skybox/front.jpg", "res/textures/skybox/back.jpg",
        "res/textures/skybox/top.jpg", "res/textures/skybox/bottom.jpg",
        "res/textures/skybox/left.jpg", "res/textures/skybox/right.jpg"));
    camera.AddComponent(Vultr::SkyboxMaterial::Create("default"));

    Entity light = Entity::New();

    light.AddComponent(LightComponent::Create());

    light.AddComponent(TransformComponent::Create(
        glm::vec3(0, 0, 30), glm::quat(1, 0, 0, 0), glm::vec3(4, 4, 4)));
    light.AddComponent(Vultr::UnlitMaterial::Create());

    Entity cube = Entity::New();
    cube.AddComponent(TransformComponent::Create(
        glm::vec3(0, 0, 60), glm::quat(1, 0, 0, 0), glm::vec3(1, 1, 1)));
    cube.AddComponent(StaticMeshComponent::Create());
    cube.AddComponent(
        Vultr::ForwardMaterial::Create("res/textures/cube/diffuse.png"));
}

void SandboxTest::Update(Vultr::UpdateTick tick)
{
    printf("%f ms\n", tick.m_delta_time);
}

void SandboxTest::Flush()
{
}

Game *init(Vultr::Engine &engine)
{
    return new SandboxTest(engine);
}
void flush(Game *game)
{
    delete game;
}