#include "Sphere.h"

#include "../Components/Transform.h"
#include "../Systems/StaticMeshSystem.h"
#include "../Systems/TransformSystem.h"
#include "../Systems/PhysixSystem.h"
#include "Shapes/Primitives/SphereShape.h"
#include "Actors/RigidType.h"

Sphere::Sphere()
{
	m_name = "Sphere";
	size_t indexMesh = World::GetInstance().GetSystem<StaticMeshSystem>()->RegisterDefault(m_indexTransform, "resources/models/sphere.fbx");

	AddComponent<StaticMesh>(indexMesh);

	size_t indexCollider = World::GetInstance().GetSystem<PhysixSystem>()->RegisterDefaultShape(SphereShape{ 1.f }, RigidType::DYNAMIC,GetTransform(), m_idEntity);

	AddComponent<Collider>(indexCollider);
}

Sphere::~Sphere()
{
	/*delete m_physixShape;
	delete m_collider;*/
}

void Sphere::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void Sphere::Begin()
{
	Actor::Begin();

}

void Sphere::End()
{
	Actor::End();
}
