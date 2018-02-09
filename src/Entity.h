#pragma once
#include <glm\glm.hpp>

struct EntityPosition {
	glm::vec3 Position;
	glm::vec3 Rotation;
};
class Entity
{
private:
	EntityPosition pos;
	EntityPosition offset;
public:

	Entity();
	void SetPosition(EntityPosition position);
	EntityPosition GetPosition();
	void SetOffset(EntityPosition offsets);
	void Bind(Entity entity, EntityPosition offset);
	~Entity();
};

