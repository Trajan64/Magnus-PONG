#pragma once

#include "Ball.h"
#include "Paddle.h"

class AI
{


	public:
		AI(float, Ball *, float, Paddle *);
		~AI();


		void		update(float);
		void		setSkill(float);

	private:

		void		moveTowards(Vec3D, float accumulatedTime);

		float		m_reactionSpeed;
		float		m_accumulator;
		float		m_skill;
		Ball *		m_ball;
		Paddle *	m_paddle;



};

