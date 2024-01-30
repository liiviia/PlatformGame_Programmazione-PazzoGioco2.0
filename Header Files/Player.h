#pragma once

#include"Entity.h"

#include<list>

class Player : public Entity{

    public:

        Player();
        Player(int entityIndex, float yPos, float xPos, float yVel, float xVel, string name, string symbol, int maxHealth);

        void incrementBudget();
        
        // Getters

        int getBudget();
        int getPickupRadius();

        // Setters

        void setBudget(int budget);
        void setPickupRadius(int radius);

    private:

        int budget;
        int pickupRadius;
        float speed;

};