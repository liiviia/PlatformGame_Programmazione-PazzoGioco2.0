main: main.o Game.o Entity.o Player.o Enemy.o Platform.o Coin.o Bullet.o Animation.o util.o WindowGenerator.o MainMenu.o NewGameMenuClass.o ContinueMenu.o MapClass.o ChunkClass.o
	g++ main.o Game.o Entity.o Player.o Enemy.o Platform.o Coin.o Bullet.o Animation.o util.o WindowGenerator.o MainMenu.o NewGameMenuClass.o ContinueMenu.o MapClass.o ChunkClass.o Shop.o -lncurses -o main 

main.o: main.cpp
	g++ -c main.cpp

Game.o: Game.cpp
	g++ -c Game.cpp

Entity.o: Entity.cpp
	g++ -c Entity.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Enemy.o: Enemy.cpp
	g++ -c Enemy.cpp

Coin.o: Coin.cpp
	g++ -c Coin.cpp

Bullet.o: Bullet.cpp
	g++ -c Bullet.cpp

Platform.o: Platform.cpp
	g++ -c Platform.cpp

Animation.o: Animation.cpp
	g++ -c Animation.cpp

util.o: util.cpp
	g++ -c util.cpp

MainMenu.o: MainMenu.cpp
	g++ -c MainMenu.cpp

WindowGenerator.o: WindowGenerator.cpp
	g++ -c WindowGenerator.cpp

NewGameMenuClass.o: NewGameMenuClass.cpp
	g++ -c NewGameMenuClass.cpp

ContinueMenu.o: ContinueMenu.cpp
	g++ -c ContinueMenu.cpp

MapClass.o: MapClass.cpp
	g++ -c MapClass.cpp

ChunkClass.o: ChunkClass.cpp
	g++ -c ChunkClass.cpp

Shop.o: Shop.cpp
	g++ -c Shop.cpp

clean:
	rm *.o

run:
	./main
