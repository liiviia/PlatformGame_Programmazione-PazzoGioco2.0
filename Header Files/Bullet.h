#pragma once

#include"Entity.h"

#include<set>

class Bullet: public Entity{

    public:

        Bullet(int entityIndex, float yPos, float xPos, direction direction, int shootingRange);   

        //Getters 
    
        int getBulletIndex();
        Point getMaxPos();
        bool getIsVertical();

        //Setters 

        void setBulletIndex(int index); 
        void setMaxPosY(float y);
        void setMaxPosX(float x);
        void setIsVertical(bool isVertical);

        Entity* checkBulletCollisions(list<Enemy*> enemies, Player *player);

        static void updateBullets(Game *game); 

    
    private: 

        int bulletIndex;
        Point maxPos;
        bool isVertical;
    
}; 
