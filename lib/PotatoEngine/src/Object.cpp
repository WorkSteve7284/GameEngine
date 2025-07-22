#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"
#include "Scene_Manager.hpp"

#include <type_traits>

Object::~Object() {On_Destroy();}

void Object::Start() {
    for (auto& component : components) {
        component->Start();
    }
}

void Object::Update(double delta_time) {
    for (auto& component : components) {
        component->Update(delta_time);
    }
}

void Object::Fixed_Update(double delta_time) {
    for (auto& component : components) {
        component->Fixed_Update(delta_time);
    }
}

void Object::Assign_UID(Component* component) {
    component->UID = scene->manager->New_UID();
}
