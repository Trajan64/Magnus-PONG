#include "stdafx.h"
#include "Camera.h"

// TODO: include scalar size. viewport & boundaries will be generated from that data
// TODO: adapt normalizedBoundaries

// TODO: ratio, gluPerspective and cameraBoundaries should be computed according to which side has the biggest size

/**	Set the game's window and allow  
*
*/
Camera::Camera(const int startWidth, const int startHeight, Room * room, Paddle * playerPaddle, const float perspectiveNear, const float perspectiveFar, char * windowName)
{

	m_width = startWidth;
	m_height = startHeight;

	m_perspectiveNear = perspectiveNear;
	m_perspectiveFar = perspectiveFar;

	m_position = Vec2D(0.0f, 0.0f);

	m_paddle = playerPaddle;
	m_room = room;

	// Compute window's ratio.
	m_ratio = (float)m_width / (float)m_height;

	m_windowName = windowName;



};

/*
*	Initialize OpenGL window.
*/
void Camera::setup() {


	// Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(m_width, m_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(m_windowName);

	// Clear buffers.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	// Create viewport.
	glViewport(0, 0, m_width, m_height);

	// Setup projection matrix.
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0f, m_ratio, m_perspectiveNear, m_perspectiveFar);

	// Compute camera's maximum range of motion.
	m_boundaries = Vec2D(0.0f, 0.0f);
	// (world_size * ratio/2)
	m_boundaries.x = (float)m_room->getWidth() / 2.0f - ((float)m_width / (float)m_height) / 2.0f;
	m_boundaries.y = (float)m_room->getHeight() / 2.0f - 0.5f;


}


/*
*	Reshape the window whilst preserving the aspect ratio.
*/
void Camera::reshape(int x, int y) {

	// If window has been minimized.
	if (!x) {
		return;
	}

	int int_x = x;
	// Based on x, we need to calculate a new height where (new width)/(new height) equals to the previously calculated window width/height ratio.
	int int_ratio = int(x / m_ratio);

	glutReshapeWindow(x, int_ratio);
	glViewport(0, 0, x, int_ratio);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, m_ratio, m_perspectiveNear, m_perspectiveFar);
	glMatrixMode(GL_MODELVIEW);

	// Update window's width and height.
	m_width = int_x;
	m_height = int_ratio;

};


/*
*	Setup 3D drawing mode.
*/
void Camera::setup3DDrawing() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-((float)m_width / (float)m_height) / 2.0, ((float)m_width / (float)m_height) / 2.0, -0.5, 0.5, m_perspectiveNear, m_perspectiveFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);

	// Translate position, so that all 3d objects will be moved according to the camera's position.
	glTranslatef(m_position.x, m_position.y, 0.0f);

};

/*
*	Setup 2D drawing mode.
*/
void Camera::setupOrthographicDrawing() {

	// Disable ligthing as we don't need it.
	glDisable(GL_LIGHTING);

	// Setup orthographic projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 1.0, 0.0, 1.0, -1.0);

	// Clear modelview matrix.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};


/*
*	Return the width of the camera (window width).
*/
int Camera::getCameraWidth() {

	return m_width;

};

/*
*	Return the height of the camera (window height).
*/

int Camera::getCameraHeight() {

	return m_height;

};


/*
*	Normalize coordinates values. 
*/
Vec2D Camera::getNormalizedCoordinates(int x, int y) {

	return Vec2D(((x - m_width / 2.0f) / m_width), -((y - m_height / 2.0f) / m_height));

}


/*
*	Move the camera in the 3D world based on a normalized coordinate vector.
*/
void Camera::moveFromNormalizedCoordinates(Vec2D * position) {

	m_position.x = -(position->x * 2 * m_boundaries.x);
	m_position.y = -(position->y * 2 * m_boundaries.y);

};




Camera::~Camera()
{

}
