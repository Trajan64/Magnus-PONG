#pragma once

#include "GameMenuLabel.h"
#include "Vec.h"
#include "Rectangle.h"

class GameMenuButton : public GameMenuLabel {

	public:
		GameMenuButton(char *, float, float, void(*) (void));
		~GameMenuButton();

		virtual	void mouseOver(Vec2D& );
		virtual	void draw();


	private:
		float	m_width;
		float	m_halfWidth;
		float	m_halfHeight;

		Rect *	m_shape;
		void	(*m_callbackFunction) (void);

};