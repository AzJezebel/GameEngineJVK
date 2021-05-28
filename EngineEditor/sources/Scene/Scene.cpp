#include "Scene.h"

#include <iostream>

#include "Actor.h"

Scene::~Scene()
{	
	std::cout << "Destroyed" << std::endl;	
}

void Scene::Begin()
{
	if (m_root != nullptr)
	{
		m_root->Begin();
	}
}

void Scene::BeginPlay()
{
    if (m_root != nullptr)
    {
        m_root->BeginPlay();
    }
}

void Scene::Update(float deltaTime)
{
	if (m_root != nullptr)
	{
		m_root->Update(deltaTime);
	}
}

void Scene::End()
{
	if (m_root != nullptr)
	{
		m_root->End();
	}
}

Actor* Scene::GetActor(Actor* actor, unsigned int entityID)
{
    if (m_root != nullptr && actor != nullptr)
    {
        if (actor->m_idEntity == entityID)
        {
            return actor;
        }

        if (actor->m_children.empty() == false)
        {
            auto children = actor->m_children;


            for (Actor* childActor : children)
            {
                if (childActor->m_idEntity == entityID)
                {
                    return childActor;
                }

            	if (childActor->m_children.empty() == false)
            	{
                    auto* ActorFound = GetActor(childActor, entityID);

            		if (ActorFound != nullptr)
            		{
                        return ActorFound;
            		}
            	}
            }
        }
       
    }

    return nullptr;
}
