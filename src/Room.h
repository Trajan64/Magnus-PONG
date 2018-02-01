#pragma once

#include "Wall.h"
#include "PNGTexture.h"

class Room
{
	public:

		Room(float, float, float, PNGTexture **);
		~Room();
		void				draw();
		float				getWidth();
		float				getHeight();
		float				getDepth();
		float				getWidthRatio();
		float				getHeightRatio();
		float				getHalfWidth();
		float				getHalfHeight();
		Wall&				getCeiling();
		Wall&				getFloor();
		Wall&				getWallLeft();
		Wall&				getWallRight();
		Wall&				operator[](unsigned int);


	private:

		std::vector<Wall*>	m_walls;
		float				m_width;
		float				m_height;
		float				m_depth;
		float				m_halfWidth;
		float				m_halfHeight;
		float				m_widthRatio;
		float				m_heightRatio;

};