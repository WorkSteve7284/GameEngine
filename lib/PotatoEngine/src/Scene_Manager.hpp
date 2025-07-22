#pragma once

#include "Scene.hpp"

#include <vector>
#include <memory>
#include <string>
#include <exception>

class No_Scene_Found : std::exception {
public:
    std::string message;

    No_Scene_Found(std::string msg) : message(msg) {};

    const char * what() const noexcept {
        return message.c_str();
    }
};

class Scene_Manager {
private:
    long int UID;

    std::vector<std::unique_ptr<Scene>> scenes;

public:

    ~Scene_Manager() = default;

    void Start();
    void Update(double delta_time);
    void Fixed_Update(double delta_time);

    Scene& Add_Scene(std::string name);

    Scene& Add_Scene_No_Start(std::string name);

    Scene& Find_Scene_With_Name(std::string name);

    Scene& Find_Scene_With_UID(long int UID);

    Scene& Find_Scene(std::string name);

    Scene& Find_Scene(long int UID);

    long int New_UID() {
        return ++UID;
    }
};