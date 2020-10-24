EXEC_NAME=pathing
C_FLAGS=-Wall
L_FLAGS=-lSDL2

$(EXEC_NAME): main.o Tile.o TileGrid.o Window.o
	g++ main.o Tile.o TileGrid.o Window.o -o $(EXEC_NAME) $(L_FLAGS)

main.o: main.cpp
	g++ $(C_FLAGS) -c main.cpp

Tile.o: Tile.cpp
	g++ $(C_FLAGS) -c Tile.cpp

TileGrid.o: TileGrid.cpp
	g++ $(C_FLAGS) -c TileGrid.cpp

Window.o: Window.cpp
	g++ $(C_FLAGS) -c Window.cpp

clean:
	rm *.o $(EXEC_NAME)
