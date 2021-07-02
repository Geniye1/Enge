#include "EntityStack.h"

namespace Enge {

	EntityStack::~EntityStack() {
		for (Entity* entity : m_Entities) {
			entity->OnEnd();
			delete entity;
		}
	}

	void EntityStack::PushEntity(Entity* entity) {
		m_Entities.emplace(m_Entities.begin(), entity);
		entity->OnStart();
	}

}