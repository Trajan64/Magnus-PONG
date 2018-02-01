#include "stdafx.h"
#include "Physics.h"
#include <math.h>

/**	Update the game's world 
*	
*	Allows the update of the ball's position while checking for and correcting collisions with the environement.	
*
*/
Physics::Physics(Room * room, Paddle * paddle1, Paddle * paddle2, Ball * ball) {

	m_room = room;
	m_ball = ball;
	m_paddles.push_back(paddle1);
	m_paddles.push_back(paddle2);

}



/*
*	Update the game's world for an amout of time that is either equal or lesser than the value passed as argument.
*
*	If a collision is detected during the update, this method will position the ball right next to the colliding object.
*
*	For conveniance, if the updated ball happens to be past one of the paddle, this method will return the paddle's id (loser id).
*/
int Physics::timeStep(float * dt) {

	// Get the ball's position at time dt.
	Vec3D candidatePosition = m_ball->getCandidatePosition(*dt);

	float ballRadius = m_ball->getRadius();
	Vec3D ballPosition = m_ball->getPosition();

	int i;
	// Check and correct collision with walls.
	for (i = 0; i < 4; i++) {
		if (isCollidingWithWall(i, candidatePosition, ballRadius)) {

			correctCollisionWithWall(i, candidatePosition, ballPosition, ballRadius, dt);
			return 0;
		}
	}

	// Check and correct collisions with paddles.
	for (i = 0; i < 2; i++) {
		if (isPastPaddleZone(i, candidatePosition, ballRadius)) {

			if (!correctCollisionWithPaddle(i, candidatePosition, ballPosition, ballRadius, dt)) {

				// The ball was found to be past the currently analyzed paddle. 
				// We just return it's id.
				return i + 1;
			}

			return 0;
		}

	}

	// No collision detected with the candidate position,
	// we can set it as the ball's position. 
	m_ball->update(*dt);

	return 0;
};




/*
*	Return true if a collision is detected between a ball and a wall.
*/
bool Physics::isCollidingWithWall(int wallIndex, Vec3D& candidatePosition, float ballRadius) {

	Wall& wall = (*m_room)[wallIndex];

	Vec3D& wallNormal = wall.getNormal();
	Vec3D& wallPosition = wall.getPosition();

	float edge;

	unsigned int i;
	for (i = 0; i < 2; i++) {

		if (wallNormal[i]) {

			// Get the ball's edge that is the closest towards the wall.
			edge = (candidatePosition[i] + (ballRadius * -(wallNormal[i]))) * wallNormal[i];

			// If the edge is past the wall's position we then have a collision.
			if (edge < -fabs(wallPosition[i])) {
				return 1;

			}
		}
	}

	return 0;

}



/*
*	Return true if the ball is past the paddle's goal plane.
*/
bool Physics::isPastPaddleZone(int paddleIndex, Vec3D& candidatePosition, float ballRadius) {

	float paddleNormal = m_paddles[paddleIndex]->getNormal();

	// Get the ball's outmost edge in direction of the paddle's goal.
	float edge = (candidatePosition.z + (ballRadius * -paddleNormal)) * paddleNormal;
	float wall = m_paddles[paddleIndex]->getDepth() * paddleNormal;

	// Check if the edge is past the paddle's goal.
	if (edge <= wall) {
		return 1;
	}

	return 0;

}



/*
*	Correct a collision with a paddle and a wall.
*/
void Physics::correctCollisionWithWall(int collidingWallIndex, Vec3D& candidatePosition, Vec3D& ballPosition, float ballRadius, float * dt) {


	Vec3D& wallNormal = (*m_room)[collidingWallIndex].getNormal();
	int i = (wallNormal[0] != 0) ? 0 : 1;

	Vec3D roomPosition = (*m_room)[collidingWallIndex].getPosition();

	Vec3D impactPosition = getImpactPosition(roomPosition, ballPosition, ballRadius, i);

	float timeCovered = getDistanceCovered(ballPosition, candidatePosition, impactPosition) * *dt;

	// Update ball's position.
	m_ball->update(timeCovered);

	// Indicate how much time we covered within this session.
	*dt = timeCovered;

	// Modify the ball's velocity and rotation.
	m_ball->rebound(i, 0);

}


/*
*	Correct a possible collision with the ball and one of the paddle.
*
*	Return true if the the ball was within the paddle's boundaries; return false otherwise.
*/
bool Physics::correctCollisionWithPaddle(int collidingPaddleIndex, Vec3D& candidatePosition, Vec3D& ballPosition, float ballRadius, float * dt) {

	Vec3D colliderPosition = m_paddles[collidingPaddleIndex]->getPosition3D();
	Vec3D impactPosition = getImpactPosition(colliderPosition, ballPosition, ballRadius, 2);

	if (m_paddles[collidingPaddleIndex]->isSphereWithinPaddle(impactPosition, ballRadius)) {

		float timeCovered = getDistanceCovered(ballPosition, candidatePosition, impactPosition) * *dt;

		// Update ball's position.
		m_ball->update(timeCovered);

		// Indicate how much time we covered within this session.
		*dt = timeCovered;



		// The ball's velocity will be set relative to the paddle velocity.
		m_ball->rebound(2, m_paddles[collidingPaddleIndex]->getVelocity());

		return 1;
	}

	// The ball was not found to be in collision with the paddle.
	return 0;

}


/*
*	Start the engine by checking if the serving paddle has hit the ball.
*/
bool Physics::start(Paddle * paddle) {

	if (paddle->isSphereWithinPaddle(m_ball->getPosition(), m_ball->getRadius())) {

		m_ball->rebound(2, paddle->getVelocity());

		return 1;
	}

	return 0;
}


/*
*	Compute the position of impact based on the colliding plane's position.
*/
Vec3D Physics::getImpactPosition(Vec3D& colliderPosition, Vec3D& ballPosition, float ballRadius, int dimensionIndex) {

	Vec3D& ballVelocity = m_ball->getVelocity();

	// Compute 1D offset.
	float desiredPosition1D = fabs(colliderPosition[dimensionIndex] - ballPosition[dimensionIndex]) - ballRadius;

	// By knowing one of the components of the position of impact we can obtain the full position.
	float coefficient = (float)desiredPosition1D / (float)ballVelocity[dimensionIndex];
	Vec3D impactOffset = ballVelocity * coefficient;

	return ballPosition + impactOffset;

}


/*
*	Compute the ratio of the total distance covered over the distance initially desired.
*/
float Physics::getDistanceCovered(Vec3D& ballPosition, Vec3D& desiredPosition, Vec3D& impactPosition) {

	float desiredVectorLength = ((desiredPosition - ballPosition).absolute()).length();
	float impactVectorLength = ((impactPosition - ballPosition).absolute()).length();

	return (float)impactVectorLength / (float)desiredVectorLength;

}