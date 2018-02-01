#include "stdafx.h"
#include "Wall.h"
#include <vector>
#include "Vec.h"

/** Setup a wall in the environment.
*
*	Width and height arguments indicate the dimensions of the wall.
*	The position vector argument represents the wall's middle point location.
*	The normal vector argument indicate the orientation relative to the wall.
*/
Wall::Wall(float width, float height, Vec3D position, Vec3D normal, PNGTexture * texture) {

	// Create wall.
	m_shape = new Rect(width, height);

	// Setup texel coordinates.
	m_shape->setTexels(0.0f, 0.0f, 1.0f, 1.0f);

	m_normal = normal;
	m_position = position;

	m_texture = texture;

}



/*
*	Deconstructor.
*/
Wall::~Wall()
{

	delete m_shadow;
	delete m_shape;

}



/*
*	Put the shadow of a 3D sphere along the wall's surface.
*/
void Wall::drawSphereSilhouette(Vec3D& spherePosition, float sphereRadius) {

	// Create the shadow if it hasn't been created before.
	if (!m_shadow)
		m_shadow = new Circle(12, 1);

	// Save current matrix at the top of the stack.
	glPushMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);

	// Setup stencil buffer.
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);

	float x = (m_normal.x) ? m_position.x : spherePosition.x;
	float y = (m_normal.y) ? m_position.y : spherePosition.y;

	// Place the shadow at the right position.
	glTranslatef(x, y, spherePosition.z);
	glRotatef(-90, (!abs(m_normal.x)), (!abs(m_normal.y)), 0.0f);
	glScalef(sphereRadius, sphereRadius, 0.0f);

	glDisable(GL_LIGHTING);
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the shadow.
	m_shadow->draw();

	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	// Restore previous matrix.
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH);


}


/*
*	Put the wall in the 3D environment. 
*/

void Wall::draw() {

	// Save current matrix at the top of the stack.
	glPushMatrix();

	// Set the colour to black.
	glColor3f(1.0, 1.0, 1.0);

	// Position and rotate the wall so that it will be located at the right spot.
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(-90, !m_normal.x, !m_normal.y, 0.0f);

	// Set normal vector for lighting purposes.
	glNormal3f(!m_normal.x, !m_normal.y, m_normal.z);

	m_texture->bind();
	m_shape->draw();

	// Restore previous transformation matrix.
	glPopMatrix();

}



/*
*	Get the wall's normal.
*/
Vec3D& Wall::getNormal() {

	return m_normal;

}



/*
*	Get the wall's position.
*/
Vec3D& Wall::getPosition() {

	return m_position;

}



/*
*	Get one of the components of the wall's position.
*/
float& Wall::operator[](const unsigned int i) {

	return m_position[i];

}


