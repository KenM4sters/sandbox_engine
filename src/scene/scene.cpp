#include "scene.h"
std::vector<float> skybox_vertices = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

Scene::Scene(unsigned int w, unsigned int h, Camera* camera, CollisionHandler* collision_handler) 
    : scr_width_(w), scr_height_(h), camera_(camera), collision_handler_(collision_handler)  
{
    lights_res_ = new SLights(&shader_res_, &texture_res_, collision_handler_);
    std::cout << "Lights resource created!" << std::endl;
}
void Scene::SetCameraData(Camera* camera) {
    for(auto& shader : shader_res_.GetAllResources()) {
        glm::mat4 projection = glm::perspective(camera_->zoom_, (float)scr_width_ / (float)scr_height_, 0.1f, 10000.0f);
        shader.second->Use();
        shader.second->setMat4("projection", projection);
        shader.second->setVector3f("camera_pos", camera_->position_);
        glm::mat4 view = camera_->GetViewMatrix();
        if(shader.first == "terrain_grass") {   
            shader.second->setMat4("view", view);
        } else {
            shader.second->setMat4("view", view);
        }
    }
}

void Scene::Init() {
    // Loading ALL shaders
    auto cube_shader = shader_res_.AddResource("src/shaders/cube.vert", "src/shaders/cube.frag", nullptr, "cube", SANDBOX_OBJECT);
    auto floor_shader = shader_res_.AddResource("src/shaders/floor.vert", "src/shaders/floor.frag", nullptr, "floor", SANDBOX_OBJECT);
    auto skybox_shader = shader_res_.AddResource("src/shaders/skybox.vert", "src/shaders/skybox.frag", nullptr, "skybox", SANDBOX_OBJECT);
    auto sky_sphere_shader = shader_res_.AddResource("src/shaders/sky_sphere.vert", "src/shaders/sky_sphere.frag", nullptr, "sky_sphere", SANDBOX_OBJECT);
    auto light_cube_shader = shader_res_.AddResource("src/shaders/light_cube.vert", "src/shaders/light_cube.frag", nullptr, "light_cube", SANDBOX_LIGHT);
    auto back_pack_shader = shader_res_.AddResource("src/shaders/model.vert", "src/shaders/model.frag", nullptr, "model", SANDBOX_OBJECT);
    auto terrain_shader = shader_res_.AddResource("src/shaders/terrain.vert", "src/shaders/terrain.frag", nullptr, "terrain", SANDBOX_OBJECT);
    auto terrain_scenery_shader = shader_res_.AddResource("src/shaders/terrain_grass.vert", "src/shaders/terrain_grass.frag", nullptr, "terrain_grass", SANDBOX_OBJECT);
    auto bounding_box_shader = shader_res_.AddResource("src/shaders/bounding_box.vert", "src/shaders/bounding_box.frag", nullptr, "bounding_box", SANDBOX_OBJECT);
    // Loading ALL textures
    auto mario_tex = texture_res_.AddResource("assets/textures/misc/super-mario-world.jpg", "mario", SANDBOX_OBJECT, "diffuse");
    auto sand_tex = texture_res_.AddResource("assets/textures/sand/sand.jpg", "sand", SANDBOX_OBJECT, "diffuse");
    auto light_cube_tex = texture_res_.AddResource("assets/textures/misc/glowstone.png", "glowstone", SANDBOX_LIGHT, "diffuse");
    auto sonic_tex = texture_res_.AddResource("assets/textures/misc/sonic.jpeg", "sonic", SANDBOX_OBJECT, "test");
    auto terrain_tex_forest = texture_res_.AddResource("assets/textures/terrain/light_grass.jpg", "terrain_middle", SANDBOX_OBJECT, "diffuse_middle");
    auto terrain_tex_salt = texture_res_.AddResource("assets/textures/terrain/red_rock.jpg", "terrain_top", SANDBOX_OBJECT, "diffuse_top");
    auto terrain_tex_rock = texture_res_.AddResource("assets/textures/terrain/forest_floor.jpg", "terrain_bottom", SANDBOX_OBJECT, "diffuse_bottom");
    auto terrain_tex_grass = texture_res_.AddResource("assets/textures/terrain/grass.png", "terrain_grass", SANDBOX_OBJECT, "diffuse_grass");
    auto terrain_tex_wild_flower = texture_res_.AddResource("assets/textures/terrain/wild_flower.png", "terrain_wild_flower", SANDBOX_OBJECT, "diffuse_wild_flower");

    // Skybox - texture loading is different for this, so it's abstracted away into dealing with all
    // of its shaders/textures for itself.
    std::vector<std::string> skybox_textures = {
        "assets/textures/skybox/rainbow_rt.png",    
        "assets/textures/skybox/rainbow_lf.png",    
        "assets/textures/skybox/rainbow_up.png",    
        "assets/textures/skybox/rainbow_dn.png",    
        "assets/textures/skybox/rainbow_bk.png",
        "assets/textures/skybox/rainbow_ft.png",   
    };
    skybox_ = new Skybox(skybox_vertices, skybox_textures, skybox_shader, camera_);
    // When we loaded the skybox, we set the textures to not be flipped on load since we weren't using
    // tex_coords in the traditional way, but we need to make sure that we set it back to true when
    // we want to load any other textures.
    stbi_set_flip_vertically_on_load(true);
    lights_res_->Init();

    // All shaders were passed to the lights so that they can set their uniform data to those shaders
    // themselves, but we only need the object-specific ones to go to our objects rendering system,
    // so we call a function that loops through them and returns an SShaderResource pointer to the ones
    // that the objects need.
    SShaderResource* objects_shaders = lights_res_->SetLightData();
    objects_res_ = new SObjects(objects_shaders, &texture_res_, collision_handler_);

    // Terrain
    std::vector<Texture2D*> ground_textures = {
        terrain_tex_forest,
        terrain_tex_salt,
        terrain_tex_rock
    };
    std::vector<Texture2D*> scenery_textures = {
        terrain_tex_grass,
        terrain_tex_wild_flower
    };
    Material terrain_ground_mat = {
        glm::vec3(0.4f),
        ground_textures,
        glm::vec3(0.0f),
        1.0f
    };
    Material terrain_scenery_mat = {
        glm::vec3(1.0f),
        scenery_textures,
        glm::vec3(1.0f),
        4.0f
    };
    unsigned int scale = 40; // sets a uniform scale and the terrain size
    terrain_ = new Terrain("assets/textures/terrain/height_map.png", terrain_shader, terrain_ground_mat, scale);
    terrain_->GenerateScenary(terrain_scenery_shader, terrain_scenery_mat);
    collision_handler_->FeedTerrain(terrain_);
}

void Scene::Render(float &delta_time) {
    SetCameraData(camera_);
    lights_res_->Draw(delta_time);
    lights_res_->UpdateLights();
    objects_res_->Draw(delta_time);
    terrain_->DrawTerrain(delta_time);
    // Render Skybox - more efficient to draw it last so that any parts of the cube that are
    // blocked by other game objects will be discared.
    glDepthFunc(GL_LEQUAL);
    skybox_->DrawCube();
    glDepthFunc(GL_LESS);
}
