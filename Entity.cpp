#include"./Header Files/Entity.h"
#include"./Header Files/Game.h"
#include"./Header Files/Bullet.h"
#include <iostream>
#include <curses.h>
#include <algorithm>

//  Costruttore standard
Entity::Entity(int entityIndex, float y, float x, float yVel, float xVel, string name, string symbol, int maxHealth, int pairNum, int radius){

    setEntityIndex(entityIndex);
    setYPos(y);
    setXPos(x);
    setIsFalling(false);
    setPrevPos(y, x);
    setYVel(yVel);
    setXVel(xVel);
    setName(name);
    setSymbol(symbol);
    setMaxHealth(maxHealth);
    setCurHealth(maxHealth);
    setPairNum(pairNum);
    setHitboxRadius(radius);
    setEliminationFlag(false);

}

//  Costruttore senza maxHealth, da specificare nel costruttore della classe figlia
Entity::Entity(int entityIndex, float y, float x, float yVel, float xVel, string name, string symbol, int pairNum, int radius){

    setEntityIndex(entityIndex);
    setYPos(y);
    setXPos(x);
    setIsFalling(false);
    setPrevPos(y, x);
    setYVel(yVel);
    setXVel(xVel);
    setName(name);
    setSymbol(symbol);
    setPairNum(pairNum);
    setHitboxRadius(radius);
    setEliminationFlag(false);

}

// Costruttore senza maxHealth e radius, entrambi da specificare nel costruttore della classe figlia
Entity::Entity(int entityIndex, float y, float x, float yVel, float xVel, string name, string symbol, int pairNum){

    setEntityIndex(entityIndex);
    setYPos(y);
    setXPos(x);
    setIsFalling(false);
    setPrevPos(y, x);
    setYVel(yVel);
    setXVel(xVel);
    setName(name);
    setSymbol(symbol);
    setPairNum(pairNum);
    setEliminationFlag(false);

}

//  Costruttore di default usato prevalentemente da Coin
Entity::Entity(int entityIndex, float y, float x, float yVel, float xVel, string symbol, int pairNum, int radius){

    setEntityIndex(entityIndex);
    setYPos(y);
    setXPos(x);
    setIsFalling(false);
    setPrevPos(y, x);
    setYVel(yVel);
    setXVel(xVel);
    setSymbol(symbol);
    setPairNum(pairNum);
    setHitboxRadius(radius);
    setEliminationFlag(false);

}

//  Costruttore di default usato prevalentemente da Bullet
Entity::Entity(int entityIndex, string symbol, int pairNum, int radius){

    setEntityIndex(entityIndex);
    setIsFalling(false);
    setSymbol(symbol);
    setPairNum(pairNum);
    setHitboxRadius(radius);
    setEliminationFlag(false);

}
  
// Getters
int         Entity::getEntityIndex(){ return this->entityIndex; }
string      Entity::getName(){ return this->name; }
string      Entity::getSymbol(){ return this->symbol; }
int         Entity::getPairNum(){ return this->pairNum; }
bool        Entity::getEliminationFlag(){ return this->eliminationFlag; }

Point       Entity::getPos(){ return this->pos; }
Point       Entity::getVel(){ return this->vel; }
Point       Entity::getPrevPos(){ return this->prevPos; }
direction   Entity::getDirection(){ return this->dir; }
float       Entity::getMovSpeed(){ return this->movSpeed; }
float       Entity::getMaxSpeed(){ return this->maxSpeed; }
bool        Entity::getIsFalling(){ return this->isFalling; }
bool        Entity::getIsMoving(){ return this->isMoving; }
int         Entity::getJumpHeight(){ return this->jumpHeight; }

int         Entity::getAttackRange(){ return this->attackRange; }
int         Entity::getDmgPerHit(){ return this->dmgPerHit; }
int         Entity::getShootingRange(){ return this->shootingRange; }
int         Entity::getHitChance(){ return this->hitChance; }
int         Entity::getAttackDelay(){ return this->attackDelay; }
int         Entity::getCurrentDelayCounter(){ return this->currentDelayCounter; }
int         Entity::getMaxHealth(){ return this->maxHealth; }
int         Entity::getCurHealth(){ return this->curHealth; }
int         Entity::getHitboxRadius(){ return this->hitboxRadius; }


// Setters
void Entity::setEntityIndex(int index){ this->entityIndex = index; }
void Entity::setName(string name){ this->name = name; }
void Entity::setSymbol(string symbol){ this->symbol = symbol; }
void Entity::setPairNum(int pairNum){ this->pairNum = pairNum; }
void Entity::setEliminationFlag(bool flag){ this->eliminationFlag = flag; }

void Entity::setYPos(float y){ this->pos.y = y; }
void Entity::setXPos(float x){ this->pos.x = x; }
void Entity::setPos(Point p){ this->pos.y = p.y; this->pos.x = p.x; }
void Entity::setPos(float y, float x){ this->pos.y = y; this->pos.x = x; }
void Entity::setYVel(float yVel){ this->vel.y = yVel; }
void Entity::setXVel(float xVel){ this->vel.x = xVel; }
void Entity::setVel(Point v){ this->vel.y = v.y; this->vel.x = v.x; }
void Entity::setVel(float yVel, float xVel){ this->vel.y = yVel; this->vel.x = xVel; }
void Entity::setPrevYPos(float y){ this->prevPos.y = y; }
void Entity::setPrevXPos(float x){ this->prevPos.x = x; }
void Entity::setPrevPos(Point p){ this->prevPos.y = p.y; this->prevPos.x = p.x; }
void Entity::setPrevPos(float y, float x){ this->prevPos.y = y; this->prevPos.x = x; }
void Entity::setDirection(direction direction){ this->dir = direction; }
void Entity::setMovSpeed(float speed){ this->movSpeed = speed; }
void Entity::setMaxSpeed(float speed){ this->maxSpeed = speed; }
void Entity::setIsFalling(float isFalling){ this->isFalling = isFalling; }
void Entity::setIsMoving(bool isMoving){ this->isMoving = isMoving; }
void Entity::setJumpHeight(int height){ this->jumpHeight = height; }

void Entity::setAttackRange(int range){ this->attackRange = range; }
void Entity::setDmgPerHit(int dmg){ this->dmgPerHit = dmg; }
void Entity::setShootingRange(int range){ this->shootingRange = range; }
void Entity::setHitChance(int chance){ this->hitChance = chance; }
void Entity::setAttackDelay(int delay){ this->attackDelay = delay; }
void Entity::setCurrentDelayCounter(int counter){ this->currentDelayCounter = counter; }
void Entity::setMaxHealth(int maxHealth){ this->maxHealth = maxHealth; }
void Entity::setCurHealth(int curHealth){ this->curHealth = curHealth; }
void Entity::setHitboxRadius(int radius){ this->hitboxRadius = radius; }

void Entity::incrementDelayCounter(){ this->currentDelayCounter += 1; }

void Entity::isHit(int dmg, direction direction, Game *game){
 
    // dmg = valore del danno

    setIsMoving(false);

    switch(direction){

        case RIGHT: case DOWN:
            setXVel(0.8);
            setYVel(1);
        break;

        case LEFT:
            setXVel(-0.8);
            setYVel(1);
        break;

        case UP:
            setYVel(1);
            setIsFalling(true);
        break;

    }
    
    setCurHealth(getCurHealth() - dmg);

    if(getCurHealth() <= 0){

        setEliminationFlag(true);
        
        Point curEntityPos = getPos();
        for(int i = 0; i < 4; i++){

            float randYVel = randomFloatInRange(0.5f, 1.5f);
            float randXVel = randomFloatInRange(-0.7f, 0.7f);

            Coin *coin = new Coin(game->getGlobalEntityCount(), curEntityPos.y, curEntityPos.x, randYVel, randXVel);
            coin->setIsFalling(true);
            game->getCoinList()->push_back(coin);

        }    
    }

}

//  vert -> variabile booleana per lo sparo verticale
void Entity::shoot(int globalEntityCount, list<Bullet*> *bullets, direction bulletDirection){

    if(getCurrentDelayCounter() >= getAttackDelay()){

        Bullet *bullet = new Bullet(globalEntityCount, getPos().y, getPos().x, bulletDirection, getShootingRange());
                        
        bullets->push_back(bullet);

        setCurrentDelayCounter(0);
    
    }

}

Entity* Entity::groundAttackTarget(float temp, Point entityPos, direction entityDirection, int range, list<Enemy*> enemies, Player *player){

    if(entityDirection == RIGHT){

        temp++;

        while(temp <= entityPos.x + range){

                int ch = mvinch(entityPos.y, temp); // Carattere da confrontare negli if per vedere se colpisco qualcuno

                if(ch == 892){

                    auto it = find_if(enemies.begin(), enemies.end(), [entityPos, temp](Enemy* enemy){
                        if(enemy->getPos().y == entityPos.y && (int)(enemy->getPos().x) == (int)(temp))
                            return true;
                        else
                            return false;
                    });

                    if(it != enemies.end()){

                        Enemy* enemy = *it;
                        return enemy; 

                    }

                }
                else if(ch == 320){

                    return player;

                }

            temp++;

        }

        return NULL;
            
    }
    else if(entityDirection == LEFT){

        temp--;

        while(temp >= entityPos.x - range){

            int ch = mvinch(entityPos.y, temp); // Carattere da confrontare negli if per vedere se colpisco qualcuno

            if(ch == 892){

                auto it = find_if(enemies.begin(), enemies.end(), [entityPos, temp](Enemy* enemy){
                    if(enemy->getPos().y == entityPos.y && (int)enemy->getPos().x == (int)temp)
                        return true;
                    else
                        return false;
                });

                if(it != enemies.end()){

                    Enemy* enemy = *it;
                    return enemy;

                }

            }
            else if(ch == 320){

                return player;

            }
            
            temp--;

        }
        
        return NULL;

    }

    return NULL;

}

bool Entity::attack(int range, list<Enemy*> enemies, Player *player, Game *game){

    srand(time(NULL));

    int hit = rand()%99 + 1;

    Point entityPos = this->getPos();
    direction entityDirection = this->getDirection();

    float temp = entityPos.x;

    // Uso la funzione groundAttackTarget che mi ritorna l'entità che sta venendo bersagliata dall'attacco di questa entità
    Entity *targetEntity = this->groundAttackTarget(temp, entityPos, entityDirection, range, enemies, player);

    if(targetEntity != NULL){

        if(this->getCurrentDelayCounter() >= this->getAttackDelay()){

            if(hit <= this->getHitChance()){

                targetEntity->isHit(1, entityDirection, game);    // dmg = 1 da sostituire in futuro con la getEntityAttackDamage()
                setCurrentDelayCounter(0);
                return true;

            }
            else{

                string msg = "Miss!";
                mvprintw(entityPos.y - 2, entityPos.x - 2, msg.c_str());
                return false;

            }

        }
        else
            return false;

    }
    else
        return false;    // Ritorno true anche se non becco nessuno solo per far andare l'animazione

    return false;

}

void Entity::entityPhysics(Game *game, bool ignoreGravity){

    Point selEntityPos = this->getPos();

    this->setPrevPos(this->getPos().y, this->getPos().x);

    if(!ignoreGravity){
        
        if(!game->getInvertedGrav()){
            if(mvinch(selEntityPos.y + 1, selEntityPos.x) == ' ')
                this->setIsFalling(true);
        }
        else{
            if(mvinch(selEntityPos.y - 1, selEntityPos.x) == ' ')
                this->setIsFalling(true);
        }
        if(this->getIsFalling())
            this->setYVel(this->getVel().y - game->getGravity());
            
    }

    /*
    
        Come threshold per far fermare il nemico uso la sua maxSpeed / 20.
        Il parametro isMoving serve al nemico per capire quando applicare l'attrito
        e quando no. L'attrito viene applicato solo quando il nemico non si sta attivamente
        spostando verso una posizione, viene così usato solamente per "fermarsi" una volta
        raggiunta la posizione desiderata.

        Così è più semplice creare nemici con più diversità tra le loro velocità
        dato che ora tutti i parametri che andavano ad influenzare il modo in cui
        un nemico si muoveva sono calcolati automaticamente.
    
    */

    float entityXVel = this->getVel().x;

    float friction = game->getFriction();

    if(entityXVel != 0){
        if(entityXVel > 0){
            
            if(entityXVel <= (this->getMaxSpeed() / 10)){
                this->setXVel(0);
                entityXVel = 0;
                friction = 0;
            }
            if(!this->getIsFalling())
                if(!this->getIsMoving())
                    this->setXVel(entityXVel - friction);
                else
                    this->setXVel(entityXVel);
        }
        else{
            
            if(entityXVel >= -(this->getMaxSpeed() / 10)){
                this->setXVel(0);
                entityXVel = 0;
                friction = 0;
            }               
            if(!this->getIsFalling())
                if(!this->getIsMoving())
                    this->setXVel(entityXVel + friction);
                else
                    this->setXVel(entityXVel);
        }
    }

    this->setYPos(this->getPos().y - this->getVel().y);
    this->setXPos(this->getPos().x + this->getVel().x);

    //  Controllo se il nemico è al di fuori dei limiti dello schermo per settare la flag per l'eliminazione
    if(selEntityPos.x > getmaxx(stdscr) || selEntityPos.x < 0 || selEntityPos.y > getmaxy(stdscr)){
        this->setEliminationFlag(true);
    }

}