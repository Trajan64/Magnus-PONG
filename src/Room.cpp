#include "stdafx.h"
#include "Room.h"

#include <GL/glut.h>
#include <stdlib.h>

/** Setup a room enclosed by 4 walls	
*/
Room::Room(float height, float width, float depth, PNGTexture ** textures)
{

	m_height = height;
	m_width = width;
	m_depth = depth;

	m_halfHeight = height / 2.0f;
	m_halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	PNGTexture * wallTexture = new PNGTexture("./textures/wall.png", 0);

	// Setup ceiling.
	m_walls.push_back(new Wall(width, depth, Vec3D(0.0f, m_halfHeight, -halfDepth), Vec3D(0.0f, -1.0f, 0.0f), wallTexture));

	// Setup floor.
	m_walls.push_back(new Wall(width, depth, Vec3D(0.0f, -m_halfHeight, -halfDepth), Vec3D(0.0f, 1.0f, 0.0f), wallTexture));

	// Setup a wall to the left.
	m_walls.push_back(new Wall(depth, height, Vec3D(-m_halfWidth, 0.0f, -halfDepth), Vec3D(1.0f, 0.0f, 0.0f), wallTexture));

	// Setup a wall to the right.
	m_walls.push_back(new Wall(depth, height, Vec3D(m_halfWidth, 0.0f, -halfDepth), Vec3D(-1.0f, 0.0f, 0.0f), wallTexture));
	
	// Calculate ratios.
	m_widthRatio = height / width;
	m_heightRatio = width / height;

}


/*
*	Deconstructor
*/
Room::~Room()
{
	for (int i = 0; i < 4; i++) {

		delete m_walls[i];

	}

}


/*
*	Draw the walls
*/

void Room::draw() {

	for (int i = 0; i < 4; i++) {
		m_walls[i]->draw();

	}

}


/*
*	Get the total height of the room (expressed in OpenGL coordinates).
*/
float Room::getHeight() {

	return m_height;
}


/*
*	Get the width of the room (expressed in OpenGL coordinates). 
*/
float Room::getWidth() {

	return m_width;

}


/*
*	Get the width to height ratio.
*/

float Room::getWidthRatio() {

	return m_widthRatio;

}


/*
*	Get the height to width ratio.
*/
float Room::getHeightRatio() {

	return m_heightRatio;

}


/*
*	Get the depth of the room (that is, how far ahead does it extends).
*/
float Room::getDepth() {

	return m_depth;

}


/*
*	Get the half height of the room. 
*/
float Room::getHalfHeight() {

	return m_halfHeight;
}


/*
*	Get the half width of the room.
*/
float Room::getHalfWidth() {

	return m_halfWidth;

}


/*
*	Get the bottom wall.
*/
Wall& Room::getFloor() {

	return *m_walls[1];

}

/*
*	Get the top wall.
*/

Wall& Room::getCeiling() {

	return *m_walls[2];

}


/*
*	Get the left wall.
*/
Wall& Room::getWallLeft() {

	return *m_walls[3];

}


/*
*	Get the right wall.
*/
Wall& Room::getWallRight() {

	return *m_walls[0];

}

/*
*	Get a wall by it's index.
*/
Wall& Room::operator[](unsigned int i) {

	return *m_walls[i];

}