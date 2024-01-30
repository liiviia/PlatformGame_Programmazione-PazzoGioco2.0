#pragma once

#include"Player.h"
#include"Enemy.h"
#include"Coin.h"
#include"Platform.hpp"
#include"Bullet.h"
#include"Animation.h"
#include"util.h"
#include"MapClass.hpp"

#include<curses.h>
#include<list>

class Game{

    public:

        enum gameState { MENU, RUNNING, WIN, LOSE, QUIT };

        const float gravity = 0.28;  // Default = 0.28
        const float friction = 0.2;  // Default = 0.15
        bool invertedGrav = false;

        int globalEntityCount;

        Game(gameState g, int yMax, int xMax);

        void  spawnEntities(int nCoins, int nEnemies, Platform* platforms);
        void  moveEntities(Platform* platforms);
        void  displayEntities(MapClass level);
        
        void checkCollisions(Platform* platforms, Entity *entity, bool &updIsFalling);
          
        void  solveCollisions(Platform* platforms, list<Enemy*> enemies);
        void  debugDisplay(MapClass level);

        void incrementGlobalEntityCount();
        void increaseGlobalEntityCount(int n);

        void updateDelayCounters();

        // Getters

        float            getGravity();
        float            getFriction();

        gameState        getGameState();
        bool             getInvertedGrav();
        int              getGlobalEntityCount();
        Player           *getPlayer();
        list<Enemy*>     *getEnemyList();
        list<Coin*>      *getCoinList();
        list<Bullet*>    *getBulletList(); 
        list<Animation*> *getAnimationList();
        int               getGlobalAnimationCount();
        int               getYMax();
        int               getXMax();

        // Setters
        void setGameState(gameState g);
        void setInvertedGrav(bool b);
        void setGlobalEntityCount(int count);
        void setPlayer(float yPos, float xPos, float yVel, float xVel, string name, string symbol, int maxHealth);
        void setGlobalAnimationCount(int index);
        void setYMax(int yMax);
        void setXMax(int xMax);
        
    private:

        gameState state;

        int yMax, xMax;

        Player player;
        list<Enemy*> enemies;
        list<Coin*> coins;
        list<Bullet*> bullets; 
        list<Animation*> animations;
        int globalAnimationCount;

};
