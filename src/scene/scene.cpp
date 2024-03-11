#include "scene.h"

Scene::Scene(unsigned int w, unsigned int h, Camera* camera) : scr_width_(w), scr_height_(h), camera_(camera)  {
    shader_res_ = std::make_unique<SShaderResource>();
    std::cout << "Shader resource created!" << std::endl;
    texture_res_ = std::make_unique<STextureResource>();
    std::cout << "Texture resource created!" << std::endl;
}

// Destructor traverses the scene and deletes all geometries, materials and meshes
Scene::~Scene() {
    #ifdef SANDBOX_DEBUG
        std::cout << "Scene is being destroyed!" << std::endl;
    #endif
    for(const auto& itr : game_objects_) {
        delete itr.second->GetMaterial();
        delete itr.second->GetGeometry();
        delete itr.second;
    }
}

void Scene::AddGameObject(Mesh* mesh, std::string name) {
    game_objects_[name] = mesh;
}
void Scene::AddLight(Mesh* mesh, std::string name) {
    lights_[name] = mesh;
}

void Scene::Init() {
    // Shaders
    auto cube_shader = shader_res_->AddResource("src/shaders/cube.vert", "src/shaders/cube.frag", nullptr, "cube");
    auto light_cube_shader = shader_res_->AddResource("src/shaders/light_cube.vert", "src/shaders/light_cube.frag", nullptr, "light_cube");
    auto floor_shader = shader_res_->AddResource("src/shaders/floor.vert", "src/shaders/floor.frag", nullptr, "floor");
    // Textures
    auto metal_albedo_tex = texture_res_->AddResource("assets/textures/metal/albedo.jpg", "metal_albedo", true);
    auto mario_tex = texture_res_->AddResource("assets/textures/misc/super-mario-world.jpg", "mario", true);
    auto sonic_tex = texture_res_->AddResource("assets/textures/misc/sonic.jpeg", "sonic", true);
    auto sand_tex = texture_res_->AddResource("assets/textures/sand/sand.jpg", "sand", true);


    // Cubes
    Material* cube_mat = new Material(cube_shader, std::string("cube"));
    UBufferGeometry* cube_geo = new UBufferGeometry(SANDBOX_CUBE);
    cube_geo->AddBufferAttribute("aNormal", 1, new BufferAtrribute(std::vector<float>(SANDBOX_CUBE_NORMAL_COORDS), 3));
    cube_geo->AddBufferAttribute("aTex_coord", 2, new BufferAtrribute(std::vector<float>(SANDBOX_CUBE_TEX_COORDS), 2));
    Mesh* cube = new Mesh(cube_mat, cube_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    cube_mat->SetColor(glm::vec3(0.3f, 0.9f, 1.0f));
    cube_mat->SetTexture(mario_tex);
    AddGameObject(cube, "cube");
    cube->SetPosition(glm::vec3(0.0f, 0.0f, -7.0f));
    cube->UpdateGeometry();

    // Light Cube
    Material* light_cube_mat = new Material(light_cube_shader, std::string("light_cube"));
    UBufferGeometry* light_cube_geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* light_cube = new Mesh(light_cube_mat, light_cube_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    light_cube_mat->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    AddLight(light_cube, "light_cube");
    light_cube->SetPosition(glm::vec3(-1.0f, 2.0f, -5.0f));
    light_cube->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));

    // Floor
    Material* floor_mat = new Material(floor_shader, std::string("floor"));
    UBufferGeometry* floor_geo = new UBufferGeometry(SANDBOX_SQUARE);
    floor_geo->AddBufferAttribute("normals", 1, new BufferAtrribute(std::vector<float>(SANDBOX_SQUARE_NORMAL_COORDS), 3));
    floor_geo->AddBufferAttribute("aTex_coord", 2, new BufferAtrribute(std::vector<float>(SANDBOX_SQUARE_TEX_COORDS), 2));
    floor_mat->SetColor(glm::vec3(0.6f, 0.6f, 0.6f)); 
    floor_mat->SetTexture(sand_tex);
    Mesh* floor = new Mesh(floor_mat, floor_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    AddGameObject(floor, "floor");
    floor->SetPosition(glm::vec3(0.0f, -0.55f, 0.0f));
    floor->SetScale(50.0f);
    floor->SetRotation(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    floor->UpdateGeometry();

}

void Scene::Render(float &delta_time) {
    // iterate through mesh repository, binding the VAO, 
    // using the appropriate shader program, and calling the appropraite draw call
    for(const auto& light : lights_) {
        auto light_mat = light.second->GetMaterial();
        light_mat->GetShaderMaterial()->Use();
        // Used for lighting - lightes need to know light sources are to calculate diffuse lighting
        light.second->UpdateUniforms(lights_["light_cube"]->GetMesh(), camera_->position_);
        light.second->Render();
    }
    for(const auto& mesh : game_objects_) {
        auto mesh_mat = mesh.second->GetMaterial();
        mesh_mat->GetShaderMaterial()->Use();
        // Used for lighting - meshes need to know light sources are to calculate diffuse lighting
        mesh.second->UpdateUniforms(lights_["light_cube"]->GetMesh(), camera_->position_);
        mesh.second->Render();
    }
}
