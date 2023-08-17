#pragma once
#include "Frame/Game.h"
#include "Frame/Singleton.h"
#include "Renderer/Text.h"

class Squisher : public max::Game, public max::Singleton<Squisher>
{
public:
	enum class eState
	{
		Title, TrackSelect, StartGame, StartLevel, StartWave, Game, EndWave, GameOver
	};

public:
	// Inherited via Game
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(max::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	auto& GetScene() { return m_scene; }

	int m_fuel = 100;

	friend class GameTrack;
	friend class Spawner;
	friend class Destroyer;

private:
	eState m_state = eState::Title;

	int m_baseHealth = 10;

	float m_stateTimer = 0;


	//std::unique_ptr<GameTrack> gametrack;

	std::shared_ptr<max::Font> m_aeromaxfont;
	std::shared_ptr<max::Font> m_speedracerfont;
	std::shared_ptr<max::Font> m_orangejuicefont;
	std::shared_ptr<max::Font> m_mondeur;


	std::unique_ptr<max::Text> m_titleText;
	std::unique_ptr<max::Text> m_gameOverText;
	std::unique_ptr<max::Text> m_stageSelectText;
	std::unique_ptr<max::Text> m_healthText;
};