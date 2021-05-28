#include "Bullet.h"


#include "../Systems/PhysixSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/StaticMeshSystem.h"
#include "Actors/RigidType.h"

#include <Shapes\Primitives\SphereShape.h>

#include "../Scene/SceneManager.h"

Bullet::Bullet(const Vector3& velocity,const Vector3& pos, Actor* actor )
{
	m_name = "Bullet";
	m_name += m_idEntity;

	GetTransform()->SetLocalPosition(pos);

	GetTransform()->SetScale({ 0.2f,0.2f,0.2f });
	const size_t indexMesh = World::GetInstance().GetSystem<StaticMeshSystem>()->RegisterDefault(m_indexTransform, "Assets/StarterContent/bullet.fbx");

	AddComponent<StaticMesh>(indexMesh);


	Collider col(SphereShape{ 0.2f }, RigidType::DYNAMIC, pos, {}, m_idEntity);

	col.DisableGravity(true);

	col.SetLinearVelocity(velocity);

	col.BindOnBeginContact(this, &Bullet::BeginOverlap);
	
	const size_t indexCollider = World::GetInstance().GetSystem<PhysixSystem>()->Register(col);

	AddComponent<Collider>(indexCollider);

	SceneManager::GetInstance().GetScene()->m_root->AddChild(this);

	//GetPhysicsComponent()->SetAngularDamping(0.5f);

	//GetPhysicsComponent()->SetLinearVelocity(camFront * velocity);

	//GetPhysicsComponent()->BindOnBeginContact(this, &Bullet::BeginOverlap);
}

void Bullet::Update(float deltaTime)
{

	Actor::Update(deltaTime);

	GetTransform()->SetScale({ 0.2f,0.2f,0.2f });
	m_time += m_scale * deltaTime;

	if(m_time >= m_timeToDestroy)
	{
		Destroy();
	}
}

void Bullet::End()
{
	Actor::End();
	Destroy();
}

void Bullet::BeginOverlap(size_t /*idOtherEntity*/)
{
	m_time = m_timeToDestroy;
}

void Bullet::Destroy()
{
	Remove();
}
