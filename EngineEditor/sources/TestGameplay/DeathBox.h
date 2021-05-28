#pragma once
#include "../Scene/Actor.h"

class DeathBox : public Actor
{
public:
	DeathBox(); 

	void BeginOverlap(size_t idOtherEntity);
};
