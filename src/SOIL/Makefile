SRCDIR= .
OBJDIR= obj
LIBNAME = SOIL.a

CXX = gcc

CXXFLAGS = -O2 -s -Wall -Wno-unused-but-set-variable -Wno-unused-result

SRCNAMES = \
  image_helper.c \
  stb_image_aug.c  \
  image_DXT.c \
  SOIL.c \


OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRCNAMES:.c=.o)))

all: $(LIBNAME)

$(LIBNAME): $(OBJ)
	ar r $(LIBNAME) $(OBJ)

./$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -o ./$@ -c $<

clean: 
	$(RM) count ./obj/*.o *~
	