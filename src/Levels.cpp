#include "stdafx.h"
#include "Levels.h"
#include <stdio.h>

/** Manage the game's levels.	
*
*	A level is characterized by 3 differents parameters: the ball's (forward/backward) speed, it's curve sensibility and the skill of the AI player.
*	This class allows the creation of multiple differents levels by defining, for each level, the values of those 3 parameters.
*
*/
Levels::Levels(float timeToAnnounce, Ball * ball, Player * opponent, Player * humanPlayer,  AI * ai, GameMenu ** currentMenu, Camera * camera) {

	m_timeToAnnounce = timeToAnnounce;
		
	m_currentMenu = currentMenu;
	m_currentLevel = 0;

	m_opponentPlayer = opponent;
	m_humanPlayer = humanPlayer;

	m_ai = ai;
	m_ball = ball;

	// GameMenu's constructor requires a camera instance.
	m_camera = camera;

}



/*
*	Add a level to the game.
*/
void Levels::addLevel(float AISkill, float ballSpeed, float curveSensibility) {

	// Put the level's informations inside a vector
	std::vector<float> levelInfos;
	levelInfos.resize(3);
	levelInfos[0] = AISkill;
	levelInfos[1] = ballSpeed;
	levelInfos[2] = curveSensibility;
	
	// Plug it in.
	m_data.push_back(levelInfos);

}


/*
*	Get to the next level.
*/
void Levels::setupNextLevel() {

	if (this->setup(m_currentLevel + 1)) {
		m_currentLevel++;
	}
}


/*
*	Get to a specified level.
*/
void Levels::setupLevel(int levelId) {

	if (setup(levelId)) {

		m_currentLevel = levelId;
	}
}



/*
*	Setup a level.
*/
bool Levels::setup(int levelId) {


	// No need to continue if we already have reached the last level.
	if ((levelId + 1) > (int) m_data.size()) {
		return 0;
	}

	// If we're at the first level, we have to reset lives of the human player.
	if (!levelId) {
		m_humanPlayer->reset();
	}

	// Give the opponent all his lives back.
	m_opponentPlayer->reset();

	// Setup level.
	m_ai->setSkill(m_data[levelId][0]);
	m_ball->setCurveAmount(m_data[levelId][1]);
	m_ball->setSpeed(m_data[levelId][2]);

	// Reset time accumulator.
	m_accumulator = 0;

	// Create the temporary menu which will display the currently reached level.
	char stringBuffer[100];
	sprintf(stringBuffer, "Level %i", levelId+1);
	*m_currentMenu = new GameMenu(m_camera);
	(*m_currentMenu)->addLabel(stringBuffer);


	return 1;
}



/*
*	Notify the beginning of a new level by displaying it's identification for an amout of time
*	that is equal to the value inside the timeToAnnounce private member variable.
*
*	Return false if the instance has not yet finished to display the level's id; true otherwise.
*/
bool Levels::announceLevel(float elapsedTime) {

	m_accumulator += elapsedTime;

	if (m_accumulator > m_timeToAnnounce) {

		// Free the temporary menu instance we created.
		delete *m_currentMenu;

		return 1;
	}

	return 0;
}