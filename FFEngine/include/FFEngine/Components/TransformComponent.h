#pragma once
#include "FFEngine/Core/EntityComponent.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace FFE
{
    class TransformComponent : public Component
    {
    public:
        void SetPosition(const glm::vec3& pos);
        void SetRotation(const glm::quat& rot);
        void SetScale(const glm::vec3& s);
        
        const glm::vec3& GetPosition() const { return _position; }
        const glm::quat& GetRotation() const { return _rotation; }
        const glm::vec3& GetScale() const { return _scale; }
        glm::mat4 GetTransformMatrix() const;
        
    private:
        glm::vec3 _position = glm::vec3(0.0f);
        glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // Identity quaternion
        glm::vec3 _scale = glm::vec3(1.0f);
        
        mutable glm::mat4 _transformMatrix = glm::mat4(1.0f);
        mutable bool _transformDirty = true;
    };
}
