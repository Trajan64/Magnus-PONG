#include "Paddle.h"
#include "LifeBar.h"

class Player {

	public:

		Player(Paddle *, int, LifeBar *, Vec3D);
		~Player();
		Paddle *	getPaddle();
		void		hit();
		bool		isAlive();
		void		reset();
		void		displayLifeBar();
		void		drawPaddle();

	private:

		LifeBar *	m_lifeBar;
		int			m_defaultLives;
		Paddle *	m_paddle;
		Vec3D		m_color;
};