#include "FFEngine/Core/EntityComponent.h"

using namespace FFE;

Component::~Component()
{
    if (_state != State::Destroyed)
    {
        OnDestroy();
        _state = State::Destroyed;
    }
}

void Component::Initialize()
{
     if (_state == State::Uninitialized)
     {
         _state = State::Initializing;
         OnInitialize();
         _state = State::Active;
     }
}

void Component::Destroy()
{
    if (_state == State::Active)
    {
        _state = State::Destroying;
        OnDestroy();
        _state = State::Destroyed;
    }
}

void Entity::Initialize()
{
    for (auto& component : _components) 
    {
        component->Initialize();
    }
}

void Entity::Update(float dt)
{
    if (!Active)
    {
        return;
    }

    for (auto& component : _components)
    {
        component->Update(dt);
    }
}

void Entity::Render()
{
    if (!Active)
    {
        return;
    }

    for (auto& component : _components) 
    {
        component->Render();
    }
}
