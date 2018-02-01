#include "Ball.h"
#include "Player.h"
#include "AI.h"
#include "GameMenu.h"
#include "Camera.h"
#include <vector>

class Levels {

	public:

		Levels(float, Ball *, Player *, Player *, AI *, GameMenu **, Camera *);
		void							addLevel(float, float, float);
		void							setupNextLevel();
		void							setupLevel(int);
		bool							announceLevel(float);

	private:

		bool							setup(int);
		int								m_currentLevel;
		float							m_accumulator;
		float							m_timeToAnnounce;
		std::vector<std::vector<float> >m_data;
		Player *						m_opponentPlayer;
		Player *						m_humanPlayer;
		AI *							m_ai;
		Ball *							m_ball;
		Camera *						m_camera;
		GameMenu **						m_currentMenu;

};