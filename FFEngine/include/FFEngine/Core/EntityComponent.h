#pragma once
#include <unordered_map>

#include "FFCore/Core/HString.h"

namespace FFE
{
    class Entity;
    
    class ComponentTypeIDSystem 
    {
    public:
        template<typename T>
        static u32 GetTypeID() 
        {
            static u32 typeID = _nextTypeID++;
            return typeID;
        }
    private:
        static u32 _nextTypeID;
    };
    
    u32 ComponentTypeIDSystem::_nextTypeID = 0;
    
    class Component
    {
    public:
        enum class State 
        {
            Uninitialized,
            Initializing,
            Active,
            Destroying,
            Destroyed
        };
        
        virtual ~Component();
        
        void Initialize();
        void Destroy();
        
        template<typename T>
        static u32 GetTypeID() 
        {
            return ComponentTypeIDSystem::GetTypeID<T>();
        }
        
        Entity* Owner = nullptr;
        
    protected:
        virtual void OnInitialize() {}
        virtual void OnDestroy() {}
        virtual void Update(float dt) {}
        virtual void Render() {}
        
        State _state = State::Uninitialized;
        
        friend class Entity;
    };
    
    class Entity
    {
    public:
        explicit Entity(const std::string& entityName) : _name(entityName) {}
        FF::HString GetName() const { return _name; }
        
        void Initialize();
        void Update(float dt);
        void Render();
        
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) 
        {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

            size_t typeID = Component::GetTypeID<T>();

            // Check if component of this type already exists
            auto it = componentMap.find(typeID);
            if (it != componentMap.end()) 
            {
                return static_cast<T*>(it->second);
            }

            // Create new component
            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            T* componentPtr = component.get();
            componentMap[typeID] = componentPtr;
            _components.push_back(std::move(component));
            return componentPtr;
        }

        template<typename T>
        T* GetComponent() 
        {
            u32 typeID = Component::GetTypeID<T>();
            auto it = componentMap.find(typeID);
            if (it != componentMap.end()) 
            {
                return static_cast<T*>(it->second);
            }
            return nullptr;
        }

        template<typename T>
        bool RemoveComponent() 
        {
            size_t typeID = Component::GetTypeID<T>();
            auto it = componentMap.find(typeID);
            if (it != componentMap.end()) 
            {
                Component* componentPtr = it->second;
                componentMap.erase(it);

                for (auto compIt = _components.begin(); compIt != _components.end(); ++compIt) 
                {
                    if (compIt->get() == componentPtr) 
                    {
                        _components.erase(compIt);
                        return true;
                    }
                }
            }
            return false;
        }
        
        bool Active = true;
        
    private:
        FF::HString _name;
        // TODO: Arena allocator
        std::vector<std::unique_ptr<Component>> _components;
        std::unordered_map<u32, Component*> componentMap;
};
}
