#include "entity.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"

using namespace Engine;

//Entity::Entity(string path, Shader& shader, Renderer* renderer) : ModelImp(path, shader, renderer) {
//
//}

glm::mat4 Entity::getLocalModelMatrix() {
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
        glm::radians(transform.eulerRot.x),
        glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
        glm::radians(transform.eulerRot.y),
        glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
        glm::radians(transform.eulerRot.z),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 roationMatrix = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), transform.pos) *
        roationMatrix *
        glm::scale(glm::mat4(1.0f), transform.scale);
}

void Entity::updateSelfAndChild() {
    if (parent)
        transform.modelMatrix = parent->transform.modelMatrix * getLocalModelMatrix();
    else
        transform.modelMatrix = getLocalModelMatrix();

    for (auto&& child : children)
    {
        child->updateSelfAndChild();
    }
}