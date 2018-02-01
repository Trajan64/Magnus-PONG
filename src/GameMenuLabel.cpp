#include "stdafx.h"
#include "GameMenuLabel.h"

#define DEFAULT_SCALE_FACTOR 0.005f

/**	Manage a visual character string.
*/
GameMenuLabel::GameMenuLabel(char * label, float height) {

	m_height = height;
	m_text = new Text(label, DEFAULT_SCALE_FACTOR);

};


/*
*	Deconstructor.
*/
GameMenuLabel::~GameMenuLabel() {

	delete m_text;

};


/*
*	Return the height of the character string.
*/
float GameMenuLabel::getHeight() {

	return m_height;

};


/*
*	Do nothing.
*
*	All display objects must implement a mouse click event handler.
*	In this case, the object is not supposed to be interactive. 
*/
void GameMenuLabel::mouseOver(Vec2D& mousePosition) {

	return;

};


/*
*	Displays the object on screen.
*/
void GameMenuLabel::draw() {

	m_text->draw();

};
