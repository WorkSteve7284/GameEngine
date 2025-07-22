#pragma once

#include "Component.hpp"
#include <vector>
#include <memory>
#include <exception>
#include <string>

class Scene;

class No_Component_Found : std::exception {
public:
    std::string message;

    No_Component_Found(std::string msg) : message(msg) {}

    const char * what() const noexcept{
        return (message.c_str());
    }
};

class Object {
private:
    std::vector<std::unique_ptr<Component>> components;

    void Assign_UID(Component* component);
public:
    std::string name;

    Scene* scene;

    long int UID;

    ~Object();

    void Start();

    void Update(double delta_time);

    void Fixed_Update(double delta_time);

    void On_Destroy() {}

    // Add Components
    template <typename T, typename... Args>
    T& Add_Component(Args&&... args) {
        std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);

        Assign_UID(component);
        component->object = this;

        T& component_ref = *component;

        components.push_back(std::move(component));

        component_ref.Start();
        
        return component_ref;
    }

    template <typename T, typename... Args>
    T& Add_Component_No_Start(Args&&... args) {

        std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
        
        Assign_UID(component.get());
        component->object = this;

        T& component_ref = *component;

        components.push_back(std::move(component));

        return component_ref;
    }

    // Find other components
    template <typename T>
    T& Find_Component_With_Type() {
        for (auto& component : components) {
            T* casted = dynamic_cast<T*>(component.get());
            if (casted) {
                return *casted;
            }
        }
        throw No_Component_Found("Component of requested type not found");
    }

    template <typename T>
    T& Find_Component_With_UID(long int UID) {
        for (auto& component : components) {
            if (component->UID == UID) {
                T* casted = dynamic_cast<T*>(component.get());
                if (casted) {
                    return *casted;
                }
            }
        }
        throw No_Component_Found("Component with requested UID not found");
    }

    template <typename T>
    T& Find_Component() {
        return Find_Component_With_Type<T>();
    }

    template <typename T>
    T& Find_Component(long int UID) {
        return Find_Component_With_UID<T>(UID);
    }
};
