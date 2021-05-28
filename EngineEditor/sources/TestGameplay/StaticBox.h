#pragma once
#include "../Components/StaticMesh.h"
#include "../Scene/Actor.h"
struct Collider;
class BoxShape;

class StaticBox : public Actor
{
public:

	StaticBox();
	~StaticBox();

	void Update(float deltaTime) override;
	void Begin() override;
	void End() override;
	//StaticMesh mesh;
	//BoxShape* m_physixShape = nullptr;
	//Collider* m_collider;
	
};
