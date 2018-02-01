SRCDIR= ./src
OBJDIR= ./src/obj

CXX = g++
CFLAGS= -Wall
LDFLAGS = -lglut -lGL -lGLU

SOILDIR=./src/SOIL
SOILLIB = SOIL.a

SRCNAMES = \
	AI.cpp \
	Ball.cpp \
	Camera.cpp \
	Circle.cpp \
	Font.cpp \
	GameMenu.cpp \
	GameMenuLabel.cpp \
	GameMenuButton.cpp \
	Levels.cpp \
	LifeBar.cpp \
	Paddle.cpp \
	Physics.cpp \
	Player.cpp \
	PNGTexture.cpp \
	Rectangle.cpp \
	Room.cpp \
	Text.cpp \
	Vec.cpp \
	Wall.cpp \
	main.cpp \
	
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRCNAMES:.cpp=.o)))

all: build_SOIL magnus_pong

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


magnus_pong: $(OBJ)
	@echo ----------------------------
	@echo Building game...
	$(CXX) $(CFLAGS) -o magnus_pong $(OBJ) $(LDFLAGS) $(SOILDIR)/$(SOILLIB)
	@echo ----------------------------
	@echo Game built.
	@echo You can now launch the game by typing ./magnus_pong within the game\'s directory.

build_SOIL:
	@echo ----------------------------
	@echo Building SOIL \(Simple OpenGL Image Library\)...
	$(MAKE) -C $(SOILDIR)
	@echo ----------------------------
	@echo SOIL Library file created.


clean:
	@echo ----------------------------
	@echo Erasing SOIL objects files...
	$(MAKE) -C $(SOILDIR) clean
	@echo ----------------------------
	@echo Erasing magnus pong objects files...
	$(RM) count $(OBJDIR)/*.o *~
	@echo ----------------------------
	@echo Everthing has been cleaned up. 


