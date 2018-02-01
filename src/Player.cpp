#include "stdafx.h"
#include "Player.h"

/** Symbolize a player.
*
*	This class stores the data/objects used by one of the players. 
*
*	It stores and allows the interaction of the paddle as well as the remaining lives of the player.
*
*/
Player::Player(Paddle * paddle, int lives, LifeBar * lifeBar, Vec3D color) {

	m_paddle = paddle;
	m_lifeBar = lifeBar;
	m_defaultLives = lives;
	m_color = color;

}

/*
*	Deconstructor.
*/
Player::~Player() {

	delete m_lifeBar;

}


/*
*	Get the player's paddle.
*/
Paddle * Player::getPaddle() {

	return m_paddle;
}


/*
*	To be called when a player has lost a round.
*/
void Player::hit() {

	m_lifeBar->decreaseLives();
}


/*
*	Return true is the player got some lives remaining; false otherwise.
*/
bool Player::isAlive() {

	if (m_lifeBar->getLivesLeft() > 0) {
		return 1;
	}

	return 0;

}

/*
*	Display the player's lifeBar on screen.
*/
void Player::displayLifeBar() {

	m_lifeBar->display(m_color);
}


/*
*	Display player's paddle on screen.
*/
void Player::drawPaddle() {

	m_paddle->draw(m_color);

}



/*
*	Reset the player's lives as well as the player's paddle's position.
*/
void Player::reset() {

	m_lifeBar->setLives(m_defaultLives);
	m_paddle->reset();

}