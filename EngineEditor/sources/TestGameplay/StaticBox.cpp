#include "StaticBox.h"

#include "../Components/Transform.h"
#include "../Systems/StaticMeshSystem.h"
#include "../Systems/TransformSystem.h"
#include "../Systems/PhysixSystem.h"
#include "Actors/RigidType.h"
#include "Shapes/Primitives/BoxShape.h"

StaticBox::StaticBox()
{
	m_name = "StaticBox";

	size_t indexMesh = World::GetInstance().GetSystem<StaticMeshSystem>()->RegisterDefault(m_indexTransform);

	AddComponent<StaticMesh>(indexMesh);


	size_t indexCollider = World::GetInstance().GetSystem<PhysixSystem>()->RegisterDefaultShape(BoxShape{ 0.5f,0.5f,0.5f }, RigidType::STATIC,GetTransform(), m_idEntity);
	
	AddComponent<Collider>(indexCollider);

	GetPhysicsComponent()->SetScale({ 10, 10, 0.5 });
	//auto colider = World::GetInstance().GetSystem<PhysixSystem>()->GetCollider((GetComponent<Collider>()));
	//colider->TriggerCollision(true);
}

StaticBox::~StaticBox()
{
	//delete m_physixShape;
	//delete m_collider;
}

void StaticBox::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void StaticBox::Begin()
{
	Actor::Begin();	
}

void StaticBox::End()
{
	Actor::End();

}
