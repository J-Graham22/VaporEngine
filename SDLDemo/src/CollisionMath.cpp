#include "../CollisionMath.h"
#include "../Collider.h"

bool CollisionMath::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectA.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		) {
		return true;
	}
	return false;
}

bool CollisionMath::AABB(const Collider& colA, const Collider& colB) {
	if (AABB(colA.collider, colB.collider)) {
		return true;
	}
	return false;
}