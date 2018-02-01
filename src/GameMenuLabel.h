#pragma once

#include "Text.h"
#include "Camera.h"
#include "Vec.h"

class GameMenuLabel
{
	public:

		GameMenuLabel(char *, float);
		~GameMenuLabel();

		virtual void	draw();
		virtual void	mouseOver(Vec2D&);
		float			getHeight();

	protected:

		Vec3D *			m_bgColor;
		float			m_width;
		float			m_height;
		Text *			m_text;

		Camera *		m_camera;
};