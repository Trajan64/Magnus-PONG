#include "stdafx.h"
#include "Paddle.h"
#include "Vec.h"

#define BORDER_LEFT 0
#define BORDER_RIGHT 1
#define BORDER_TOP 2
#define BORDER_BOTTOM 3


/** Symbolize a 3D modelled paddle.
*
*	This class setup an interactive paddle to be drawn in the 3D world.
*	
*	The zPosition argument indicate where the paddle zone should be located at.
*	The normal argument is a scalar value indicating the facing of the paddle. 
*/
Paddle::Paddle(float width, float height, float borderSize, float zPosition, float normal, Room * room, Vec3D color, Vec3D flashingColor) {

	m_flashingColor = flashingColor;

	m_velocity = Vec2D(0.0f, 0.0f);
	m_position = Vec2D(0.0f, 0.0f);
	m_mainColor = color;
	m_regularColor = color;
	
	m_width = width;
	m_height = height;

	m_zPosition = zPosition;
	m_normal = normal;

	m_halfWidth = width / 2.0f;
	m_halfHeight = height / 2.0f;

	m_timeToFlash = 0.5f;
	m_updateTime = 0.033333f;

	m_transparencyLevel = 0.8f;
	m_transparencyLevelBorders = 0.4f;

	// Create paddle shape.
	m_shape = new Rect(width - borderSize, height - borderSize);

	// Surround it with borders.
	m_shape->generateBorders(borderSize);

	m_flashing = 0;

	m_room = room;

}



/*
*	Deconstructor.
*/
Paddle::~Paddle() {

	delete m_shape;

}



/*
*	Update the flashing color.
*	This method should be called at each time step, with the amount of elapsed time since the last call as argument.
*
*	If the boolean variable flashing is set to true, this function will modify the paddle's color
*	so that it will progessively drift towards the regular (nonflashing) paddle color.
*	The color values will depend on the division of the time elapsed so far since the flashing and the value
*	inside the timeToFlash member variable.
*/
void Paddle::flashUpdate(float elapsedTime) {
	
	if (!m_flashing) {

		// The flash indicator has not been set. no need to continue.
		return;
	}

	m_timeFlashed += elapsedTime;

	float flashFactor = (float)m_timeFlashed / (float)m_timeToFlash;

	for (int i = 0; i < 3; i++) {
	
		m_mainColor[i] = (m_regularColor[i] - m_flashingColor[i]) * flashFactor + m_flashingColor[i];

	}

	if (flashFactor >= 1.0) {

		// We are done flashing, let's turn it off.
		m_flashing = 0;

	}

}



/*
*	Initialize a flashing procedure.
*
*	This method turns on a flash indicator.
*	During the drawing process, the paddle will first be displayed with a certain color and will
*	progressively go back to it's regular color. The amount of time needed for the transition is set by
*	the timeToFlash private variable member.
*
*	When a collision is detected with the paddle, this method will be automatically called.
*/
void Paddle::flash() {

	// Reset time accumulator.
	m_timeFlashed = 0;

	// Set flashing to true.
	m_flashing = 1;
	
	// Change the paddle's color.
	m_mainColor.x = m_flashingColor.x;
	m_mainColor.y = m_flashingColor.y;
	m_mainColor.z = m_flashingColor.z;

}



/*
*	Draw the paddle on screen.
*/
void Paddle::draw(Vec3D borderColor) {

	// Save current matrix at the top of the stack.
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_LIGHTING);

	// Setup transparency.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Translate to paddle's current position.
	glTranslatef(m_position.x, m_position.y, m_zPosition);

	// Colour and draw actual paddle.
	glColor4f(m_mainColor.x, m_mainColor.y, m_mainColor.z, 0.8f);
	m_shape->draw();

	// Colour and draw borders.
	glEnable(GL_COLOR);
	glColor4f(borderColor.x, borderColor.y, borderColor.z, m_transparencyLevelBorders);
	m_shape->drawBorder();

	// Re-enable ligthing and disable transparency setting.
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	// Restore transformation matrix.
	glPopMatrix();

	glClear(GL_CURRENT_BIT);

}



//TODO: should the instance manage it's own timer ?

/*
*	Move the paddle to a new position.
*	The elapsedTime argument must contain the amount of time elapsed since update()'s last call.
*	
*	Before moving the paddle, this method first check if the new position is not going to put the paddle outside of the room.
*	If so, to correct the error, the paddle will then be placed along the side of one of the the room's boundaries.
*
*	To record the paddle's velocity, the method setup a time accumulator containing the time elapsed since the last velocity update.
*	After hitting a fixed limit, the paddle's velocity will then be updated.
*
*/
void Paddle::update(float elapsedTime, Vec2D newPosition) {

	m_lastUpdateTime += elapsedTime;


	float x = newPosition.x;
	float y = newPosition.y;

	// Check if the paddle might step outside of the room after the position update.
	if ((x - m_halfWidth) < -m_room->getHalfWidth()) {
		x = -m_room->getHalfWidth() + m_halfWidth;
	}
	if ((x + m_halfWidth) > m_room->getHalfWidth()) {
		x = m_room->getHalfWidth() - m_halfWidth;
	}
	if ((y - m_halfHeight) < -m_room->getHalfHeight()) {
		y = -m_room->getHalfHeight() + m_halfHeight;
	}
	if ((y + m_halfHeight) > m_room->getHalfHeight()) {
		y = m_room->getHalfHeight() - m_halfHeight;
	}

	// Paddle's velocity may be updated only every m_updateTime seconds.
	if (m_lastUpdateTime >= m_updateTime) {
		
		// reset timer
		m_lastUpdateTime = 0;

		// update velocity
		m_velocity.x = -(x - m_position.x);
		m_velocity.y = (m_normal == 1) ? y - m_position.y : -(y - m_position.y);
	
	}

	m_position.x = x;
	m_position.y = y;
}



/*
*	Check for 2D collision with a sphere and the paddle.
*	Arguments should include the sphere position as well as it's radius.
*
*	If a collision is indeed detected, the flash() method will automatically be called.
*/
bool Paddle::isSphereWithinPaddle(Vec3D& spherePosition, float sphereRadius) {

	if (((spherePosition.x - sphereRadius) <= (m_position.x + m_halfWidth)) &&
		((spherePosition.x + sphereRadius) >= (m_position.x - m_halfWidth)) &&
		((spherePosition.y - sphereRadius) <= (m_position.y + m_halfHeight)) &&
		((spherePosition.y + sphereRadius) >= (m_position.y - m_halfHeight))) {

		// Flash paddle.
		flash();

		return 1;
	}
	return 0;
}



/*
*	Reset the paddle's position so that it wil be located at the center of the screen.
*/
void Paddle::reset() {

	m_position.x = 0;
	m_position.y = 0;

}



/*
*	Get the paddle's current velocity.
*/
Vec2D * Paddle::getVelocity() {

	return &m_velocity;
}


/*
*	Get the paddle's shape's width.
*/

float Paddle::getWidth() {

	return m_width;

}


/*
*	Get the paddle's shape's height.
*/
float Paddle::getHeight() {

	return m_height;

}


/*
*	Get the paddle's position.
*/
Vec2D Paddle::getPosition() {

	return m_position;

}


/*
*	Get the paddle's normal scalar value.
*/
float Paddle::getNormal() {

	return m_normal;
}


/*
*	Get the paddle's plane position in the room.
*/
float Paddle::getDepth() {

	return m_zPosition;

}


/*
*	Get the paddle's complete 3D position.
*/
Vec3D Paddle::getPosition3D() {

	return Vec3D(m_position.x, m_position.y, m_zPosition);
}