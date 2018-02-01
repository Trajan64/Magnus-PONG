#include "stdafx.h"
#include "AI.h"
#include "Ball.h"
#include "Paddle.h"


/**	AI player.
*	
*	Allows the human player to play against a CPU.
*
*/
AI::AI(float reactionSpeed, Ball * ball, float skill, Paddle * myPaddle) {

	m_reactionSpeed = reactionSpeed;
	m_accumulator = 0;
	m_skill = skill;
	m_paddle = myPaddle;
	m_ball = ball;

}


AI::~AI()
{

}


/*
*	Update AI's state.
*/
void AI::update(float timeElapsed) {

	m_accumulator += timeElapsed;

	if (m_accumulator >= m_reactionSpeed) {

		if (m_ball->getVelocity().z > 0.0f) {

			// The ball is moving towards human player.
			// The AI must then center the paddle.
			moveTowards(Vec3D(0.0f, 0.0f, 0.0f), m_accumulator);

		}

		else {

			// The ball is moving towards the AI's paddle.
			// The AI must then try it's best to intercept it.
			moveTowards(m_ball->getPosition(), m_accumulator);
		}

		m_accumulator -= m_reactionSpeed;

	}

}


/*
*	Move the AI's paddle towards a target.
*/
void AI::moveTowards(Vec3D target, float accumulatedTime) {

	// Get AI's paddle's position.
	Vec2D position = m_paddle->getPosition();

	// Calculate AI's speed.
	Vec3D velocity = (target - position) / m_skill;

	// Update paddle's position based on the sum of the AI's velocity and the paddle's position.
	m_paddle->update(accumulatedTime, Vec2D(velocity.x + position.x, velocity.y + position.y));

}


/*
*	Modify the CPU's difficulty level.
*/
void AI::setSkill(float skill) {

	m_skill = skill;

}