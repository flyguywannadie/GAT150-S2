#pragma once
#include "Frame/Game.h"
#include "Frame/Singleton.h"
#include "Frame/Event/EventManager.h"
#include "Renderer/Text.h"

class Squisher : public max::Game, max::IEventListener, public max::Singleton<Squisher>
{
public:
	enum class eState
	{
		Title, Gaming, StartLevel1, StartLevel2, StartLevel3, EndScreen, GameOver
	};

public:
	// Inherited via Game
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(max::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	auto& GetScene() { return m_scene; }

	void AddPoints(const max::Event& event);
	void OnPlayerDead(const max::Event& event);

private:
	eState m_state = eState::Title;

	float m_stateTimer = 0;


	//std::unique_ptr<GameTrack> gametrack;

	std::shared_ptr<max::Font> m_aeromaxfont;
	std::shared_ptr<max::Font> m_speedracerfont;
	std::shared_ptr<max::Font> m_orangejuicefont;
	std::shared_ptr<max::Font> m_mondeur;

	std::unique_ptr<max::Text> m_gameOverText;
};