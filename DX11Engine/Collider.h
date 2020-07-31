#pragma once
#include "Component.h"
#include "Collision.h"
class Collider : public Component {
public:
	void SetTrigger(bool _isTrigger);
	bool GetTrigger();

	Collider();

private:
	bool isTrigger;
};