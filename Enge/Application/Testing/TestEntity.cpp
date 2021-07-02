#include "TestEntity.h"

namespace Enge {

	void TestEntity::OnStart() {
		LOG(ENGE_INFO, "TEST ENTITY HAS STARTED\n");
	}

	void TestEntity::OnTick(float dt) {
		this->transform.x += dt;
	}

	void TestEntity::OnEnd() {
		LOG(ENGE_INFO, "TEST ENTITY HAS BEEN DESTROYED\n");
	}
}