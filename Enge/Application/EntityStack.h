#pragma once

#include "Enge_PCH.h"

#include "Entity.h"

namespace Enge {

	class EntityStack {
	public:
		EntityStack() = default;
		~EntityStack();

		void PushEntity(Entity* entity);

		std::vector<Entity*>::iterator begin() { return m_Entities.begin(); }
		std::vector<Entity*>::iterator end() { return m_Entities.end(); }
	private:
		std::vector<Entity*> m_Entities;
	};

}