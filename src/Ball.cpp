#include "stdafx.h"
#include "Ball.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vec.h"
#include <algorithm>
#include "Room.h"
#include "Paddle.h"

/** Setup and manage the game's ball.
*
*/
Ball::Ball(float radius, int rings, int sectors, bool startOrientation, Room * room, std::vector<Paddle*> paddles, Vec3D * position)
{

	m_startOrientation = (startOrientation) ? -1.0f : 1.0f;


	// Set speed Z (forward/backward speed) to default.
	m_speedZ = 4.8f;

	m_velocity = Vec3D(0.0f, 0.0f, m_speedZ * m_startOrientation);
	m_position = Vec3D(0.0f, 0.0f, -1.5f);
	m_startPosition = m_position;
	m_rotationalVector = Vec3D(1.0f, 1.0f, 1.0f);
	m_curve = Vec2D(0.0f, 0.0f);

	m_timeoutShowGoal = 0.75f;

	// Setup the ball's texture
	m_texture = new PNGTexture((const char *) "./textures/ball.png", 0);

	// Set default curve parameters.
	m_curveDecay = 1.004f;
	m_curveAmount = 25.0f;

	// Store data about environment.
	m_room = room;
	m_paddles = paddles;
	m_radius = radius;


	// Create sphere shape.
	float const R = 1.0f / (float)(rings - 1.0f);
	float const S = 1.0f / (float)(sectors - 1.0f);
	int r, s;


	m_vertices.resize(rings * sectors * 3);
	m_normals.resize(rings * sectors * 3);
	m_texcoords.resize(rings * sectors * 2);
	std::vector<GLfloat>::iterator v = m_vertices.begin();
	std::vector<GLfloat>::iterator n = m_normals.begin();
	std::vector<GLfloat>::iterator t = m_texcoords.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = (float) sin(-M_PI_2 + M_PI * r * R);
		float const x = (float) cos(2.0f * M_PI * s * S) * (float) sin(M_PI * r * R);
		float const z = (float) sin(2.0f * M_PI * s * S) * (float) sin(M_PI * r * R);

		*t++ = s*S;
		*t++ = r*R;

		*v++ = x * radius;
		*v++ = y * radius;
		*v++ = z * radius;

		*n++ = x;
		*n++ = y;
		*n++ = z;
	}

	m_indices.resize(rings * sectors * 4);
	std::vector<GLushort>::iterator i = m_indices.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
	}
}


/*
*	Draw ball on screen.
*/
void Ball::draw() {
	
	// If m_showGoal is on, that means that the ball has hit one of the goal zones and will be frozen for a given time.
	// We  must then give the ball a special color in order to indicate that the round is over.
	if (m_showGoal) {

		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	}

	// Else, the ball will be given it's regular color.
	else {

		glColor4f(0.6f, 0.6f, 0.6f, 0.6f);

	}

	m_texture->bind();
	// Save matrix on top of the stack.
	glPushMatrix();

	glTranslatef(m_position.x, m_position.y, m_position.z);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Rotate ball
	glRotatef(m_rotationalAngle, m_rotationalVector.x, m_rotationalVector.y, m_rotationalVector.z);

	// Setup pointers
	glVertexPointer(3, GL_FLOAT, 0, &m_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &m_normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &m_texcoords[0]);

	// Draw vertices batch
	glDrawElements(GL_QUADS, m_indices.size(), GL_UNSIGNED_SHORT, &m_indices[0]);
	glPopMatrix();

}


/*
*	Get ball's velocity.
*/
Vec3D& Ball::getVelocity() {
	return m_velocity;
}


/*
*	Get ball's radius.
*/
float Ball::getRadius() {
	return m_radius;
}


/*
*	Get ball's position.
*/
Vec3D& Ball::getPosition() {
	return m_position;
}


/*
*	Set ball's position.
*/
void Ball::setPosition(Vec3D& newPosition) {
	m_position = newPosition;
}


/*
*	Set ball's forward/backward speed.
*/
void Ball::setSpeed(float newSpeedZ) {
	
	m_speedZ = newSpeedZ;
	m_velocity.z = newSpeedZ * m_startOrientation;

}


/*
*	Set the ball's curve sensitivity.
*/
void Ball::setCurveAmount(float newCurveAmount) {

	m_curveAmount = newCurveAmount;

}

/*
*	Reset paramteres and position the ball at the initially given location.
*/
void Ball::reset() {

	// Put ball back at baseline position.
	m_position = m_startPosition;

	// Empty curve vector.
	m_curve.x = 0;
	m_curve.y = 0;

	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
	m_velocity.z = m_speedZ * m_startOrientation;

}


/*
*	Modify the ball's rotation, velocity and curve effect when the ball is found to be colliding with a plannar object.		
*/
void Ball::rebound(int collidingAxis, Vec2D * collidingObjectVelocity) {

	// Inverse velocity component at index collidingAxis.
	m_velocity[collidingAxis] *= -1.0f;

	// If the object is static (say a wall), we just have to update the curve.
	if (!collidingObjectVelocity) {

		m_curve[collidingAxis] = m_curve[collidingAxis] / ((m_curveDecay - 1.0f) * 50.0f + 1.0f);

	}

	// Else, the object is movable and has an impact on the ball's curving effect.
	else {

		m_curve = (*collidingObjectVelocity * 50.0f) / m_curveAmount;

		m_rotationalForce = collidingObjectVelocity->length() * 25000.0f;

	}

	// We inverse rotation vector's component at index collidingAxis.
	m_rotationalVector[collidingAxis] *= -1.0f;

}


/*
*	Peek ball's position at the provided time.
*/
Vec3D Ball::getCandidatePosition(float time) {

	return ((m_velocity + m_curve / m_curveDecay) * time) + m_position;

}


/*
*	When one of the players loses the current round,
*	this method will freeze the ball for a fixed time
*	in order to showcase the position where the hit occured.
*	It will also give some time for the human player to
*	ready himself for the next round.
*/
bool Ball::showGoal(float elapsedTime) {

	if (!m_showGoal) {

		// Turn the display on.
		m_showGoal = 1;

	}

	m_accumulatorShowGoal += elapsedTime;

	// Check if the time is up
	if (m_accumulatorShowGoal < m_timeoutShowGoal) {

		// If not, return 0 to indicate that the process is continuing.
		return 0;

	}
	
	// If so, it's over. We must turn m_showGoal off.
	m_showGoal = 0;

	// And reset the time accumulator.
	m_accumulatorShowGoal = 0.0f;

	return 1;

}


/*
*	Update ball's state with the elapsed time.
*/
void Ball::update(float time) {

	// Decrease curve's value.
	m_curve = m_curve / m_curveDecay;

	// Update velocity.
	m_velocity.x = m_velocity.x + m_curve.x;
	m_velocity.y = m_velocity.y + m_curve.y;

	// Add velocity to position.
	m_position = m_velocity * time + m_position;

	// Update rotational angle.
	m_rotationalAngle += m_rotationalForce * time;

}