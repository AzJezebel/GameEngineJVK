#include "Capsule.h"

#include "Bullet.h"
#include "Actors/RigidType.h"
#include "../Components/Collider.h"
#include "../Components/Transform.h"
#include "../InputSystem/InputManager.h"
#include "../Systems/StaticMeshSystem.h"
#include "../Systems/PhysixSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/ScriptingSystem.h"
#include "Shapes/Primitives/CapsuleShape.h"
#include "../InputSystem/DefineInput.h"
#include <filesystem>

Capsule::Capsule()
{
	m_name = "Capsule";
	m_bIsController = true;

	size_t indexCollider = World::GetInstance().GetSystem<PhysixSystem>()->RegisterDefaultShape(CapsuleShape{ 1.f, 0.5f }, RigidType::DYNAMIC,GetTransform(), m_idEntity);

	AddComponent<Collider>(indexCollider);
	GetPhysicsComponent()->LockRotation(true, true, true);
	GetPhysicsComponent()->SetMass(100);
	const size_t camIndex = World::GetInstance().GetSystem<CameraSystem>()->Register(GetTransform()->GetLocalLocation(), { 0.f, 0.f, -1.f }, { 0.f, 1.f, 0.f });

	AddComponent<Camera>(camIndex);

	World::GetInstance().GetSystem<ScriptingSystem>()->Register(m_idEntity, "Assets/Scripts/MyCharacterScript.lua");
}

Capsule::~Capsule()
{
	//delete m_shape;
	//delete m_collider;
}

void Capsule::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void Capsule::Begin()
{
	Actor::Begin();


}

void Capsule::BeginPlay()
{
	Actor::BeginPlay();
	auto inputManager = &InputManager::GetInstance();
	inputManager->SaveMouseKey("Pick", MOUSE_BUTTON_LEFT);
	inputManager->BindMouseKey("Pick", KeyEvent::RELEASE, this, &Capsule::Fire);
}

void Capsule::End()
{
	Actor::End();
	
}

void Capsule::Fire()
{
	new Bullet(GetCameraComponent()->m_cameraFront *7.f,  GetTransform()->GetWorldLocation() + GetCameraComponent()->m_cameraFront *2.f , this);
}
