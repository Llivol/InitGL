
#pragma once
#include "Texture.h"
#include "includes.h"
#include <vector>

/**** COMPONENTS ****/

//Component (base class)
// - owner: id of Entity which owns the instance of the component
struct Component {
    int owner;
};

struct Transform : public Component, public lm::mat4 {
    int parent = -1;
    lm::mat4 getGLobalMatrix(std::vector<Transform>& transform)
    {
        if (parent) { //if I have a model matrix parent
            // Multiply this model by all of its  parents
            return transform.at(parent).getGLobalMatrix(transform) * *this;
        } else {
            return *this;
        }
    }
};

struct Mesh : public Component {
    // TODO fill  in mesh data
};

typedef std::tuple<
    std::vector<Transform>,
    std::vector<Mesh>>
    ComponentArrays;

const int NUM_TYPE_COMPONENTS = 2;

template <typename T>
struct type2int {
};

template <>
struct type2int<Transform> {
    enum { result = 0 };
};

template <>
struct type2int<Mesh> {
    enum { result = 1 };
};

/**** ENTITY ****/
struct Entity {
    std::string name;
    bool active = true;
    int components[NUM_TYPE_COMPONENTS];
    Entity()
    {
        for (int i = 0; i < NUM_TYPE_COMPONENTS; i++) {
            components[i] = -1;
        };
    }
    Entity(std::string a_name)
        : name(a_name)
    {
        for (int i = 0; i < NUM_TYPE_COMPONENTS; i++) {
            components[i] = -1;
        }
    }
};
