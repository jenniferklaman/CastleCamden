# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/mingw64/include

# Linker flags for SFML
LDFLAGS = -L/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source and object files
SRC = Main.cpp GameMenu.cpp CharacterSelection.cpp Game.cpp Player.cpp Enemy.cpp
OBJ = $(SRC:.cpp=.o)

# Executable name
EXE = CastleCamden

# Default build rule
all: $(EXE)

# Link executable
$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE) $(LDFLAGS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game after compilation
run: $(EXE)
	./$(EXE)

# Clean build files
clean:
	rm -f $(OBJ) $(EXE)
