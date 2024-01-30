#include"./Header Files/Game.h"
#include"./Header Files/Platform.hpp"
#include"./Header Files/util.h"

#include<cmath>
#include<ctime>
#include<algorithm>
#include<iostream>

Game::Game(gameState g, int yMax, int xMax){

    setGameState(g);
    setGlobalEntityCount(0);
    setGlobalAnimationCount(0);

    setYMax(yMax);
    setXMax(xMax - 20); // 20 colonne per le statistiche

}

void Game::moveEntities(Platform* platforms){

    // Salviamo la posizione del frame precedente

    // Prima di tutto è necessario calcolare la posizione aggiornata delle entità all'inizio di ogni frame, così che il valore aggiornato sia subito disponibile per l'utilizzo nelle altre funzioni

    player.entityPhysics(this, false);
    Enemy::findPath(enemies, platforms, player, this);
    

    // Aggiorno prima i proiettili dei nemici, così posso avere 
    // sia posizione vecchia che posizione nuova pronte per l'utilizzo dentro solveCollisions

    if (!bullets.empty())
        Bullet::updateBullets(this); 

    for(Enemy *enemy : enemies){

        Enemy::enemyType type = enemy->getEnemyType();

        if(type == Enemy::enemyType::FLYING || type == Enemy::enemyType::FLYINGRANGED)
            enemy->entityPhysics(this, true);
        else
            enemy->entityPhysics(this, false);

        // Aggiorno i contatori per il delay d'attacco
        updateDelayCounters();

        // Controllo se il nemico è in range per attaccare

        switch(enemy->getEnemyType()){

            case Enemy::enemyType::MELEE:

                if(enemy->isInRange(&player) && (enemy->getPos().y == player.getPos().y)){
                    
                    if(enemy->attack(enemy->getAttackRange(), enemies, &player, this))
                        Animation::addAnimation(this, Animation::GROUND_ATTACK, enemy);

                }

            break;

            case Enemy::enemyType::RANGED:
                
                if(enemy->isInShootingRange(&player) && (enemy->getPos().y == player.getPos().y)){
                    
                    enemy->shoot(getGlobalEntityCount(), getBulletList(), enemy->getDirection());
                    incrementGlobalEntityCount(); 
                    
                }

            break;

            case Enemy::enemyType::FLYING:

                if(enemy->isInRange(&player) && ((int)enemy->getPos().y == (int)enemy->getOriginalYPos())){
                    if(enemy->getCurrentDelayCounter() >= enemy->getAttackDelay()){
                        enemy->setYPos(enemy->getPos().y + 1.1);
                        enemy->setYVel(-1);
                        enemy->setCurrentDelayCounter(0);
                    }
                }

            break;

            case Enemy::enemyType::FLYINGRANGED:

                if(enemy->isInShootingRange(&player) && (abs(enemy->getPos().x - player.getPos().x) <= 1) && enemy->getVel().y == 0){
                    
                    enemy->shoot(getGlobalEntityCount(), getBulletList(), DOWN);
                    incrementGlobalEntityCount(); 
                    
                }
            
            break;

        }
    

    }
    

    //  Sposto le monete e controllo se sono nella pickupRange del player
    for(list<Coin*>::iterator it = coins.begin(); it != coins.end(); ++it){

        Coin *selCoin = (*it);
        Point selCoinPos = selCoin->getPos();
        Point selCoinVel = selCoin->getVel();

        selCoin->setPrevPos(selCoinPos);

        if(selCoinVel.x != 0 || selCoinVel.y != 0){

            selCoin->entityPhysics(this, false);

        }


        Point playerPos;
        int radius = player.getPickupRadius();
        selCoinPos = (*it)->getPos();   //  Aggiorno la posizione della moneta dopo averla spostata
        playerPos = player.getPos();

        if(abs(selCoinPos.y - playerPos.y) <= radius && abs(selCoinPos.x - playerPos.x) <= radius){

            player.incrementBudget();

            (*it)->setEliminationFlag(true);

        }
        
    }

    solveCollisions(platforms, enemies);

}

void Game::checkCollisions(Platform* platforms, Entity *entity, bool &updIsFalling){
    platforms->rewindPlatformList();
    while(platforms->checkNext() != false){
        if(trajectory(*entity, platforms)){

            int approxEntPrevPosY, approxEntPosY, approxPlatPosY;
            approxEntPosY = approxFloat(entity->getPos().y);
            approxEntPrevPosY = approxFloat(entity->getPrevPos().y);
            approxPlatPosY = approxFloat(platforms->getEnd().y);
            
            // If player is above the platform
            if(approxEntPrevPosY <= approxPlatPosY && approxEntPosY >= approxPlatPosY){
                entity->setXPos((entity->getPrevPos().x + entity->getPos().x)/2);
                entity->setYPos(platforms->getEnd().y - 1);
                entity->setYVel(0);
                entity->setXVel(entity->getVel().x);

                if(!invertedGrav)
                    updIsFalling = false;

            }
        }
        platforms -> advancePlatformList(); 
    }
    //Ho dovuto ripetere l'if fuori dal while per controllare le collisioni con
    //l'ultima piattaforma. Ho provato a modificare il while in modo che iterasse
    //controllando l'esistenza della piattaforma attule e non della sua successiva
    //e avanzando di piattaforma con advancePlatformList() solo se esisteva una 
    //piattaforma successiva, ma mi dava dei problemi quindi ho optato per questo.
    //Andrea 29/01.
    if(trajectory(*entity, platforms)){

        int approxEntPrevPosY, approxEntPosY, approxPlatPosY;
        approxEntPosY = approxFloat(entity->getPos().y);
        approxEntPrevPosY = approxFloat(entity->getPrevPos().y);
        approxPlatPosY = approxFloat(platforms->getEnd().y);
        
        // If player is above the platform
        if(approxEntPrevPosY <= approxPlatPosY && approxEntPosY >= approxPlatPosY){
            entity->setXPos((entity->getPrevPos().x + entity->getPos().x)/2);
            entity->setYPos(platforms->getEnd().y - 1);
            entity->setYVel(0);
            entity->setXVel(entity->getVel().x);

            if(!invertedGrav)
                updIsFalling = false;

        }
    }
}


void Game::solveCollisions(Platform* platforms, list<Enemy*> enemies){

    // Controllo le collisioni tra entity e le piattaforme
    // Invece che chiamare solveCollisions per ogni nemico mi conviene chiamarla una sola volta dove controllo le collisioni del player e di ogni nemico internamente
    // non tra un entità generica e tutte le piattaforme
    
    bool updIsFalling = player.getIsFalling();
    
    checkCollisions(platforms, getPlayer(), updIsFalling);

    player.setIsFalling(updIsFalling);

    // Collisioni tra nemici

    for(Enemy *selEnemy : enemies){

        updIsFalling = selEnemy->getIsFalling();

        checkCollisions(platforms, selEnemy, updIsFalling);

        obPointer selEnemyPlat = platforms -> getCurPlatform(selEnemy -> getPos());
        Point selEnemyPos = selEnemy->getPos();
        int selEnemyHtbxRadius = selEnemy->getHitboxRadius();

        for(Enemy *enemy : enemies){

            obPointer enemyPlat = platforms -> getCurPlatform(enemy -> getPos());

            if(selEnemyPlat == enemyPlat){

                Point enemyPos = enemy->getPos();
                int enemyHtbxRadius = enemy->getHitboxRadius();

                float minDistance = ((float)enemyHtbxRadius / (float)2) + ((float)selEnemyHtbxRadius / (float)2);

                if((abs(enemyPos.x - selEnemyPos.x) < minDistance)
                && (abs(enemyPos.y - selEnemyPos.y) < minDistance)){

                    if(enemyPos.x > selEnemyPos.x){ 

                       enemy->setXPos(enemy->getPos().x + 0.4);
                       selEnemy->setXPos(selEnemy->getPos().x - 0.4);

                   }
                   else{

                       enemy->setXPos(enemy->getPos().x - 0.4);
                       selEnemy->setXPos(selEnemy->getPos().x + 0.4);

                   }

                }

            }
            
        }

        Point playerPos = player.getPos();
        int playerHtbxRadius = player.getHitboxRadius();

        float minDistance = ((float)playerHtbxRadius / (float)2) + ((float)selEnemyHtbxRadius / (float)2);

        if((abs(playerPos.x - selEnemyPos.x) < minDistance)
        && (abs(playerPos.y - selEnemyPos.y) < minDistance)){
            player.isHit(1, selEnemy->getDirection(), this);
        }

        selEnemy->setIsFalling(updIsFalling);

    }

    for(Coin *coin : coins){

        if(coin->getVel().x != 0 || coin->getVel().y != 0){
            updIsFalling = coin->getIsFalling();

            checkCollisions(platforms, coin, updIsFalling);

            coin->setIsFalling(updIsFalling);
        }

    }

    // Collisioni tra proiettili e entità

    for(Bullet *bullet : bullets){

        //  temp punta all'entità colpita dal proiettile
        Entity* temp = bullet->checkBulletCollisions(enemies, &player);

        if(temp != NULL){

            temp->isHit(1, bullet->getDirection(), this);
            bullet->setEliminationFlag(true);

        }

    }
    
}

void Game::displayEntities(MapClass level){
    // Stampa le piattaforme
    Platform* printPlatform = level.getPList();

    //non c'è bisogno di riavvolgere la lista, perché printPlatformToMap stampa al contrario
    printPlatform->printPlatformsToMap(level.getWinLevel(), level.getId());
    level.scoreWindow();  //al momento stampare per forza prima scoreWindow della WinLevel perché
                          //altrimenti scoreWindow viene stampata sopra e cancella WinLevel.
    level.show_win(level.getWinLevel());

    //Bisogna mettere qui l'erase per stampare anche il player. Ci sono ancora problemi coi nemici
    werase(level.getWinLevel().getW());

    // Stampa il player
    //wattron(level.getWinLevel().getW(), COLOR_PAIR(player.getPairNum()));
    wattron(level.getWinLevel().getW(), COLOR_PAIR(6));
    mvwprintw(level.getWinLevel().getW(), player.getPos().y, player.getPos().x, "%s", player.getSymbol().c_str());
    //wattroff(level.getWinLevel().getW(),COLOR_PAIR(player.getPairNum()));
    wattroff(level.getWinLevel().getW(),COLOR_PAIR(6));

    

    /*
        Per ciclarmi tutte le entità (che siano nemici, proiettili, ecc.) e eliminarli se
        sono flaggati devo per forza usare l'iteratore delle liste, dato che il metodo
        erase() della classe lista di c++ accetta come parametro solamente iteratori.

        Ho scelto di fare il controllo per l'eliminazione nella stessa funzione in cui
        stampo le entità per una questione di efficienza, per non stare a fare un'altra
        funzione che si cicla tutte le entità solo per eliminarle quando posso benissimo
        farlo qui.
    */

    // Stampa le monete

    for(list<Coin*>::iterator it = coins.begin(); it != coins.end();){

        if(!(*it)->getEliminationFlag()){

            wattron(level.getWinLevel().getW(), COLOR_PAIR((*it)->getPairNum()));
            mvwprintw(level.getWinLevel().getW(), (*it)->getPos().y, (*it)->getPos().x, (*it)->getSymbol().c_str());
            wattroff(level.getWinLevel().getW(), COLOR_PAIR((*it)->getPairNum()));
            ++it;

        }
        else{
            
            it = coins.erase(it);

        }
    }
    
    //Stampa i proiettili
    if(!bullets.empty()){
        for(list<Bullet*>::iterator it = bullets.begin(); it != bullets.end();){

            if(!(*it)->getEliminationFlag()){

                wattron(level.getWinLevel().getW(), COLOR_PAIR((*it)->getPairNum())); 
                mvwprintw(level.getWinLevel().getW(),(*it)->getPos().y, (*it)->getPos().x, (*it)->getSymbol().c_str()); 
                wattroff(level.getWinLevel().getW(), COLOR_PAIR((*it)->getPairNum()));
                ++it;

            }
            else{

                //  NB: usando erase, per far si che l'iteratore punti alla posizione della lista successiva
                //  è necessario fare il riassegnamento. erase() ritorna il puntatore alla posizione successiva.
                it = bullets.erase(it);

            }

        }
    } 
    
    // Stampa i nemici 
    if(!enemies.empty()){    
        for(list<Enemy*>::iterator it = enemies.begin(); it != enemies.end();){

            if(!(*it)->getEliminationFlag()){

                wattron(level.getWinLevel().getW(), COLOR_PAIR((*it)->getPairNum()));
                mvwprintw(level.getWinLevel().getW(), (*it)->getPos().y, (*it)->getPos().x, (*it)->getSymbol().c_str());
                wattroff(level.getWinLevel().getW(), COLOR_PAIR((*it)->getPairNum()));
                ++it;

            }
            else{

                it = enemies.erase(it);

            }

        }
    }

    if(!animations.empty()){
      
        for(list<Animation*>::iterator it = animations.begin(); it != animations.end(); ++it){

            if(!(*it)->isFramesEmpty()){

                Frame curFrame = (*it)->getCurFrame();

                mvwprintw(level.getWinLevel().getW(), curFrame.framePos.y, curFrame.framePos.x, curFrame.frameChar.c_str());
                (*it)->nextFrame();

                
                if((*it)->getCurFrameIndx() >= (*it)->getFrameCount()){  // Se il numero di frame dell'animazione è superato, la elimino dalla lista
                    (*it)->setEliminationFlag(true);
                }
            }
        }

        bool s = true;

        while(s){

            s = false;
                    
            auto itToRemove = std::find_if(animations.begin(), animations.end(), [](Animation* animation){
                return animation->getEliminationFlag() == true;
            });

            if(itToRemove != animations.end()){
                s = true;
                animations.erase(itToRemove);
                setGlobalAnimationCount(getGlobalAnimationCount() - 1);
                itToRemove++;
            }
            
        }

    }
}

void Game::debugDisplay(MapClass level){

    string sYPos = "yPos: " + to_string(player.getPos().y);
    mvwprintw(level.getWinLevel().getW(), 1, 1, sYPos.c_str());
    
    string sXPos = "xPos: " + to_string(player.getPos().x);
    mvwprintw(level.getWinLevel().getW(), 2, 1, sXPos.c_str());

    string lastYPos = "lastYPos: " + to_string(player.getPrevPos().y);
    mvwprintw(level.getWinLevel().getW(), 4, 1, lastYPos.c_str());

    string lastXPos = "lastXPos: " + to_string(player.getPrevPos().x);
    mvwprintw(level.getWinLevel().getW(), 5, 1, lastXPos.c_str());

    string sYVel = "yVel: " + to_string(player.getVel().y);
    mvwprintw(level.getWinLevel().getW(), 7, 1, sYVel.c_str());
    
    string sXVel = "xVel : " + to_string(player.getVel().x);
    mvwprintw(level.getWinLevel().getW(),8, 1, sXVel.c_str());

    string sIsFalling = "isFalling : " + to_string(player.getIsFalling());
    mvwprintw(level.getWinLevel().getW(), 10, 1, sIsFalling.c_str());

    string budget = "Budget: " + to_string(player.getBudget());
    mvwprintw(level.getWinLevel().getW(), 11, 1, budget.c_str());

    string health = "Vite: " + to_string(player.getCurHealth()); 
    mvwprintw(level.getWinLevel().getW(), 12, 1, health.c_str());

    // for(Enemy* enemy : enemies){
    //     string eYPos = "eYPos: " + to_string(enemy->getPos().y);
    //     string eXPos = "eXPos: " + to_string(enemy->getPos().x);
    //     string xVel = "xVel: " + to_string(enemy->getVel().x);
    //     string delay = "delay: " + to_string(enemy->getCurrentDelayCounter());
    //     string range = "isInRange: " + to_string(enemy->isInRange(&player));
    //     mvprintw(11, 1, eYPos.c_str());
    //     mvprintw(12, 1, eXPos.c_str());
    //     mvprintw(13, 1, xVel.c_str());
    //     mvprintw(14, 1, delay.c_str());
    //     mvprintw(15, 1, range.c_str());
    // }
    
    // for(Bullet* bullet : bullets){
    //     string bYPos = "bYPos: " + to_string(bullet->getPos().y);
    //     string bXPos = "bXPos: " + to_string(bullet->getPos().x);
    //     mvprintw(14, 1, bYPos.c_str());
    //     mvprintw(15, 1, bXPos.c_str());
    // }


}

void Game::spawnEntities(int nCoins, int nEnemies, Platform* platforms){

    set<float> recordedPos;
    Coin::spawnCoins(this, nCoins, recordedPos, platforms);

    Enemy::spawnEnemies(this, nEnemies, recordedPos, Enemy::enemyType::WALKER, platforms);
    Enemy::spawnEnemies(this, nEnemies, recordedPos, Enemy::enemyType::MELEE, platforms);
    Enemy::spawnEnemies(this, nEnemies, recordedPos, Enemy::enemyType::RANGED, platforms);
    Enemy::spawnEnemies(this, nEnemies, recordedPos, Enemy::enemyType::FLYING, platforms);
    Enemy::spawnEnemies(this, nEnemies, recordedPos, Enemy::enemyType::FLYINGRANGED, platforms);

}

// Funzione unica che incrementa il delayCounter (contatore per il delay dell'attacco) per ogni entità
void Game::updateDelayCounters(){

    for(Enemy *enemy : enemies){

        enemy->incrementDelayCounter();

    }

}

void Game::incrementGlobalEntityCount(){ this->globalEntityCount += 1; }
void Game::increaseGlobalEntityCount(int n){ this->globalEntityCount += n; }

// Getters

float            Game::getGravity(){ return this->gravity; }
float            Game::getFriction(){ return this->friction; }

Game::gameState  Game::getGameState(){ return this->state; }
bool             Game::getInvertedGrav(){ return this->invertedGrav; }
int              Game::getGlobalEntityCount(){ return this->globalEntityCount; }
Player           *Game::getPlayer(){ return &this->player; }
list<Enemy*>     *Game::getEnemyList(){ return &this->enemies; }
list<Coin*>      *Game::getCoinList(){ return &this->coins; }
list<Animation*> *Game::getAnimationList(){ return &this->animations; }
list<Bullet*>    *Game::getBulletList(){return &this->bullets; }
int              Game::getGlobalAnimationCount(){ return this->globalAnimationCount; }
int              Game::getYMax(){ return this->yMax; }
int              Game::getXMax(){ return this->xMax; }

// Setters
void Game::setGameState(gameState g){ this->state = g; }
void Game::setInvertedGrav(bool b){ this->invertedGrav = b; }
void Game::setGlobalEntityCount(int count){ this->globalEntityCount = count; }
void Game::setPlayer(float yPos, float xPos, float yVel, float xVel, string name, string symbol, int maxHealth){

    this->player = Player(getGlobalEntityCount(), yPos, xPos, yVel, xVel, name, symbol, maxHealth);

    incrementGlobalEntityCount();

}
void Game::setGlobalAnimationCount(int index){ this->globalAnimationCount = index; }
void Game::setYMax(int yMax){ this->yMax = yMax; }
void Game::setXMax(int xMax){ this->xMax = xMax; }