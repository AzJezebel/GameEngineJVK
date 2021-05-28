#pragma once
class Button
{
public:
	Button();

	void OnBeginOverlap(size_t otherActor);
	void OnEndOverlap(size_t otherActor);
};
