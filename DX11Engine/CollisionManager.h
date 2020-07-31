#pragma once
#include "Collider.h"
#include <vector>
using namespace std;
class CollisionManager {
private:
	static vector<Collider*> colliders;
public:
	static void AddCollider(Collider* collider);
	static void RemoveCollider(Collider* collider);
	static void Update();
};