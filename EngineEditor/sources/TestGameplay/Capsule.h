#pragma once
#include "../Components/StaticMesh.h"
#include "../Scene/Actor.h"
struct Collider;
class CapsuleShape;

class Capsule: public Actor
{
public:
	Capsule();
	~Capsule();
	void Update(float deltaTime) override;
	void Begin() override;
        void BeginPlay() override;
	void End() override;

	void Fire();
	/*CapsuleShape* m_shape;
	Collider* m_collider;*/
};
