#pragma once

#include"Entity.h"

#include<list>
#include<set>

class Coin : public Entity{

    public:

        Coin(int entityIndex, float yPos, float xPos, float yVel, float xVel);

        void addCoin(Game *game, float yPos, float xPos, float yVel, float xVel);

        static void spawnCoins(Game *game, int n, set<float> &recordedPos, Platform* platforms);

        // Getters

        int getCoinIndex();

        // Setters

        void setCoinIndex(int index);

    private:

        int coinIndex;

};