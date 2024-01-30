#include"./Header Files/Enemy.h"

#include"./Header Files/Entity.h"
#include"./Header Files/Player.h"
#include"./Header Files/Platform.hpp"
#include"./Header Files/util.h"
#include"./Header Files/Game.h"

#include<ctime>
#include<iostream>
#include<list>
#include<curses.h>
#include<stdlib.h>
#include<math.h>

Enemy::Enemy(int entityIndex, enemyType enemyType, float y, float x, float yVel, float xVel, string name, int pairNum)
:Entity(entityIndex, y, x, yVel, xVel, name, "|", 3, 1.5)
{

    setEnemyType(enemyType);

    switch(enemyType){

        case WALKER:

            setMaxSpeed(0.15);
            setAttackRange(0);
            setShootingRange(0);
            setDmgPerHit(1);
            setHitChance(70);  
            setMovSpeed(0.02);
            setHitboxRadius(1);
            setAttackDelay(300);
            setCurrentDelayCounter(0);
            setMaxHealth(2);
            setCurHealth(getMaxHealth());
            setJumpHeight(10);

        break;

        case MELEE:
            setMaxSpeed(0.15);
            setAttackRange(2);
            setShootingRange(0);
            setDmgPerHit(1);
            setHitChance(70);  
            setMovSpeed(0.02);
            setHitboxRadius(1);
            setAttackDelay(300);
            setCurrentDelayCounter(0);
            setMaxHealth(2);
            setCurHealth(getMaxHealth());
            setJumpHeight(10);

        break;

        case RANGED:

            setMaxSpeed(0.15);
            setShootingRange(15);
            setAttackRange(0);
            setDmgPerHit(1);
            setHitChance(100);  
            setMovSpeed(0.02);
            setHitboxRadius(1);
            setAttackDelay(100);
            setCurrentDelayCounter(0);
            setMaxHealth(2);
            setCurHealth(getMaxHealth());
            setJumpHeight(10);

        break;

        case FLYING:

            setOriginalYPos(y);
            setMaxSpeed(0.15);
            setShootingRange(0);
            setAttackRange(25);
            setDmgPerHit(1);
            setHitChance(100);  
            setMovSpeed(0.02);
            setHitboxRadius(1);
            setAttackDelay(200);
            setCurrentDelayCounter(0);
            setMaxHealth(2);
            setCurHealth(getMaxHealth());
            setJumpHeight(0);

        break;

        case FLYINGRANGED:

            setOriginalYPos(y);
            setMaxSpeed(0.15);
            setShootingRange(15);
            setAttackRange(0);
            setDmgPerHit(1);
            setHitChance(0);  
            setMovSpeed(0.02);
            setHitboxRadius(1);
            setAttackDelay(200);
            setCurrentDelayCounter(0);
            setMaxHealth(2);
            setCurHealth(getMaxHealth());
            setJumpHeight(0);

        break;

    }
    
};

bool Enemy::isInRange(Player *player){

    switch(this->getEnemyType()){

        case MELEE:

            if(abs(this->getPos().x - player->getPos().x) <= this->getAttackRange())
                return true;
            else
                return false;

        break;

        case RANGED:

            if(abs(this->getPos().x - player->getPos().x) <= this->getShootingRange())
                return true;
            else
                return false;

        break;

        case FLYING:

            if(abs(this->getPos().x - player->getPos().x) <= 4 && abs(this->getPos().y - player->getPos().y) <= this->getAttackRange())
                return true;
            else
                return false;

    }

    return false;    
    
}

bool Enemy::isInShootingRange(Player *player){

    if(abs(this->getPos().x - player->getPos().x) <= this->getShootingRange() && abs(this->getPos().y - player->getPos().y) <= this->getShootingRange())
        return true;
    else
        return false;

}

void Enemy::findPath(list<Enemy*> enemies, Platform* platforms, Player &player, Game *game){
    Platform pl = Platform();
    Platform en = Platform();
    Point curPlayerPos = player.getPos();
    Enemy *selEnemy;
    obPointer playerPlatform = platforms -> getCurPlatform(player.getPos());
    pl.setObPointer(playerPlatform);
    for(list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){

        selEnemy = *it;
        Point selEnemyPos = selEnemy->getPos();
        Point selEnemyPrevPos = selEnemy->getPrevPos();
        float maxSpeed = selEnemy->getMaxSpeed();
        obPointer enemyPlatform = platforms -> getCurPlatform(selEnemy -> getPos());  
        en.setObPointer(enemyPlatform); 
    
        /* 
        
            In questo if controllo se il nemico è all'interno del parallelepipedo con base la piattaforma su cui
            è situato il player e altezza tutto lo schermo. Se lo è, continua ad inseguirlo così
            se il nemico si trova su una piattaforma sopra a quella del player, riesce a raggiungerlo buttandosi sotto.
            
            Nella condizione uso maggiore perchè ncurses inizia a disegnare dall'alto, quindi la prima riga del terminale ha indice 0
        
        */

        

        switch(selEnemy->getEnemyType()){

            case WALKER: case MELEE: case RANGED:

                if(playerPlatform != NULL){

                    if(enemyPlatform != NULL){
 
                        short int isInPlatformAreaValue = isInPlatformArea(playerPlatform, enemyPlatform);
    
                        //  Controllo se sono in una piattaforma fuori dall'area
                        if(isInPlatformAreaValue != 0 && !selEnemy->isInRange(&player)){
    
                            selEnemy->setIsMoving(true);
    
                            //  Forza frenante se sto andando nella direzione giusta ma ho ancora momentum opposto
                            if(selEnemy->getVel().x < 0 && (selEnemy->getDirection() == RIGHT)
                            || selEnemy->getVel().x > 0 && (selEnemy->getDirection() == LEFT))
                                selEnemy->setIsMoving(false);
    
                            //  Caso in cui il nemico è su un'altra piattaforma
                            if(!selEnemy->getIsFalling() && playerPlatform != enemyPlatform){
                                
                                if(selEnemyPos.x <= pl.getEnd().x - 2 && selEnemyPos.x >= pl.getStart().x + 2){
                                    switch(isInPlatformAreaValue){
    
                                        case 1:
    
                                            if(!en.getIsGround()){
                                                selEnemy->setIsFalling(true);
                                                selEnemy->setYPos(selEnemy->getPos().y + 1);
                                                selEnemy->setYVel(selEnemy->getVel().y - 1);
                                            }
    
                                        break;
    
                                        case -1:
    
                                            if(pl.getStart().y > (selEnemy->getPos().y - selEnemy->getJumpHeight()))
                                                selEnemy->setYVel(selEnemy->getVel().y + (selEnemy->getJumpHeight() * game->getGravity()));
    
                                        break;
    
                                    }
                                }
                            }
    
                            //  Mi sposto sulla piattaforma corrente
                            if(selEnemyPos.x > curPlayerPos.x)
                                if(selEnemy->getVel().x > -(selEnemy->getMaxSpeed())){
                                    selEnemy->setXVel(selEnemy->getVel().x - selEnemy->getMovSpeed());
                                    selEnemy->setDirection(LEFT);    
                                }
                                else 
                                    selEnemy->setXVel(selEnemy->getVel().x + selEnemy->getMovSpeed());
                            else
                                if(selEnemy->getVel().x < selEnemy->getMaxSpeed()){
                                    selEnemy->setXVel(selEnemy->getVel().x + selEnemy->getMovSpeed()); 
                                    selEnemy->setDirection(RIGHT);
                                }
                                else 
                                    selEnemy->setXVel(selEnemy->getVel().x - selEnemy->getMovSpeed());
    
                        }
                    }
                    else{
                        selEnemy->setIsMoving(false);
                    }
                }
                else{
                    selEnemy->setXVel(0);
                    selEnemy->setIsMoving(false);
                }
            
            break;

            case FLYING:
            {

                    selEnemy->setIsMoving(true);

                    if(abs(selEnemyPos.x - curPlayerPos.x) > 0.8){
                        if(selEnemyPos.x > curPlayerPos.x)
                            if(selEnemy->getVel().x > -(selEnemy->getMaxSpeed())){
                                selEnemy->setXVel(selEnemy->getVel().x - selEnemy->getMovSpeed());
                                selEnemy->setDirection(LEFT);    
                            }
                            else 
                                selEnemy->setXVel(selEnemy->getVel().x + selEnemy->getMovSpeed());
                        else
                            if(selEnemy->getVel().x < selEnemy->getMaxSpeed()){
                                selEnemy->setXVel(selEnemy->getVel().x + selEnemy->getMovSpeed()); 
                                selEnemy->setDirection(RIGHT);
                            }
                            else 
                                selEnemy->setXVel(selEnemy->getVel().x - selEnemy->getMovSpeed());
                    }

                    //  Se la pos attuale è > di quella originale allora è sotto e viceversa

                    float originalYPos = selEnemy->getOriginalYPos();

                    float diff = abs(selEnemyPos.y - originalYPos);
                    
                    if(selEnemyPos.y < originalYPos)
                        selEnemy->setYVel(selEnemy->getVel().y - selEnemy->getMovSpeed());

                    else if(selEnemyPos.y > originalYPos)
                        selEnemy->setYVel(selEnemy->getVel().y + selEnemy->getMovSpeed());
                    
                    if(diff <= 1){
                    
                        selEnemy->setYVel(0);
                        selEnemy->setYPos(originalYPos);
                    
                    }

                break;

            }

            case FLYINGRANGED:
            {

                    selEnemy->setIsMoving(true);
                    
                    if(abs(selEnemyPos.x - curPlayerPos.x) > 0.8){
                        if(selEnemyPos.x > curPlayerPos.x)
                            if(selEnemy->getVel().x > -(selEnemy->getMaxSpeed())){
                                selEnemy->setXVel(selEnemy->getVel().x - selEnemy->getMovSpeed());
                                selEnemy->setDirection(LEFT);    
                            }
                            else 
                                selEnemy->setXVel(selEnemy->getVel().x + selEnemy->getMovSpeed());
                        else
                            if(selEnemy->getVel().x < selEnemy->getMaxSpeed()){
                                selEnemy->setXVel(selEnemy->getVel().x + selEnemy->getMovSpeed()); 
                                selEnemy->setDirection(RIGHT);
                            }
                            else 
                                selEnemy->setXVel(selEnemy->getVel().x - selEnemy->getMovSpeed());
                    }

                    //  Se la pos attuale è > di quella originale allora è sotto e viceversa

                    float originalYPos = selEnemy->getOriginalYPos();

                    float diff = abs(selEnemyPos.y - originalYPos);

                    if(diff >= 1){
                        if(selEnemyPos.y < originalYPos)
                            selEnemy->setYVel(selEnemy->getVel().y - selEnemy->getMovSpeed());
                        else
                            selEnemy->setYVel(selEnemy->getVel().y + selEnemy->getMovSpeed());

                        // Stop the enemy from oscillating once it reaches its original Y position
                        if(abs(selEnemyPos.y - originalYPos) < 0.9)
                            selEnemy->setYVel(0);
                    }
                    else {
                        selEnemy->setYPos(originalYPos);
                        // selEnemy->setYVel(0);
                    }

                break;

            }
        }
    }
}


void Enemy::addEnemy(Game* game, Enemy::enemyType enemyType, float y, float x, float yVel, float xVel, string name, int pairNum){

    Enemy *enemy = new Enemy(game->getGlobalEntityCount(), enemyType, y, x, yVel, xVel, name, pairNum);
    game->getEnemyList()->push_back(enemy);

    game->incrementGlobalEntityCount();

}

void Enemy::spawnEnemies(Game *game, int n, set<float> &recordedPos, Enemy::enemyType enemyType, Platform* platforms){

    srand(time(NULL));
    Platform* tmp;
    platforms -> rewindPlatformList();
    tmp = platforms;    
    for(int i = 0; i < n; i++){
        
        if(!tmp->checkNext())
            tmp->rewindPlatformList();

        float yPos, xPos;

        switch(enemyType){

            case WALKER: case MELEE: case RANGED:

                yPos = tmp -> getStart().y - 1;
       
                do{

                    xPos = rand()%(tmp ->getLength() - 2) + ((int)tmp -> getStart().x + 2);

                }while(isInSet(recordedPos, xPos) || isInSafeZone(*game->getPlayer(), xPos));

                recordedPos.insert(xPos);

            break;

            case FLYING: case FLYINGRANGED:

                yPos = 10;

                do{

                    xPos = rand()%(getmaxx(stdscr) - 10) + 10;

                }while(isInSet(recordedPos, xPos));

                recordedPos.insert(xPos);

            break;

        }

        Enemy *newEnemy = new Enemy(game->getGlobalEntityCount(), enemyType, yPos, xPos, 0, 0, "Enemy", 3); 
        game->getEnemyList()->push_back(newEnemy);

        game->incrementGlobalEntityCount();

        tmp -> advancePlatformList();

    }

}

// Getters

Enemy::enemyType Enemy::getEnemyType(){ return this->type; }
float            Enemy::getOriginalYPos(){ return this->originalYPos; }

// Setters

void Enemy::setEnemyType(Enemy::enemyType type){ this->type = type; }
void Enemy::setOriginalYPos(float pos){ this->originalYPos = pos; }

