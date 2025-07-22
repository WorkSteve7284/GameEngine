#pragma once

#include "PotatoEngine.h"

#include <memory>

#include "Test_Component.hpp"

void Create_Scenes(std::unique_ptr<Scene_Manager>& manager) {
    Scene& scene1 = manager->Add_Scene_No_Start("Scene 1");
    Object& object1 = scene1.Add_Object_No_Start("Object 1");
    Test_Component& component1 = object1.Add_Component_No_Start<Test_Component>();
}
