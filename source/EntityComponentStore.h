#pragma once
#include "Components.h"
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

/**** ENTITY COMPONENT STORE ****/

//the entity component manager is a global struct that contains an array of
//all the entities, and an array to store each of the component types
struct EntityComponentStore {
    
    vector<Entity> entities;

    ComponentArrays components; // tuple of arrays
    
    //create Entity and add transform component by default
    //return array id of new entity
//    int createEntity(string name) {
//
//    }
//
   //creates a new component with no entity parent
   template<typename T>
   int createComponent(){
       vector<T>& the_comps = get<vector<T>>( components );

        Transform my_transform;

        // creates a new object directy on the vector
        the_comps.emplace_back();

       return (int)the_comps.size() - 1; // index of new transform in array
   }
//
//    //creates a new component and associates it with an entity
//    template<typename T>
//    T& createComponentForEntity(int entity_id){
//
//    }
//
//    //return reference to component at id in array
//    template<typename T>
//    T& getComponentInArray(int an_id) {
//
//    }
//
//    //return reference to component stored in entity
//    template<typename T>
//    T& getComponentFromEntity(int entity_id) {
//
//    }
//
//    //return id of component in relevant array
//    template<typename T>
//    int getComponentID(int entity_id) {
//
//    }
//
//    //returns a const (i.e. non-editable) reference to vector of Type
//    //i.e. array will not be editable
//    template<typename T>
//    std::vector<T>& getAllComponents() {
//
//    }
    
    //stores main camera id
    int main_camera = -1;
//
};

