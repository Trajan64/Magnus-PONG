#pragma once

#include "GameMenuLabel.h"
#include "GameMenuButton.h"
#include "Vec.h"
#include "Camera.h"
#include <stdlib.h>
#include "Rectangle.h"

class GameMenu {

	public:

		GameMenu(Camera * camera);
		~GameMenu();

		void addLabel(char * label);
		void addButton(char * label, void(*callbackFunction)(void));
		void checkClick(Vec2D& clickPosition);
		void render();

	private:

		Camera * m_camera;
		float	calculateHeight();
		float	m_height;
		float	m_displayObjectHeight;
		float	m_displayObjectWidth;
		float	m_separatorValue;
		Rect *	m_background;
		std::vector<GameMenuLabel*> m_displayObjects;


};