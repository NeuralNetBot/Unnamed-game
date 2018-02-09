#include "Entity.h"



Entity::Entity()
{
	offset.Position.x = 0;
	offset.Position.y = 0;
	offset.Position.z = 0;
	offset.Rotation.x = 0;
	offset.Rotation.y = 0;
	offset.Rotation.z = 0;
}

void Entity::SetPosition(EntityPosition position)
{
	pos.Position.x = position.Position.x + offset.Position.x;
	pos.Position.y = position.Position.y + offset.Position.y;
	pos.Position.z = position.Position.z + offset.Position.z;
	pos.Rotation.x = position.Rotation.x + offset.Rotation.x;
	pos.Rotation.y = position.Rotation.y + offset.Rotation.y;
	pos.Rotation.z = position.Rotation.z + offset.Rotation.z;
}

EntityPosition Entity::GetPosition()
{
	return pos;
}

void Entity::SetOffset(EntityPosition offsets)
{
	offset.Position.x = offsets.Position.x;
	offset.Position.y = offsets.Position.y;
	offset.Position.z = offsets.Position.z;
	offset.Rotation.x = offsets.Position.x;
	offset.Rotation.y = offsets.Position.y;
	offset.Rotation.z = offsets.Position.z;
}

void Entity::Bind(Entity entity, EntityPosition offset)
{
	pos.Position.x = entity.GetPosition().Position.x + offset.Position.x;
	pos.Position.y = entity.GetPosition().Position.y + offset.Position.y;
	pos.Position.z = entity.GetPosition().Position.z + offset.Position.z;
	pos.Rotation.x = entity.GetPosition().Position.x + offset.Rotation.x;
	pos.Rotation.y = entity.GetPosition().Position.y + offset.Rotation.y;
	pos.Rotation.z = entity.GetPosition().Position.z + offset.Rotation.z;
}

Entity::~Entity()
{
}
