#include "Destroyer.h"
#include "Squisher.h"

void Destroyer::Update(float dt) {
	if (dynamic_cast<Squisher*>(m_game)->m_state == Squisher::eState::EndWave) {
		m_destroyed = true;
	}
}

void Destroyer::OnCollision(Actor* other) {
	if (other->m_tag == "Enemy") {
		dynamic_cast<Squisher*>(m_game)->m_baseHealth--;
	}
}