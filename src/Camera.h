#pragma once

#include "Vec.h"
#include "Room.h"
#include "Paddle.h"


class Camera
{

	public:

		Camera(int, int, Room *, Paddle *, float, float, char *);
		~Camera();

		int			getCameraWidth();
		int			getCameraHeight();
		void		reshape(int, int);
		Vec2D		getNormalizedCoordinates(int, int);
		void		moveFromNormalizedCoordinates(Vec2D *);
		void		setup3DDrawing();
		void		setupOrthographicDrawing();
		void		setup();

	private:

		float		m_perspectiveNear;
		float		m_perspectiveFar;
		float		m_ratio;
		Vec2D		m_position;
		Paddle *	m_paddle;
		Room *		m_room;
		Vec2D		m_normalizedCoordinates;
		Vec2D		m_boundaries;
		int			m_width;
		int			m_height;
		char *		m_windowName;



};

