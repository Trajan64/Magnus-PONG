#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Vec.h"
#include "Rectangle.h"
#include "PNGTexture.h"


class LifeBar
{
	public:

		LifeBar(Vec2D, bool, int);
		~LifeBar();

		void			display(Vec3D);
		int				getLivesLeft();
		void			decreaseLives();
		void			setLives(int);

	private:

		Vec2D			m_position;
		int				m_direction;
		int				m_size;
		float			m_lifeWidth;
		float			m_lifeHeight;
		Rect *			m_shape;
		PNGTexture *	m_texture;


};