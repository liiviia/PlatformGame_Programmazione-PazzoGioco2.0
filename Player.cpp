#include"./Header Files/Player.h"
#include"./Header Files/Entity.h"

Player::Player(int entityIndex, float yPos, float xPos, float yVel, float xVel, string name, string symbol, int maxHealth)
:Entity(entityIndex, yPos, xPos, yVel, xVel, name, symbol, maxHealth, 1, 1){

    setMovSpeed(0.5);
    setMaxSpeed(2);
    setJumpHeight(11);

    setAttackDelay(0);
    setCurrentDelayCounter(0);
    setAttackRange(3);
    setShootingRange(15);
    setHitChance(100);
    setHitboxRadius(1);
    
    setBudget(0);
    setPickupRadius(1);

};

Player::Player()
:Entity(0, 30, 40, 0, 0, "Default Player", "@", 5, 6, 1){

    setBudget(0);
    setPickupRadius(1);
    setMovSpeed(0.5);
    setHitboxRadius(1);

};

void Player::incrementBudget(){ this->budget += 1; }

// Getters

int   Player::getBudget(){ return this->budget; }
int   Player::getPickupRadius(){ return this->pickupRadius; }

// Setters

void Player::setBudget(int budget){ this->budget = budget; }
void Player::setPickupRadius(int radius){ this->pickupRadius = radius; }