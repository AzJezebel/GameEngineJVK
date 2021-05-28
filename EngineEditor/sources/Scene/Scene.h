#pragma once
#include <string_view>
struct Actor;

class Scene
{
public:
	Scene()
	{
		m_name = "no_name";
	}
	Scene(std::string_view name) :
		m_name(name)
	{
	}

	~Scene();

	void Begin();
	void BeginPlay();
	void Update(float deltaTime);
	void End();

	[[nodiscard]] Actor* GetActor(Actor* actor, unsigned int entityID);

	
	Actor* m_root = nullptr;
	std::string m_name;
};
