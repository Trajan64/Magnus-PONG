#include "stdafx.h"
//#include "Game.h"

/*

Game::Game() {

	// Setup the room.
	m_room = Room(1.3333333f, 2.40f, 8.0f);

	// Create camera.
	m_camera = Camera(800, 450, &m_room, &m_myPaddle, 1.0f, 32.0f, "Magnus PONG");

	// Create ball.
	m_ball = Ball(Vec3D(0.0f, 0.0f, -1.5f), 0.1f);

	int lives = 4;
	m_humanPlayer = Player(Vec3D(0.8, 0.5, 0.4), lives, room, camera);
	m_opponnent = Player(Vec3D(0.4, 0.4, 0.3), lives, room, camera);

	std::vector<Paddle*> paddles;
	paddles.push_back(m_humanPlayer->getPaddle(), m_opponent->getPaddle());

	// Setup physics manager.
	m_physics = Physics(&room, paddles, ball);

	m_players.push_back(humanPlayer);
	m_players.push_back(opponent);

	// Create AI.
	m_ai = AI(0.033f, ball, 1.0f, m_opponentPaddle);

	// Setup levels.
	m_levels = Levels(2.0f, m_ball, m_opponent, m_humanPlayer, ai);
	m_levels.addLevel(17.0f, 366, 5.66f);
	m_levels.addLevel(14.0f, 333, 6.00f);
	m_levels.addLevel(11.0f, 277, 6.33f);
	m_levels.addLevel(9.0f, 250, 6.66f);
	m_levels.addLevel(7.0f, 222, 7.00f);
	m_levels.addLevel(5.0f, 200, 7.33f);
	m_levels.addLevel(3.5f, 177, 7.66f);
	m_levels.addLevel(2.5f, 150, 8.00f);
	m_levels.addLevel(1.5f, 133, 8.33f);
	m_levels.addLevel(1.0f, 100, 8.66f);

	// Fill menus.
	m_menuStart = new GameMenu(m_camera);
	m_menuStart->addLabel("MAGNUS PONG");
	m_menuStart->addButton("Play", buttonStart);
	m_menuStart->addButton("Quit", buttonQuit);

	m_menuPause = new GameMenu(m_camera);
	m_menuPause->addLabel("Quit ?");
	m_menuPause->addButton("Yes", buttonQuit);
	m_menuPause->addButton("No", buttonReturn);

	m_menuGameOver = new GameMenu(m_camera);
	m_menuGameOver->addLabel("GAME OVER");
	m_menuGameOver->addButton("Try again", buttonStart);
	m_menuGameOver->addButton("Quit", buttonQuit);


	// Set current state.
	m_gameState = GAME_IN_MENU;
	currentMenu = menuStart;


}


void Game::mouseMove(int x, int y) {

	if (!m_currentMenu) {

		Vec2D position = camera->getNormalizedCoordinates(x, y);
		camera->moveFromNormalizedCoordinates(&position);


		position.x = position.x * (m_room.getWidth() - myPaddle.getWidth());
		position.y = position.y * (m_room.getHeight() - myPaddle.getHeight());

		myPaddle.update(10, position);

	}

}



void Game::mouseClick(int button, int state, int x, int y) {

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

		Vec2D mousePosition = m_camera->getNormalizedCoordinates(x, y);


		switch (m_gameState) {

			case GAME_IN_MENU:
				m_currentMenu->checkClick(mousePosition);
				break;

			case GAME_PLAYING_SERVING:
				if (m_physics->start(&myPaddle)) {
					m_gameState = GAME_PLAYING_IN_ROUND;
				}


		}
	}
}


void Game::drawWorld() {

	// Draw 3D:
	camera->setup3DDrawing();
	setupLights();
	m_room.draw();
	m_opponentPaddle.draw();
	m_room.getFloor().drawSphereSilhouette(m_ball->getPosition(), m_ball->getRadius());
	m_ball->draw();
	myPaddle.draw();

	// Draw 2D:

	camera->setupOrthographicDrawing();

	if (gameState == GAME_IN_MENU || gameState == GAME_ANNOUNCING_LEVEL) {
			m_currentMenu->render();
	}

	else {

		for (int i = 0; i < 2; i++) {

			m_players[i]->displayLifeBar();

		}

	}

}

void Game::pause() {

	m_currentMenu = m_menuStart;

}


void Game::unpause() {

	m_currentMenu = NULL;

}



void Game::start() {

	// Set current level to 1 and change game state.
	levels.setupLevel(0);
	gameState = GAME_ANNOUNCING_LEVEL;


}


int Game::gameLoop() {



	switch (m_gameState) {

		case GAME_LEVEL_ANNOUNCEMENT:

			// Check to see if we have finished noticing the beginning of the level.
			if (levels->announceLevel(elapsedTime)) {

				// If so, the match can start. 
				m_gameState = GAME_SERVING;
			}
			break;

		case GAME_SERVING:

			// Do nothing.
			break;

		case GAME_IN_ROUND:

			float coveredTime;
			int loser;
			m_timeAccumulator += elapsedTime;
			while (timeAccumulator >= m_fps) {

				// Run physics update.
				coveredTime = m_fps;
				if ((loser = physics->timeStep(&coveredTime)) > 2) {
						break;
				}

				timeAccumulator -= coveredTime;
				
				// Run ai.
				ai.update(coveredTime);
				for (int i = 0; i < 2; i++) players[i]->getPaddle()->flashUpdate(dt);

				}

				// Check to see if the round has ended.
				if (loser > 0) {

					// If so:

					// Decrease loser's lives.
					players[round.state]->hit();

					// Reset time accumulator
					m_timeAccumulator = 0;

					// Put the ai's paddle back at the center
					m_opponent.reset();
			
					// Put the ball back at baseline
					m_ball->reset();

					// Check to see if the human player got some lives left.
					if (!m_humanPlayer.isAlive()) {

						// He doesn't, it's game over.
						m_gameState = GAME_OVER;

						return GAME_OVER;
					}

					else if (!opponent.isAlive()) {

						// It's the opponent who lost the match,
						// The next level can be loaded.
						levels.setupNextLevel();
					}

					else {

						// One of the player lost a life but the current match has not ended yet.
						m_gameState = GAME_PLAYING_SERVING;
					}

				}

			}

	return 0;

}

*/

/*
*	Menu callback functions.
*/
/*
void buttonStart() {

	printf("buttonStart called");


}

void buttonQuit() {
	printf("buttonQuit called");
//	exit(0);

}


void buttonReturn() {

	// the previous state must have been saved before, we just have to restore it
	//gameState = previousGameState;

}

*/