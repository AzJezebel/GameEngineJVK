#include "StatePlay.h"

#include "../../../Components/Camera.h"
#include "../../../ECS/World.h"
#include "../../../Scene/Scene.h"
#include "../../../Scene/SceneManager.h"
#include "../../../Systems/PhysixSystem.h"
#include "../../../InputSystem/InputManager.h"
#include "RenderingManager.h"
#include "../../../InputSystem/DefineInput.h"
#include "../../../Systems/CameraSystem.h"
#include "../../../Systems/RenderSystem.h"
#include "../../../Systems/PhysixSystem.h"
#include "../../../Systems/TransformSystem.h"
#include "Window/Window.h"

void StatePlay::Begin(Window* window, InputManager* inputManager, size_t sceneID, RenderingMgr* render)
{
	if (!m_window)
	{
		m_window = window;
	}
	m_sceneID = sceneID;

	SceneManager::GetInstance().GetSceneAt(m_sceneID)->Begin();
	SceneManager::GetInstance().GetSceneAt(m_sceneID)->BeginPlay();

	World::GetInstance().GetSystem<PhysixSystem>()->UpdateAllTransform();

	auto camId = World::GetInstance().GetComponentID<Camera>(render->m_UIWindowManager.GetActorIDToPossess());
	if (camId != -1)
	{
		m_currentPlayerCamera = World::GetInstance().GetSystem<CameraSystem>()->GetCamera(camId);
	}


	inputManager->SaveKey("Scene1", KEY_F2);
	inputManager->BindKey("Scene1", KeyEvent::PRESS, this, &StatePlay::Scene1);
	inputManager->SaveKey("Scene2", KEY_F1);
	inputManager->BindKey("Scene2", KeyEvent::PRESS, this, &StatePlay::Scene2);
#ifndef _SHIPPING
	inputManager->SaveKey("ChangeState", KEY_ESCAPE);
	inputManager->BindKey("ChangeState", KeyEvent::PRESS, this, &StatePlay::ChangeState);
#endif

	inputManager->SetMousePosCallback(this, &StatePlay::MouseMoveCamera);
	window->SetCursorMode(m_bActiveMouse);
}
void StatePlay::Scene1()
{
	SceneManager& sm = SceneManager::GetInstance();

	if (sm.GetKnownScenes().empty() == false)
	{
		auto levelPath = sm.GetKnownScenes().find("no_name");

		if (levelPath != sm.GetKnownScenes().end())
		{
			sm.LoadKnownScene(levelPath->second);

			World::GetInstance().GetSystem<TransformSystem>()->Update();
		}
	}
}

void StatePlay::Scene2()
{
	SceneManager& sm = SceneManager::GetInstance();

	if (sm.GetKnownScenes().empty() == false)
	{
		auto levelPath = sm.GetKnownScenes().find("save");

		if (levelPath != sm.GetKnownScenes().end())
		{
			sm.LoadKnownScene(levelPath->second);
			
			World::GetInstance().GetSystem<TransformSystem>()->Update();
		}
	}
}

void StatePlay::End()
{
	m_window->SetCursorMode(true);
	World::GetInstance().GetSystem<PhysixSystem>()->End();
	SceneManager::GetInstance().GetSceneAt(m_sceneID)->End();
}

STATE StatePlay::Update(Window* window, const float deltaTime)
{
	SceneManager::GetInstance().GetSceneAt(m_sceneID)->Update(deltaTime);
	return m_currentState;
}

void StatePlay::MouseMoveCamera(double xOffset, double yOffset)
{
	m_mousePosX = xOffset;
	m_mousePosY = yOffset;

	double xoffset = xOffset - m_lastX;
	double yoffset = m_lastY - yOffset;

	m_lastX = xOffset;
	m_lastY = yOffset;
	if (m_currentPlayerCamera)
	{
		m_currentPlayerCamera->MouseMoveCamera((float)xoffset, (float)yoffset, true);
	}
}

void StatePlay::ChangeState()
{
	auto uimainToolBar = static_cast<UIWindowMainToolBar*>(World::GetInstance().GetSystem<RenderSystem>()->m_renderingMgr->m_UIWindowManager.GetWindow("MainToolBarWindow"));
	uimainToolBar->ResetToEngineState();
}
