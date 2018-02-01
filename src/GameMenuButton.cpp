#include "stdafx.h"
#include "GameMenuButton.h"
#include <GL/glut.h>


/** Allows the rendering and manipulation of a button.
*
*	Creates and renders a button labeled by a character string.
*	The argument callbackFunction will be called by the class when detecting a mouse down event.
*/
GameMenuButton::GameMenuButton(char * label, float width, float height, void(*callbackFunction) (void)) : GameMenuLabel(label, height) {

	m_width = width;
	m_callbackFunction = callbackFunction;

	m_halfWidth = width / 2.0f;
	m_halfHeight = height / 2.0f;

	// Create button shape.
	m_shape = new Rect(width, height);
};


/*
*	Deconstructor
*/
GameMenuButton::~GameMenuButton() {

	delete m_shape;

};


/*
*	Display the button and it's text on the screen
*/
void GameMenuButton::draw() {

	glColor3f(1.0f, 1.0f, 0.0f);

	// Draw button.
	m_shape->draw();

	// Draw text.
	m_text->draw();

};


/*
*	Check if the provided mouse position is within the bounds of the button's body.
*	If true, the instance will call it's function pointer (callbackFunction) to do some actions.
*/
void GameMenuButton::mouseOver(Vec2D& mousePosition) {

	// Check if mouse position is within the button's body.
	if ((mousePosition.x >= -m_halfWidth) && (mousePosition.x <= m_halfWidth) &&
		(mousePosition.y >= -m_halfHeight) && (mousePosition.y <= m_halfHeight)) {

		(*m_callbackFunction)();

	}

};