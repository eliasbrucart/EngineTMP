#ifndef ENTITY_H
#define ENTITY_H
#include "export.h"
#include "modelimp.h"
#include "shader.h"
#include "renderer.h"
#include "mat4x4.hpp"
#include "vec3.hpp"
#include <string>
#include <list>
using namespace std;

namespace Engine {
    struct ENGINE_API Trans {
        /*SPACE INFORMATION*/
        //Local space information
        glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
        glm::vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

        //Global space information concatenate in matrix
        glm::mat4 modelMatrix = glm::mat4(1.0f);
    };

    class ENGINE_API Entity : public ModelImp {
    private:
    public:
        Trans transform;
        Entity() {

        }
        Entity(string path, Shader& shader, Renderer* renderer) : ModelImp(path, shader, renderer) {

        }
        //Entity(string path, Shader& shader, Renderer* renderer) : ModelImp(path, shader, renderer) {};
        std::vector<Entity*> children;
        Entity* parent = nullptr;
        //template<typename... TArgs>
        void addChild(Entity* entity)
        {
            children.emplace_back(entity);
            children.back()->parent = this;
        }
        glm::mat4 getLocalModelMatrix();
        void updateSelfAndChild();

    };
}

#endif