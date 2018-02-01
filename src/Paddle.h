#pragma once
#include "Room.h"
#include "Rectangle.h"

#include <GL/glew.h>
#include <GL/glut.h>


class Paddle {

	public:

		Paddle(float, float, float, float, float, Room *, Vec3D, Vec3D);
		~Paddle();

		void		update(float dt, Vec2D);
		bool		isSphereWithinPaddle(Vec3D&, float);
		void		draw(Vec3D);
		void		reset();
		void		flashUpdate(float);
		Vec2D *		getVelocity();
		Vec2D		getPosition();
		Vec3D		getPosition3D();
		float		getWidth();
		float		getHeight();
		float		getDepth();
		float		getNormal();



	private:

		void		flash();

		float		m_width;
		float		m_height;
		GLfloat		m_halfWidth;
		GLfloat		m_halfHeight;
		float		m_zPosition;
		float		m_normal;
		Vec2D		m_velocity;
		Vec2D		m_position;
		Room *		m_room;
		Rect *		m_shape;
		float		m_lastUpdateTime;
		float		m_updateTime;
		float		m_transparencyLevel;
		float		m_transparencyLevelBorders;
		float		m_timeFlashed;
		float		m_timeToFlash;
		Vec3D		m_flashingColor;
		Vec3D		m_regularColor;
		Vec3D		m_mainColor;
		bool		m_flashing;


};

