
#pragma once

#include "Object.hpp"

#include <vector>
#include <memory>
#include <string>
#include <exception>

class Scene_Manager;

class No_Object_Found : std::exception {
public:
    std::string message;

    No_Object_Found(std::string msg) : message(msg) {}

    const char * what() const noexcept {
        return message.c_str();
    }
};

class Scene {
private:
    std::vector<std::unique_ptr<Object>> objects;
public:

    Scene_Manager* manager;

    long int UID;

    std::string name;

    ~Scene();

    void Start();
    void Update(double delta_time);
    void Fixed_Update(double delta_time);

    void On_Destroy() {}

    // Add Objects
    Object& Add_Object(std::string name);

    Object& Add_Object_No_Start(std::string name);

    // Find Objects
    Object& Find_Object_With_Name(const std::string name);

    Object& Find_Object_With_UID(long int UID);

    Object& Find_Object(const std::string name);

    Object& Find_Object(long int UID);
};
