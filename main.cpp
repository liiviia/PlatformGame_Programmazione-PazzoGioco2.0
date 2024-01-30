#include<iostream>
#include<curses.h>
#include<list>
#include"./Header Files/Game.h"
#include"./Header Files/Entity.h"
#include"./Header Files/Player.h"
#include"./Header Files/Enemy.h"
#include"./Header Files/MapClass.hpp"
#include"./Header Files/Platform.hpp"
#include"./Header Files/Coin.h"
#include"./Header Files/util.h"
using namespace std;

int main(){

    // ncurses initialization
    
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    use_default_colors();
    if(!has_colors()){ perror("Terminal does not support color."); };
    
    init_pair(6, COLOR_RED, COLOR_RED); // Player
    init_pair(7, COLOR_YELLOW, COLOR_BLACK); // Coins
    init_pair(3, COLOR_BLUE, COLOR_BLUE); // Enemies
    init_pair(4, COLOR_WHITE, COLOR_WHITE); // Platforms
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA); //Starting Platform

    //FileManager files = FileManager();  //Crea i file per i salvataggi

    // Crea oggetto Game

    Game game(Game::gameState::MENU, getmaxy(stdscr), getmaxx(stdscr));
    
    //Avvia il menù principale
    MainMenu menu = MainMenu();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    yMax -= 3;
    game.setPlayer(yMax, xMax - 25, 0, 0, "Player", "@", 5);

    // Creo un oggetto Player locale e linko quello dell'oggetto Game

    Player *player = game.getPlayer();
    
    // Stessa cosa per le liste di nemici, monete e piattaforme
    MapClass levels = MapClass(menu.getGameName());
    levels.setGameSlot(menu.getGameName());
    list<Enemy*> *enemies = game.getEnemyList();
    list<Coin*> *coins = game.getCoinList();
    Platform* platforms = levels.getPList();
    
    levels.show_win(levels.getWinLevel());
    levels.scoreWindow();

    // Genera le monete e i nemici
    game.spawnEntities(4, 1, platforms);  ///ERRORE DI Segmentation fault
    game.setGameState(Game::gameState::RUNNING);
    char ch;
    while(game.getGameState() == Game::gameState::RUNNING){
        
        game.debugDisplay(levels);
        ch = getch();
        flushinp();

        switch(ch){

            case (int)'q': case (int)'Q':
                game.setGameState(Game::gameState::QUIT);
            break;
 
            case (int)' ':
                if(player->getVel().y == 0){ 
 
                    if(!game.getInvertedGrav())
                        player->setYVel(player->getVel().y + (player->getJumpHeight() * game.getGravity()));
                    else
                        player->setYVel(player->getVel().y - (player->getJumpHeight() * game.getGravity()));

                    player->setIsFalling(true);
 
                }
            break;

            case (int)'w': case (int)'W':
                player->shoot(game.getGlobalEntityCount(), game.getBulletList(), UP);
            break;
 
            case (int)'a': case (int)'A':
                if(player->getVel().x > -player->getMaxSpeed()) player->setXVel(player->getVel().x - player->getMovSpeed()); else player->setXVel(-player->getMaxSpeed());
                player->setDirection(LEFT);
                player->setIsMoving(true);
            break;
 
            case (int)'d': case (int)'D':
                if(player->getVel().x < player->getMaxSpeed()) player->setXVel(player->getVel().x + player->getMovSpeed()); else player->setXVel(player->getMaxSpeed());
                player->setDirection(RIGHT);
                player->setIsMoving(true);
            break;
            
            case (int)'s': case (int)'S':
                if(!player->getIsFalling()){
                    bool fall = platforms -> getStandingPlatform(player->getPos());
                    if(!fall){
                        player->setIsFalling(true);
                        player->setYPos(player->getPos().y + 1);
                        player->setYVel(player->getVel().y - 1);
                    }
                }
            break;
 
            case (int)'.':
                player->shoot(game.getGlobalEntityCount(), game.getBulletList(), player->getDirection());
            break;

            case (int)',':
                if(player->attack(player->getAttackRange(), *game.getEnemyList(), player, &game))
                    Animation::addAnimation(&game, Animation::GROUND_ATTACK, player);
            break;
 
            default:
                player->setIsMoving(false);
            break;
 
        }
        
        game.displayEntities(levels);

        game.moveEntities(platforms);
        
        napms(35);

    }

    endwin();

}
