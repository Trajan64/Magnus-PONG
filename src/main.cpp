#include "stdafx.h"
#include "time.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include "Ball.h"
#include "Wall.h"
#include "Room.h"
#include "Paddle.h"
#include "Camera.h"
#include "AI.h"
#include "GameMenu.h"
#include "Levels.h"
#include "Physics.h"


bool OpenGLInitialized = false;

/* OPENGL RELATED INITIALIZERS */

void initializeOpenGL() {
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	OpenGLInitialized = 1;
}


/*
*	Setup a bunch of lights inside the 3D world.
*/
void setupLights() {
	GLfloat materialSpecular[] = {0.5f, 0.5f, 0.8f, 1.0f};
	GLfloat materialShininess = 45.0f;
	GLfloat materialAmbient[] = { 0.4f, 0.4f, 0.4f, 0.0f };
	GLfloat materialDiffuse[] = { 0.2f, 0.2f, 0.2f, 0.0f };

	GLfloat ligth1Position[] = { 0.0f, 0.5f, -8.0f, 1.0f };
	GLfloat light1Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat light1Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat light2Position[] = { 0.0f, 0.5f, -1.0f, 1.0f };
	GLfloat light2Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light2Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);

	glLightfv(GL_LIGHT0, GL_POSITION, ligth1Position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1Specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Diffuse);

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light2Position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light2Specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Diffuse);

	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


/* CONSTRUCTORS */

Room room = Room(1.3333333f, 2.40f, 8.0f, (PNGTexture **)NULL);

Paddle myPaddle = Paddle(0.35f, 0.2f, 0.01f, -1.0f, -1.0f, &room, Vec3D(0.2f, 0.2f, 0.2f), Vec3D(0.5f, 0.5f, 0.0f));
Paddle opponentPaddle = Paddle(0.35f, 0.2f, 0.01f, -8.0f, 1.0f, &room, Vec3D(0.2f, 0.2f, 0.2f), Vec3D(0.5f, 0.5f, 0.0f));
Camera * camera = new Camera(800, 450, &room, &myPaddle, 1.0f, 32.0f, (char *) "Magnus PONG");

std::vector<Paddle*> paddles;

Ball * ball = new Ball(0.1f, 12, 24, 0, &room, paddles, new Vec3D(0.0f, 0.0f, -1.5f));
AI ai = AI(0.0f, ball, 1.0f, &opponentPaddle);


Player me = Player(&myPaddle, 4, new LifeBar(Vec2D(0.1f, 0.15f), 0, 4), Vec3D(0.0f, 1.0f, 1.0f));
Player opponent = Player(&opponentPaddle, 4, new LifeBar(Vec2D(0.9f, 0.15f), 1, 4), Vec3D(1.0f, 0.5f, 0.0f));

std::vector<Player*> players;

GameMenu * currentMenu;

GameMenu * menuGameOver = new GameMenu(camera);
GameMenu * menuStart = new GameMenu(camera);
GameMenu * menuPause = new GameMenu(camera);

Levels levels = Levels(3.0, ball, &opponent, &me, &ai, &currentMenu, camera);

Physics * physics = new Physics(&room, &myPaddle, &opponentPaddle, ball);


// Game states.
#define GAME_PLAYING_SERVING 0
#define GAME_PLAYING_IN_ROUND 1
#define GAME_IN_MENU 2
#define GAME_ANNOUNCING_LEVEL 3
#define GAME_SHOW_GOAL 4
#define GAME_CHECK_ROUND_STATUS 5


// Initiliaze game state with state GAME_IN_MENU
unsigned int gameState = GAME_IN_MENU;

// Backup gameState. Usefull if we have to pause the game.
unsigned int previousGameState;

/* DRAW WORLD & DRAW UI/HUD FUNCTIONS */


/*
*	Draw all the objects inside the 3D environements.
*/
void draw3D() {
	camera->setup3DDrawing();
	setupLights();
	room.draw();
	opponent.drawPaddle();
	room.getFloor().drawSphereSilhouette(ball->getPosition(), ball->getRadius());
	ball->draw();
	me.drawPaddle();
}


/*
*	Draw all the 2D objects: UI and HUD.
*/
void draw2D() {

	camera->setupOrthographicDrawing();

	if (gameState == GAME_IN_MENU || gameState == GAME_ANNOUNCING_LEVEL) {
		currentMenu->render();
	}

	else {

		for (int i = 0; i < 2; i++) {

			players[i]->displayLifeBar();

		}

	}

}


/* USER INPUT CALLBACKS */


/*
*	Mouse click callback function.
*/
void mouseClick(int button, int state, int x, int y) {


	// Check to see if it's an actual click and if the button pressed is the left one.
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

		// Translate the mouse into normalized coordinates.
		Vec2D mousePosition = camera->getNormalizedCoordinates(x, y);

		switch (gameState) {

			case GAME_IN_MENU:

				// We are currently in a menu.
				// We must then check if the click has hit one of the menu's buttons.
				currentMenu->checkClick(mousePosition);
				break;

			case GAME_PLAYING_SERVING:

				// The player is serving.
				// Check if he clicked on the ball.
				if (physics->start(&myPaddle)) {

					// If so, this will start the game.
					gameState = GAME_PLAYING_IN_ROUND;
				}


		}
	}
}

clock_t mouseMoveLastTime;

/*
*	Mouse move callback function.
*/
void mouseMove(int x, int y) {

	// Calculate the elapsed time, which is necessary for the eventual update of the human player's paddle.
	clock_t currentTime = clock();
	float elapsedTime = (float)(currentTime - mouseMoveLastTime) / (float)CLOCKS_PER_SEC;

	// Update paddle's position if we are currently 'in-game'.
	if (!(gameState == GAME_IN_MENU)) {

		Vec2D position = camera->getNormalizedCoordinates(x, y);
		camera->moveFromNormalizedCoordinates(&position);

		position.x = position.x * (room.getWidth() - myPaddle.getWidth());
		position.y = position.y * (room.getHeight() - myPaddle.getHeight());

		myPaddle.update(elapsedTime, position);

	}

	mouseMoveLastTime = currentTime;

}


void reshape(int x, int y) {

	camera->reshape(x, y);

}



/* GAME LOOP */

clock_t currentTime;
float elapsedTime;
clock_t lastTime;

float accumulator;

// FPS. 
// The Physics simulation as well as the AI will be updated every dt.
float dt = 0.0333333333f;

int loser;

void gameLoop() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Time related update.
	currentTime = clock();
	elapsedTime = (float) (currentTime - lastTime) / (float)CLOCKS_PER_SEC;
	lastTime = currentTime;

	switch (gameState) {

		// Do nothing if the player is currently in a menu.
		case GAME_IN_MENU:
			break;

		// Display an announce to notice the start of a new level.
		case GAME_ANNOUNCING_LEVEL:
			if (levels.announceLevel(elapsedTime)) {
				gameState = GAME_PLAYING_SERVING;
			}
			break;

		// The human player is serving, no need for game related updates until the player actually serves.
		case GAME_PLAYING_SERVING:
			break;


		// Exhibit the goal that just happened.
		case GAME_SHOW_GOAL:
			if (ball->showGoal(elapsedTime)) {
				gameState = GAME_CHECK_ROUND_STATUS;
			}
			break;

		// A round is currently being played.
		// The physics simulation as well as the AI must be continiously updated until we have covered the value inside the accumulator. 
		case GAME_PLAYING_IN_ROUND:

			accumulator += elapsedTime;
			float coveredTime;

			// Semi-fixed timestep.
			while (accumulator >= dt) {
				coveredTime = dt;

				// Run physics simulation.
				if ((loser = physics->timeStep(&coveredTime)) > 2) {
					break;
				}
				accumulator -= coveredTime;

				// Update ai.
				ai.update(coveredTime);
				for (int i = 0; i < 2; i++) players[i]->getPaddle()->flashUpdate(dt);
			}
			// Check to see if the round has ended.
			if (loser > 0) {

				// If so, decrease loser value.
				loser -= 1;
				// Show the hit.
				gameState = GAME_SHOW_GOAL;

			}
			break;


		case GAME_CHECK_ROUND_STATUS:

			// Decrease loser's lives.
			players[loser]->hit();

			// Reset time accumulator.
			accumulator = 0;

			// Put the ai's paddle back at the center.
			opponentPaddle.reset();

			// Put the ball back at baseline.
			ball->reset();

			// Check to see if the human player got some lives left.
			if (!me.isAlive()) {

				// He doesn't -> it's game over.

				// Reset lives just in case we might play again.
				for (int i = 0; i < 2; i++) players[i]->reset();

				// Setup game over menu & modify game state.
				currentMenu = menuGameOver;
				gameState = GAME_IN_MENU;
			}

			else if (!opponent.isAlive()) {

				// It's the opponent who lost the game -> we go to the next level.
				levels.setupNextLevel();
				gameState = GAME_ANNOUNCING_LEVEL;
			}

			else {

				// One of the player lost a life but the current match has not ended yet.
				gameState = GAME_PLAYING_SERVING;
			}

			// Empty loser value.
			loser = 0;

			break;


	}

	// Draw the 3D world.
	draw3D();

	// Draw UI/HUD.
	draw2D();

	glutSwapBuffers();
	glFlush();

}

/*
*	Menu callback function.
*/
void buttonStart() {

	levels.setupLevel(0);
	gameState = GAME_ANNOUNCING_LEVEL;

}

/*
*	Menu callback function.
*/
void buttonQuit() {
	exit(0);

}

/*
*	Menu callback function.
*/
void buttonReturn() {

	// The previous state must have been saved before, we just have to restore it.
	gameState = previousGameState;

}



int main(int argc, char * argv[]) {

	glutInit(&argc, argv);

	// Setup game's camera.
	camera->setup();

	// Fill global objects.

	// Setup all the different levels.
	// For each call, the arguments are: the AI's difficulty, the ball's curve sensibility and the ball forward/backward speed.  
	levels.addLevel(17.0f, 25.0f, 4.8f);
	levels.addLevel(14.0f, 22.5f, 6.00f);
	levels.addLevel(11.0f, 20.0f, 6.33f);
	levels.addLevel(9.0f, 17.5f, 6.66f);
	levels.addLevel(7.0f, 15.0f, 7.00f);
	levels.addLevel(5.0f, 12.5f, 7.33f);
	levels.addLevel(3.5f, 10.0f, 7.66f);
	levels.addLevel(2.5f, 10.0f, 8.00f);
	levels.addLevel(1.5f, 10.0f, 8.33f);
	levels.addLevel(1.0f, 10.0f, 8.66f);
	
	// Fill 'players' vector.
	players.push_back(&me);
	players.push_back(&opponent);

	// Fill menus.

	menuStart->addLabel((char *) "MAGNUS PONG");
	menuStart->addButton((char *) "Play", buttonStart);
	menuStart->addButton((char *) "Quit", buttonQuit);

	menuGameOver->addLabel((char *) "GAME OVER");
	menuGameOver->addButton((char *) "Try again", buttonStart);
	menuGameOver->addButton((char *) "Quit", buttonQuit);

	menuPause->addLabel((char *) "Quit ?");
	menuPause->addButton((char *) "Yes", buttonQuit);
	menuPause->addButton((char *) "No", buttonReturn);

	currentMenu = menuStart;

	initializeOpenGL();
	setupLights();

	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	
	glutReshapeFunc(reshape);

	glutDisplayFunc(gameLoop);
	glutIdleFunc(gameLoop);

	glutMainLoop();

	return 0;
}