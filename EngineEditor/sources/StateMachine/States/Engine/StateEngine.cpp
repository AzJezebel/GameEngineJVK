#include "StateEngine.h"

#include "../../../App.h"
#include "../../../ECS/World.h"
#include "../../../Components/Camera.h"
#include "../../../InputSystem/DefineInput.h"
#include "../../../InputSystem/InputManager.h"
#include "../../../TestGameplay/Player.h"
#include "../../../TestGameplay/Weapon.h"
#include "../../../Scene/Scene.h"
#include "../../../Scene/Actor.h"
#include "../../../TestGameplay/Capsule.h"
#include "../../../TestGameplay/Mountain.h"
#include "../../../TestGameplay/Sphere.h"
#include "../../../TestGameplay/StaticBox.h"
#include "Window/Window.h"
#include "../../../Scene/SceneManager.h"
#include "../../../Serialization/Serializer.h"

StateEngine::StateEngine()
{
	World* m_world = &World::GetInstance();
	//Setup EditorSystem
	m_camControlSystem = m_world->RegisterSystem<CameraControlSystem>();
	{
		Signature signature;
		signature.set(m_world->GetComponentType<Camera>());
		m_world->SetSystemSignature<CameraControlSystem>(signature);//todo deplace in constructor ?
	}
}

StateEngine::~StateEngine()
{
	//TODO Check if their load has been skipped (when Loading scene with XML)
}

void StateEngine::Begin(Window* window, InputManager* inputManager, size_t sceneID, RenderingMgr* render)
{
	SceneManager& sm = SceneManager::GetInstance();

	m_inputManager = inputManager;
	m_window = window;
	m_sceneID = sceneID;

	m_camControlSystem->Init(inputManager, window, sm.GetSceneAt(m_sceneID));
	if (m_bisFirstTime)
	{
		if (sm.GetSceneAt(m_sceneID)->m_root != nullptr && sm.GetSceneAt(m_sceneID)->m_root->m_children.empty())
		{
			m_player = new Player{};
			m_weapon = new Weapon{};
			m_mountain = new Mountain{};
			m_box = new StaticBox{};
			m_sphere = new Sphere{};
			m_capsule = new Capsule{};
			sm.GetSceneAt(m_sceneID)->m_root->AddChild(m_player);
			sm.GetSceneAt(m_sceneID)->m_root->m_children[0]->AddChild(m_weapon);
			sm.GetSceneAt(m_sceneID)->m_root->AddChild(m_box);
			sm.GetSceneAt(m_sceneID)->m_root->AddChild(m_mountain);
			sm.GetSceneAt(m_sceneID)->m_root->AddChild(m_sphere);
			sm.GetSceneAt(m_sceneID)->m_root->AddChild(m_capsule);

			m_bDefaultScene = true;
		}
		//m_inputManager->SaveKey("LoadScene", KEY_N);
		//m_inputManager->SaveKey("SaveScene", KEY_M);
		//-------------------------------------------------------------------------------------

		//m_inputManager->BindKey("SaveScene", KeyEvent::PRESS, this, &StateEngine::SaveScene);
		m_inputManager->BindKey("CloseApp", KeyEvent::PRESS, this, &StateEngine::CloseApp); 


		m_bisFirstTime = false;
	}
	else
	{
		m_inputManager->SaveKey("CloseApp", KEY_ESCAPE);
		//m_inputManager->SaveKey("SaveScene", KEY_M);

		//-------------------------------------------------------------------------------------

		m_inputManager->BindKey("CloseApp", KeyEvent::PRESS, this, &StateEngine::CloseApp); 
		//m_inputManager->BindKey("SaveScene", KeyEvent::PRESS, this, &StateEngine::SaveScene);
	}
	sm.GetSceneAt(m_sceneID)->Begin();
}

void StateEngine::End()
{
	SceneManager::GetInstance().GetSceneAt(m_sceneID)->End();

	m_inputManager->Clear();
}

STATE StateEngine::Update(Window* window, const float deltaTime)
{
	m_camControlSystem->Update(deltaTime);
	//m_scene->Update(deltaTime);
	return m_currentState;
}

void StateEngine::CloseApp()
{
	m_window->SetWindowShouldClose();
}

void StateEngine::SaveScene()
{
	XML::Serializer::GetInstance().ExportScene(SceneManager::GetInstance().GetScene());
}

void StateEngine::LoadScene()
{
	SceneManager& sm = SceneManager::GetInstance();

	Scene scene = XML::Serializer::GetInstance().LoadScene("resources/no_name.xml");
	sm.AddScene(scene);
	sm.ChangeScene(sm.GetScenesSize() - 1);

	//m_fsm->ChangeSceneID(SceneManager::GetInstance().GetCurrentID());
}