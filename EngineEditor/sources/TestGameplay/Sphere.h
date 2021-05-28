#pragma once
#include "../Components/StaticMesh.h"
#include "../Scene/Actor.h"

struct Collider;
class SphereShape;

class Sphere : public Actor
{
public:
	Sphere();
	~Sphere();
	void Update(float deltaTime) override;
	void Begin() override;
	void End() override;

	/*StaticMesh m_mesh;
	SphereShape* m_physixShape = nullptr;
	Collider* m_collider;*/
};
