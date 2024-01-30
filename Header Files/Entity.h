#pragma once

#include"util.h"

#include<list>
#include<string>
using namespace std;

class Game;
class Player;
class Enemy;
class Bullet;

class Entity{

    private:
    
        int entityIndex;
        string name;
        string symbol;
        int pairNum;
        bool eliminationFlag;

        Point pos, vel;
        Point prevPos;
        direction dir;
        float movSpeed, maxSpeed;
        bool isFalling, isMoving;
        int jumpHeight;
        
        int attackRange, dmgPerHit, shootingRange, hitChance;
        int attackDelay, currentDelayCounter;
        int maxHealth, curHealth;
        int hitboxRadius;

    public:

        Entity(int entityIndex, float y, float x, float yVel, float xVel, string name, string symbol, int maxHealth, int pairNum, int radius);
        Entity(int entityIndex, float y, float x, float yVel, float xVel, string name, string symbol, int pairNum, int radius);
        Entity(int entityIndex, float y, float x, float yVel, float xVel, string name, string symbol, int pairNum);
        Entity(int entityIndex, float y, float x, float yVel, float xVel, string symbol, int pairNum, int radius);
        Entity(int entityIndex, string symbol, int pairNum, int radius);
        
        // Getters
        int getEntityIndex();
        string getName();
        string getSymbol();
        int getPairNum();
        bool getEliminationFlag();
        
        Point getPos();
        Point getVel();
        Point getPrevPos();
        direction getDirection();
        float getMovSpeed();
        float getMaxSpeed();
        bool getIsFalling();
        bool getIsMoving();
        int getJumpHeight();
        
        int getAttackRange();
        int getDmgPerHit();
        int getShootingRange(); 
        int getHitChance();
        int getAttackDelay();
        int getCurrentDelayCounter();
        int getMaxHealth();
        int getCurHealth();
        int getHitboxRadius();

        // Setters
        void setEntityIndex(int index);
        void setName(string name);
        void setSymbol(string symbol);
        void setPairNum(int pairNum);
        void setEliminationFlag(bool flag);
        
        void setYPos(float y);
        void setXPos(float x);
        void setPos(Point p);
        void setPos(float y, float x);
        void setYVel(float yVel);
        void setXVel(float xVel);
        void setVel(Point v);
        void setVel(float yVel, float xVel);
        void setPrevYPos(float y);
        void setPrevXPos(float x);
        void setPrevPos(Point p);
        void setPrevPos(float y, float x);
        void setDirection(direction direction);
        void setMovSpeed(float speed);
        void setMaxSpeed(float speed);
        void setIsFalling(float isFalling);
        void setIsMoving(bool isMoving);
        void setJumpHeight(int height);

        void setAttackRange(int range);
        void setDmgPerHit(int dmg);
        void setShootingRange(int range);
        void setHitChance(int chance);
        void setAttackDelay(int delay);
        void setCurrentDelayCounter(int counter);
        void setMaxHealth(int maxHealth);
        void setCurHealth(int curHealth);
        void setHitboxRadius(int radius);

        void incrementDelayCounter();

        bool attack(int range, list<Enemy*> enemies, Player *player, Game *game);
        void isHit(int dmg, direction direction, Game *game);

        Entity* groundAttackTarget(float temp, Point entityPos, direction entityDirection, int range, list<Enemy*> enemies, Player *player);
        void shoot(int globalEntityCount, list<Bullet*> *bullets, direction bulletDirection);

        void entityPhysics(Game *game, bool ignoreGravity);

};