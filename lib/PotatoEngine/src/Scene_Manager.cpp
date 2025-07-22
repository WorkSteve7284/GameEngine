#include "Scene_Manager.hpp"
#include "Scene.hpp"

#include <memory>
#include <vector>

void Scene_Manager::Start() {
    for (auto& scene : scenes) {
        scene->Start();
    }
}

void Scene_Manager::Update(double delta_time) {
    for (auto& scene : scenes) {
        scene->Update(delta_time);
    }
}

void Scene_Manager::Fixed_Update(double delta_time) {
    for (auto& scene : scenes) {
        scene->Fixed_Update(delta_time);
    }
}

Scene& Scene_Manager::Add_Scene(std::string name) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    scene->UID = New_UID();
    scene->manager = this;
    scene->name = name;

    Scene& scene_ref = *scene;

    scenes.push_back(std::move(scene));

    scene_ref.Start();

    return scene_ref;
}

Scene& Scene_Manager::Add_Scene_No_Start(std::string name) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    scene->UID = New_UID();
    scene->manager = this;
    scene->name = name;

    Scene& scene_ref = *scene;

    scenes.push_back(std::move(scene));

    return scene_ref;
}

Scene& Scene_Manager::Find_Scene_With_Name(std::string name) {
    for (auto& scene : scenes) {
        if (scene->name == name) {
            return *scene;
        }
    }
    throw No_Scene_Found("No Scene with specified name found!");
}

Scene& Scene_Manager::Find_Scene_With_UID(long int UID) {
    for (auto& scene : scenes) {
        if (scene->UID == UID) {
            return *scene;
        }
    }
    throw No_Scene_Found("No Scene with specified UID found!");
}

Scene& Scene_Manager::Find_Scene(std::string name) {
    return Find_Scene_With_Name(name);
}

Scene& Scene_Manager::Find_Scene(long int UID) {
    return Find_Scene_With_UID(UID);
}