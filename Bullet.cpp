#include"./Header Files/Bullet.h"
#include"./Header Files/Game.h"
#include"./Header Files/util.h"
#include"./Header Files/Entity.h"

#include<iostream>
#include<ctime>
#include<algorithm>
#include<list>

Bullet::Bullet(int entityIndex, float yPos, float xPos, direction direction, int shootingRange)
:Entity(entityIndex, "-", 5, 1){
    
    setDirection(direction); 
    setEliminationFlag(false);

    switch(direction){

        case LEFT:
            setPos(yPos, xPos - 1);
            setPrevPos(yPos, xPos - 1);
            setXVel(-1.0);
            setYVel(0);
            setMaxPosX(xPos - shootingRange);
        break;
        case RIGHT:
            setPos(yPos, xPos + 1);
            setPrevPos(yPos, xPos + 1);
            setXVel(1.0);
            setYVel(0);
            setMaxPosX(xPos + shootingRange);
        break;
        case UP:
            setPos(yPos - 1, xPos);
            setPrevPos(yPos - 1, xPos);
            setXVel(0);
            setYVel(1.0);
            setMaxPosY(yPos - shootingRange);
            setSymbol("|");
        break;
        case DOWN:
            setPos(yPos + 1, xPos);
            setPrevPos(yPos + 1, xPos);
            setXVel(0);
            setYVel(-1.0);
            setMaxPosY(yPos + shootingRange);
            setSymbol("|");
        break;

    }

}; 

//  Getters

int Bullet::getBulletIndex(){return this->bulletIndex; }
Point Bullet::getMaxPos(){ return this->maxPos; }
bool Bullet::getIsVertical(){ return this->isVertical; }

//  Setters

void Bullet::setBulletIndex(int index) {this->bulletIndex = index; }
void Bullet::setMaxPosY(float y){ this->maxPos.y = y; }
void Bullet::setMaxPosX(float x){ this->maxPos.x = x; }
void Bullet::setIsVertical(bool isVertical){ this->isVertical = isVertical; }



Entity* Bullet::checkBulletCollisions(list<Enemy*> enemies, Player *player){

    Point pos = this->getPos();
    Point prevPos = this->getPrevPos();

    /*
        ATTENZIONE: la funzione mvinch NON RESTITUISCE UN CHAR
        MA UN OGGETTO DI TIPO chtype, quindi i confronti devono
        essere effettuati tramite il valore in chtype assegnato
        al carattere specifico, in questo caso ' ' = 32.

        Spazio = 32
        Moneta = 623
        Nemico = 892
        Player = 320
        Piattaforma = 1085
    */

    float temp;
    switch(this->getDirection()){

        case RIGHT:

            temp = prevPos.x;

            while(temp <= pos.x){
                
                if((mvinch(pos.y, temp) == 892 || mvinch(pos.y, temp + 1) == 892)){
                        
                    list<Enemy*>::iterator it = find_if(enemies.begin(), enemies.end(), [pos, temp](Enemy* enemy){
                        if((enemy->getPos().y == pos.y) && (((int)enemy->getPos().x == (int)temp) || ((int)enemy->getPos().x == (int)temp + 1)))
                            return true;
                        else
                            return false;
                    });

                    if(it != enemies.end())
                        return *it;                                                              
                            
                }
                else if((mvinch(pos.y, temp) == 320 || mvinch(pos.y, temp + 1) == 320)){

                    return player;

                }                                                                                                   

                temp++;

            }

            return NULL;

        break;

        case LEFT:
            
            temp = prevPos.x;

            while(temp >= pos.x){

                if((mvinch(pos.y, temp) == 892 || mvinch(pos.y, temp - 1) == 892)){
    
                    list<Enemy*>::iterator it = find_if(enemies.begin(), enemies.end(), [pos, temp](Enemy* enemy){
                        if((enemy->getPos().y == pos.y) && (((int)enemy->getPos().x == (int)temp) || ((int)enemy->getPos().x == (int)temp - 1)))
                            return true;
                        else
                            return false;
                    });
                    
                    if(it != enemies.end())
                        return *it;
                    
                }
                else if((mvinch(pos.y, temp) == 320 || mvinch(pos.y, temp - 1) == 320)){

                    return player;

                }

                temp--;

            }

            return NULL;

        break;

        case UP:

            temp = prevPos.y;

            while(temp >= pos.y){

                if(mvinch(temp, pos.x) == 892 || mvinch(temp - 1, pos.x) == 892){

                    list<Enemy*>::iterator it = find_if(enemies.begin(), enemies.end(), [pos, temp](Enemy* enemy){
                        if(abs(enemy->getPos().x - pos.x) <= 0.6 && (((int)enemy->getPos().y == (int)temp) || ((int)enemy->getPos().y == (int)temp - 1)))
                            return true;
                        else
                            return false;
                    });
                    
                    if(it != enemies.end())
                        return *it;

                }
                else if(mvinch(temp, pos.x) == 1085){

                    this->setEliminationFlag(true);
                    return NULL;

                }

                temp--;
                
            }

            return NULL;

        break;

        case DOWN:

            temp = prevPos.y;

            while(temp <= pos.y){

                if(mvinch(temp, pos.x) == 892 || mvinch(temp + 1, pos.x) == 892){

                    list<Enemy*>::iterator it = find_if(enemies.begin(), enemies.end(), [pos, temp](Enemy* enemy){
                        if(abs(enemy->getPos().x - pos.x) <= 0.6 && (((int)enemy->getPos().y == (int)temp) || ((int)enemy->getPos().y == (int)temp + 1)))
                            return true;
                        else
                            return false;
                    });
                    
                    if(it != enemies.end())
                        return *it;

                }
                else if(mvinch(temp, pos.x) == 1085){

                    this->setEliminationFlag(true);
                    return NULL;

                }else if((mvinch(temp, pos.x) == 320 || mvinch(temp + 1, pos.x) == 320)){

                    return player;

                }

                temp++;
                
            }

            return NULL;

        break;

    }

    return NULL;

}

void Bullet::updateBullets(Game *game){

    list<Bullet*> *bullets = game->getBulletList();

    Point prevPos;

    for(list<Bullet*>::iterator it = bullets->begin(); it != bullets->end(); ++it){

        if((*it)->getVel().x != 0){
            if((*it)->getDirection() == RIGHT) //controllo direzione 
                (*it)->setXVel((*it)->getVel().x);
            else if((*it)->getDirection() == LEFT)
                (*it)->setXVel((*it)->getVel().x);
                
        }

        (*it)->setPrevPos((*it)->getPos().y, (*it)->getPos().x);

        (*it)->setPos((*it)->getPos().y - (*it)->getVel().y, (*it)->getPos().x + (*it)->getVel().x);

        // flaggo per l'eliminazione dei bullets che escono dallo schermo 
        if((*it)->getPos().x < 0 || (*it)->getPos().x > getmaxx(stdscr) || (*it)->getPos().y < 0 || (*it)->getPos().y > getmaxy(stdscr))
            (*it)->setEliminationFlag(true);
        else if((*it)->getDirection() != UP){

            if((*it)->getDirection() == RIGHT){
                if((*it)->getPos().x >= (*it)->getMaxPos().x)
                    (*it)->setEliminationFlag(true);
            }
            else if((*it)->getDirection() == LEFT){
                if((*it)->getPos().x <= (*it)->getMaxPos().x)
                    (*it)->setEliminationFlag(true);
            }

        }
        else{

            if((*it)->getPos().y <= (*it)->getMaxPos().y)
                (*it)->setEliminationFlag(true);

        }
    
    }
        
}