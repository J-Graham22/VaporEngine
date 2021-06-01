#pragma once
#include <SDL.h>

class Collider;

class CollisionMath
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const Collider& colA, const Collider& colB);
private:

};
