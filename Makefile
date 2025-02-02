# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -I/mingw64/include

# Linker Flags (SFML libraries)
LDFLAGS = -L/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = Main.cpp GameMenu.cpp CharacterSelection.cpp

# Output executable name
OUT = CastleCamden

# Default target (compiles the program)
all: $(OUT)

# Compilation command
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

# Run the game
run: all
	./$(OUT)

# Clean the compiled files
clean:
	rm -f $(OUT)
