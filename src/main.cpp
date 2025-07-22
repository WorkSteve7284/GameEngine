#include "PotatoEngine.h"
#include "Scene-List.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <chrono>

int main()
{
    Debug.Log("Engine Starting...");
    
    std::unique_ptr<Scene_Manager> manager = std::make_unique<Scene_Manager>();
    
    Create_Scenes(manager);
    
    manager->Start();
    
    long double runtime = 0;
    
    auto last_update = std::chrono::steady_clock::now();
    auto last_fixed_update = std::chrono::steady_clock::now();
    auto last_iteration = std::chrono::steady_clock::now();
    
    while(runtime < 2.0) {
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::microseconds>(now - last_iteration).count() <= 10) {
            continue;
        }

        last_iteration = std::chrono::steady_clock::now();
        
        long double dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_update).count() * 1e-9;

        runtime += dt;
        
        manager->Update(dt);

        last_update = std::chrono::steady_clock::now();
        
        now = std::chrono::steady_clock::now();
        
        dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_fixed_update).count();

        if (dt >= 16666666.66) {
            last_fixed_update = std::chrono::steady_clock::now();

            manager->Fixed_Update(dt * 1e-9);
        }

        Debug.Log(std::to_string(runtime) + " seconds elapsed.");
    }

    Debug.Log("Engine Stopping After " + std::to_string(runtime) + " seconds.");
    
    return 0;
}
