C="-Wall"
L="-lSDL2"

pathingdemo: main.o Tile.o TileGrid.o Window.o
	g++ main.o Tile.o TileGrid.o Window.o $L -o pathingdemo

main.o: main.cpp
	g++ -c $C main.cpp

Tile.o: Tile.cpp
	g++ -c $C Tile.cpp

TileGrid.o: TileGrid.cpp
	g++ -c $C TileGrid.cpp

Window.o: Window.cpp
	g++ -c $C Window.cpp

clean:
	rm *.o pathingdemo
