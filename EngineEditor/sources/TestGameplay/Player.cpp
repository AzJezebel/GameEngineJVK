#include "Player.h"

#include <iostream>

#include "Actors/RigidType.h"
#include "../Components/Camera.h"
#include "../Systems/StaticMeshSystem.h"
#include "../Components/Transform.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/PhysixSystem.h"
#include "../Systems/TransformSystem.h"
#include "../InputSystem/DefineInput.h"
#include "../InputSystem/InputManager.h"
#include "Shapes/ComplexMesh/ConvexMesh.h"
#include "RenderingManager.h"
#include "../Components/SoundComponent.h"
#include "../Components/Lights/DirectionalLight.h"
#include "../Components/Lights/PointLight.h"
#include "../Components/Lights/SpotLight.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/LightSystem.h"
#include "../Systems/SoundSystem.h"
#include "Forces/ForceMode.h"

Player::Player()
{
	m_name = "Player";

	size_t indexMesh = World::GetInstance().GetSystem<StaticMeshSystem>()->RegisterDefault(GetTransform()->myIndexSystem, "resources/models/viking_room.obj", "resources/images/viking_room.png");

	AddComponent<StaticMesh>(indexMesh);

	size_t indexCamera = World::GetInstance().GetSystem<CameraSystem>()->Register(GetTransform()->GetLocalLocation(), { 0.f, 0.f, -1.f }, { 0.f, 1.f, 0.f });

	AddComponent<Camera>(indexCamera);
	//AddComponent(Camera{ {20.f,2.f,2.f} });

	if (GetMeshComponent() != nullptr)
	{
		std::pair<std::vector<uint32_t>, std::vector<LibMath::Vector3>> dataObj = World::GetInstance().GetSystem<RenderSystem>()->m_renderingMgr->GetModelVertex(GetMeshComponent()->modelID);

		ConvexMeshDescriptor cDesc = ConvexMeshDescriptor{ (unsigned int)dataObj.second.size(),dataObj.second };

		size_t indexCollider = World::GetInstance().GetSystem<PhysixSystem>()->RegisterDefaultShape(ConvexMesh{ cDesc }, RigidType::DYNAMIC,GetTransform() ,m_idEntity);

		AddComponent<Collider>(indexCollider);
		auto colider = World::GetInstance().GetSystem<PhysixSystem>()->GetCollider((GetComponent<Collider>()));
		colider->BindOnBeginContact(this, &Player::BeginOverlap);

		//World::GetInstance().GetSystem<PhysixSystem>()->GetPhysix(indexCollider)->BindOnBeginContact(this, &Player::BeginOverlap);
	}

	/*m_dataObj = World::GetInstance().GetSystem<RenderSystem>()->m_renderingMgr->GetModelVertex(m_mesh.modelID);

	m_cDesc = ConvexMeshDescriptor{ (unsigned int)m_dataObj.second.size(),m_dataObj.second };
	m_cPhysixShape = new ConvexMesh{ m_cDesc };

	m_collider =  new Collider { m_cPhysixShape, RigidType::DYNAMIC, m_indexTranform };
	m_collider->BindOnBeginContact(this, &Player::BeginOverlap);
	AddComponent(*m_collider);*/

	PointLight pointLight({ 0,1,0 }, { 1,1,1 }, { 1,0,0 }, { 0,1,0 }, 0.2f, 0.5f, 0.5f);

	DirectionalLight dirLight({ 0,1,0 }, { 0.7f,0.7f,0.7f }, { 0.7f,0.7f,0.7f }, { 0.7f,0.7f,0.7f });
	SpotLight spoLight(GetTransform()->GetLocalLocation(), { 0,1,0 }, 1.f, 1.f, { 0.7f,0.7f,0.7f }, { 0.7f,0.7f,0.7f }, { 0.7f,0.7f,0.7f }, 1.f, 1.f, 1.f);
	m_lightSystem = World::GetInstance().GetSystem<LightSystem>();
	//indexPointLight = m_lightSystem->Register(dirLight);

	size_t indexLight = World::GetInstance().GetSystem<LightSystem>()->Register(dirLight);
	AddComponent<LightComponent>(indexLight);

	/*size_t indexSound3D = World::GetInstance().GetSystem<SoundSystem>()->Register("resources/sounds/in-the-dark.wav", { 0,0,0 }, 10, 5);
	AddComponent<SoundComponent>(indexSound3D);*/
}

Player::~Player()
{
	/*delete m_cPhysixShape;
	delete m_collider;*/
}

void Player::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	
}

void Player::Begin()
{
	Actor::Begin();

	auto inputManager = &InputManager::GetInstance();
	inputManager->SaveKey("AddForce", KEY_SPACE);
	inputManager->BindKey("AddForce", KeyEvent::PRESS, this, &Player::AddForce);
	
	

	/*TransformSystem* m_tSystem = World::GetInstance().GetSystem<TransformSystem>();
	m_tranform = m_tSystem->GetTransform(m_indexTranform);*/
}

void Player::End()
{
	Actor::End();
}

void Player::BeginOverlap(size_t indexOtherCollider)
{
	std::cout << "je suis le player et je suis rentrer en contact avec " << indexOtherCollider << std::endl;
}

void Player::AddForce()
{
	if (GetPhysicsComponent() != nullptr)
	{
		ForceMode force(FORCE);
		GetPhysicsComponent()->AddForce({ 0,1000,0 }, force);
	}
}