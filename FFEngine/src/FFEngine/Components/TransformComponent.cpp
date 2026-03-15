#include "FFEngine/Components/TransformComponent.h"

using namespace FFE;

void TransformComponent::SetPosition(const glm::vec3& pos)
{
    _position = pos;
    _transformDirty = true;
}

void TransformComponent::SetRotation(const glm::quat& rot)
{
    _rotation = rot;
    _transformDirty = true;
}

void TransformComponent::SetScale(const glm::vec3& s)
{
    _scale = s;
    _transformDirty = true;
}

glm::mat4 TransformComponent::GetTransformMatrix() const
{
    if (_transformDirty)
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), _position);
        glm::mat4 rotationMatrix = glm::mat4_cast(_rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), _scale);

        _transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        _transformDirty = false;
    }
    return _transformMatrix;
}
