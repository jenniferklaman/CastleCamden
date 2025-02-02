CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/mingw64/include
LDFLAGS = -L/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = Main.cpp GameMenu.cpp CharacterSelection.cpp Game.cpp Player.cpp Enemy.cpp
OBJ = $(SRC:.cpp=.o)

EXE = CastleCamden

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(OBJ) $(EXE)
