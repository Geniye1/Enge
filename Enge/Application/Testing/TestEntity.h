/*
	If all things go well, this file would actually be what gets generated when you create a new
	object in the engine. 
*/

#pragma once

#include "../Enge_PCH.h"

#include "../Entity.h"

namespace Enge {

	class TestEntity : public Entity {
	public:
		TestEntity(const std::string& name, std::vector<float> vertices) : Entity(name, vertices) {}

		virtual void OnStart() override;
		virtual void OnTick(float dt) override;
		virtual void OnEnd() override;
	};

}