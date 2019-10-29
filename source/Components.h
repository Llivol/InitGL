
#pragma once
#include "includes.h"
#include "Texture.h"
#include <vector>
#include <tuple>

/**** COMPONENTS ****/

//Component (base class)
// - owner: id of Entity which owns the instance of the component
struct Component
{
    int owner;
};

struct Transform : public Component, public lm::mat4
{
    //     int parent = -1;
    //     lm::mat4 getGlobalMatrix(std::vector<Transform> &transforms)
    //     {
    //         if (parent != -1)
    //         { // if I have a model matrix parent
    //             // multiply this model by all of its parents
    //             // to access in a vector:
    //             // transforms[i]
    //             // transforms.at(i)
    //             return transforms.at(parent).getGlobalMatrix(transforms) * *this;
    //         }
    //         else
    //         {
    //             return *this; // this returns the copy of the memory, NOT the address
    //         }
    //     }
};

struct Mesh : public Component
{
    // TODO fill in mesh data
};

typedef std::tuple<
    std::vector<Transform>,
    std::vector<Mesh>>
    ComponentArrays;

const int NUM_TYPE_COMPONENTS = 2;
/**** ENTITY ****/

struct Entity
{
    std::string name;
    bool active = true;
    int components[NUM_TYPE_COMPONENTS];
    Entity()
    {
        for (int i = 0; i < NUM_TYPE_COMPONENTS; i++)
        {
            components[i] = -1;
        }
    }
    Entity(std::string a_name) : name(a_name)
    {
        for (int i = 0; i < NUM_TYPE_COMPONENTS; i++)
        {
            components[i] = -1;
        }
    }
};
