#pragma once

#include"Entity.h"

#include<string>
#include<list>
#include<set>

class Player;
class Platform;

class Enemy : public Entity{

    public:

        enum enemyType { WALKER , MELEE , RANGED , FLYING , FLYINGRANGED };

        Enemy(int entityIndex, enemyType enemyType, float y, float x, float yVel, float xVel, string name, int pairNum);

        bool isInRange(Player *player);

        bool isInShootingRange(Player *player);
        
        static void findPath(list<Enemy*> enemies, Platform* platforms, Player &player, Game *game);
        
        void addEnemy(Game *game, Enemy::enemyType enemyType, float y, float x, float yVel, float xVel, string name, int pairNum);

        static void spawnEnemies(Game *game, int n, set<float> &recordedPos, enemyType enemyType, Platform* platforms);

        
        // Getters

        enemyType getEnemyType();
        float     getOriginalYPos();

        // Setters

        void setEnemyType(enemyType type);
        void setOriginalYPos(float pos);

    private:

        enemyType type;
        float originalYPos; //  Usato dai nemici volanti per tornare in quota

};