#pragma once
#include "../Components/StaticMesh.h"
#include "../Scene/Actor.h"

class Weapon : public Actor
{
public:
	Weapon();
	~Weapon();

	void Update(float deltaTime) override;
	void Begin() override;
	void End() override;
	/*StaticMesh mesh;*/
};
