#pragma once
#include "Frame/Game.h"
#include "Renderer/Text.h"

class Squisher : public max::Game
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
	void SetFuelTimer(float time) { m_fuelTimer = time; }
	float GetFuelTimer() { return m_fuelTimer; }
	void SetWeaponTimer(float time) { m_weaponTimer = time; }

	int m_fuel = 100;

	friend class GameTrack;
	friend class Spawner;
	friend class Destroyer;

private:
	eState m_state = eState::Title;

	int m_weaponSelect = 1;
	int m_stageSelect = 1;
	int m_totalTracks = 2;

	int m_baseHealth = 10;

	float m_stateTimer = 0;

	float m_fuelTimer = 0;
	float m_weaponTimer = 0;

	int m_currentWave = 1;
	int m_finalWave = 5;
	int m_tracksDone = 0;
	int m_trackCount = 1;

	//std::unique_ptr<GameTrack> gametrack;

	std::shared_ptr<max::Font> m_aeromaxfont;
	std::shared_ptr<max::Font> m_speedracerfont;
	std::shared_ptr<max::Font> m_orangejuicefont;
	std::shared_ptr<max::Font> m_mondeur;


	std::unique_ptr<max::Text> m_scoreText;
	std::unique_ptr<max::Text> m_titleText;
	std::unique_ptr<max::Text> m_lazerText;
	std::unique_ptr<max::Text> m_gameOverText;
	std::unique_ptr<max::Text> m_stageSelectText;
	std::unique_ptr<max::Text> m_weaponSelectText;
	std::unique_ptr<max::Text> m_healthText;
};