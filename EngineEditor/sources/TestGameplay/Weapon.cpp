#include "Weapon.h"
#include "../Components/Transform.h"
#include "../Systems/StaticMeshSystem.h"
#include "../Systems/TransformSystem.h"


Weapon::Weapon()
{
	m_name = "Weapon";

	size_t indexMesh = World::GetInstance().GetSystem<StaticMeshSystem>()->RegisterDefault(m_indexTransform, "resources/models/viking_room.obj", "resources/images/viking_room.png");

	AddComponent<StaticMesh>(indexMesh);
}

Weapon::~Weapon()
{
}

void Weapon::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	GetTransform()->Rotate({ 10.f * deltaTime, 0.f , 0.0f });
}

void Weapon::Begin()
{
	Actor::Begin();
	
}

void Weapon::End()
{
	Actor::End();
}
