#include "../ECS.h"

void Entity::addGroup(Group memberGroup) {
	groupBitSet[memberGroup] = true;
	manager.AddToGroup(this, memberGroup);
}
