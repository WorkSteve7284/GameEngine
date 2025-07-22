#include "Object.hpp"
#include "Scene.hpp"
#include "Scene_Manager.hpp"

Scene::~Scene() { On_Destroy(); }

void Scene::Start() {
    for(auto& object : objects) {
        object->Start();
    }
}

void Scene::Update(double delta_time) {
    for(auto& object : objects) {
        object->Update(delta_time);
    }
}

void Scene::Fixed_Update(double delta_time) {
    for(auto& object : objects) {
        object->Fixed_Update(delta_time);
    }
}

// Add Objects
Object& Scene::Add_Object(std::string name) {
    std::unique_ptr<Object> object = std::make_unique<Object>();

    object->UID = manager->New_UID();
    object->scene = this;
    object->name = name;

    Object& object_ref = *object;

    objects.push_back(std::move(object));

    object_ref.Start();

    return object_ref;
}

Object& Scene::Add_Object_No_Start(std::string name) {
    std::unique_ptr<Object> object = std::make_unique<Object>();

    object->UID = manager->New_UID();
    object->scene = this;
    object->name = name;

    Object& object_ref = *object;

    objects.push_back(std::move(object));

    return object_ref;
}

// Find Objects
Object& Scene::Find_Object_With_Name(const std::string name) {
    for (auto& object : objects) {
        if ((*object).name == name) {
            return *object;
        }
    }
    throw No_Object_Found("No Object with specified name found!");
}

Object& Scene::Find_Object_With_UID(long int UID) {
    for (auto& object : objects) {
        if ((*object).UID == UID) {
            return *object;
        }
    }
    throw No_Object_Found("No Object with specified UID found!");
}

Object& Scene::Find_Object(const std::string name) {
    return Find_Object_With_Name(name);
}

Object& Scene::Find_Object(long int UID) {
    return Find_Object_With_UID(UID);
}
