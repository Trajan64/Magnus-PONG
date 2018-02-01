#include "stdafx.h"
#include "GameMenu.h"

extern "C" {
#include <GL/gl.h>
}
#include <GL/glut.h>


/** Setup a GUI.
*
*	Allows the creation, interaction and rendering of different visual objects such as buttons or character strings.
*	When displayed on screen, the menu will always be presented as centered, with objects ordered from top to bottom.
*
*/
GameMenu::GameMenu(Camera * camera) {

	m_separatorValue = 0.06f;
	m_camera = camera;

	m_displayObjectHeight = 0.1f;
	m_displayObjectWidth = 0.6f;

	m_background = new Rect(2.0f, 2.0f);


	// initialize array of display objects
	std::vector<GameMenuLabel*> m_displayObjects;

};



/*
*	Deconstructor
*/
GameMenu::~GameMenu() {

	for (int i = 0; i < (int) m_displayObjects.size(); i++) {

		delete m_displayObjects[i];

	}

};



/*
*	Creates a simple character string object to be displayed on the game menu 
*/
void GameMenu::addLabel(char * label) {

	if (m_displayObjects.size()) {
		m_height += m_separatorValue;
	}

	m_displayObjects.push_back(new GameMenuLabel(label, m_displayObjectHeight));

	m_height += m_displayObjectHeight;
};



/*
*	Creates a button object to be displayed on the game menu.
*	callbackFunction  will be called once a provided click position will be found to be within the button's body. 
*/
void GameMenu::addButton(char * label, void(*callbackFunction) (void)) {

	if (m_displayObjects.size()) {
		m_height += m_separatorValue;
	}

	m_displayObjects.push_back(new GameMenuButton(label, m_displayObjectWidth, m_displayObjectHeight, callbackFunction));

	m_height += m_displayObjectHeight;
};


/*
*	Displays the menu on screen.
*/
void GameMenu::render() {

	float middle = (1.0f - m_height) / 2.0f;

	// Draw background.
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_background->draw();

	glDisable(GL_BLEND);

	// Translate to center the menu's content.
	glTranslatef(0.5f, middle, 0.0f);

	// Draw display objects.
	for (int i = 0; i < (int) m_displayObjects.size(); i++) {
		
		m_displayObjects[i]->draw();

		// Translate so that the next object will be drawn ounto the next line.
		glTranslatef(0.0f, m_displayObjects[i]->getHeight() + m_separatorValue, 0.0);

	}

	glColor3f(0, 0, 0);
	glClear(GL_CURRENT_BIT);

};

/*
*	Check on all the objects if a given mouse position is within their visual boundaries.
*	If true, the interrogated object might call a callback function to do some actions.
*/
void GameMenu::checkClick(Vec2D& mousePosition) {

	// get menu's centered position
	float middle = (1.0f - m_height) / 2.0f;

	Vec2D translatedMouse = Vec2D(mousePosition.x, ((-mousePosition.y + 0.5f) - middle));

	int i;
	for (i = 0; i < (int) m_displayObjects.size(); i++) {
		m_displayObjects[i]->mouseOver(translatedMouse);
		
		// We modify the mouse coordinates so that they will be expressed as relative to the next button's position.
		translatedMouse.y -= m_displayObjects[i]->getHeight() + m_separatorValue;
	}
};
