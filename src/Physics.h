#include "Vec.h"
#include "Ball.h"
#include "Paddle.h"
#include "Room.h"
#include <vector>


class Physics {

public:

	Physics(Room *, Paddle *, Paddle *, Ball *);
	int						timeStep(float *);
	bool					start(Paddle *);

private:

	Room *					m_room;
	std::vector<Paddle*>	m_paddles;
	Ball *					m_ball;

	bool					isCollidingWithWall(int, Vec3D&, float);
	bool					isPastPaddleZone(int, Vec3D&, float);
	void					correctCollisionWithWall(int, Vec3D&, Vec3D&, float, float *);
	bool					correctCollisionWithPaddle(int, Vec3D&, Vec3D&, float, float *);
	Vec3D					getImpactPosition(Vec3D&, Vec3D&, float, int);
	float					getDistanceCovered(Vec3D&, Vec3D&, Vec3D&);

	float					m_accumulator;

};