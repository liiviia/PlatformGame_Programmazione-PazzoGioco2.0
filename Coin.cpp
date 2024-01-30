#include"./Header Files/Coin.h"
#include"./Header Files/util.h"
#include"./Header Files/Game.h"

#include<list>
#include<ctime>
#include<iostream>
using namespace std;

Coin::Coin(int entityIndex, float yPos, float xPos, float yVel, float xVel)
:Entity(entityIndex, yPos, xPos, yVel, xVel, "o", 7, 1){

    setMaxSpeed(2);

};

void Coin::addCoin(Game *game, float yPos, float xPos, float yVel, float xVel){

    Coin *coin = new Coin(game->getGlobalEntityCount(), yPos, xPos, yVel, xVel);
    game->getCoinList()->push_back(coin);

    game->incrementGlobalEntityCount();

}

void Coin::spawnCoins(Game *game, int n, set<float> &recordedPos, Platform* platforms){
    
    srand(time(NULL));
    Platform* tmp;
    platforms -> rewindPlatformList();
    tmp = platforms;    
    for(int i = 0; i < n; i++){
        
        if(!tmp->checkNext())
            tmp->rewindPlatformList();

        float yPos, xPos;

        yPos = tmp -> getStart().y - 1;
       
        do{

            xPos = rand()%(tmp ->getLength() - 2) + ((int)tmp -> getStart().x + 2);

        }while(isInSet(recordedPos, xPos));

        recordedPos.insert(xPos);
        
        Coin *newCoin = new Coin(game->getGlobalEntityCount(), yPos, xPos, 0, 0); 
        game->getCoinList()->push_back(newCoin);

        game->incrementGlobalEntityCount(); 

        tmp -> advancePlatformList();

    }


}

// Getters

int Coin::getCoinIndex(){ return this->coinIndex; }

// Setters

void Coin::setCoinIndex(int index){ this->coinIndex = index; }