#pragma once

class Object;

class Component {
public:
    long int UID;

    Object* object;

    ~Component() {On_Destroy();}
    virtual void Start() {}
    virtual void Update(double delta_time) {}
    virtual void Fixed_Update(double delta_time) {}
    virtual void On_Destroy() {}
};
