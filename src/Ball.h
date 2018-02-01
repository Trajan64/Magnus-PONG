#pragma once
#include "PNGTexture.h"
#include <vector>
#include "Paddle.h"
#include "Room.h"

class Ball
{
public:
	
	Ball(float, int, int, bool, Room *, std::vector<Paddle*>, Vec3D *);
	~Ball();

	void					draw();
	void					reset();
	void					setCurveAmount(float);
	void					setSpeed(float);
	float					getRadius();
	Vec3D&					getPosition();
	Vec3D&					getVelocity();
	void					setPosition(Vec3D&);
	void					rebound(int, Vec2D *);
	void					update(float);
	Vec3D					getCandidatePosition(float);
	bool					showGoal(float);

private:

	float					m_curveAmount;
	float					m_curveDecay;
	Vec2D					m_curveAcc;
	float					m_radius;
	Vec3D					m_velocity;
	Vec3D					m_startPosition;
	std::vector<Paddle*>	m_paddles;
	Room *					m_room;
	float					m_rotationalForce;
	Vec3D					m_rotationalVector;
	float					m_rotationalAngle;
	PNGTexture *			m_texture;
	Vec3D					m_position;
	Vec2D					m_curve;
	float					m_startOrientation;
	float					m_speedZ;

	std::vector<GLfloat>	m_vertices;
	std::vector<GLfloat>	m_normals;
	std::vector<GLfloat>	m_texcoords;
	std::vector<GLushort>	m_indices;

	float					m_timeoutShowGoal;
	bool					m_showGoal;
	float					m_accumulatorShowGoal;




};

