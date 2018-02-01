#include "stdafx.h"
#include "LifeBar.h"
#include "Vec.h"

/** Record and display the number of lifes a player has.
*	
*	The position argument indicates where the first life shape should be located at. 
*	The direction boolean either indicates if the next lifes should be lined up from left to right or right to left.
*	The size argument indicates how many lives the instance should start with.
*	The lifeFilePath argument tells where to find the life's texture image.
*/
LifeBar::LifeBar(Vec2D position, bool direction, int size) 
{

	m_position = position;

	m_direction = (direction) ? -1 : 1;

	m_size = size;

	m_lifeWidth = 0.075f;
	m_lifeHeight = 0.075f;


	// Create life shape.
	m_shape = new Rect(m_lifeWidth, m_lifeHeight);
	m_shape->setTexels(0.0f, 0.0f, 1.0f, 1.0f);
	
	m_texture = new PNGTexture((const char *) "./textures/ball_life.png", 1);

}


/*
*	Deconstructor.
*/
LifeBar::~LifeBar()
{

	delete m_shape;
	
}


/*
*	Return the number of remaining lives.
*/

int LifeBar::getLivesLeft() {

	return m_size;

}


/*
*	Decrease lives by one.
*/
void LifeBar::decreaseLives() {

	m_size--;

}


/*
*	Change the number of remaining lives.
*/
void LifeBar::setLives(int newSize) {

	m_size = newSize;

}


/*
*	Display the number of remaining lives on screen.
*/
void LifeBar::display(Vec3D color) {

	// Colour texture
	glColor4f(color.x, color.y, color.z, 0.5);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_texture->bind();

	// Save current matrix by putting it at the top of the stack.
	glPushMatrix();

	// Position the lifebar.
	glTranslatef(m_position.x, m_position.y, -1.0f);

	GLfloat offset = m_lifeWidth;

	for (int i = 0; i < m_size; i++) {

		// Draw life shape.
		m_shape->draw();

		// The next life shape will be drawn next to the previous one.
		glTranslatef(offset * m_direction, 0.0f, 0.0f);

	}

	// Restore previous transformation matrix.
	glPopMatrix();

	glDisable(GL_BLEND);


}