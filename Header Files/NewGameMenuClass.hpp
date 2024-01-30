#pragma once
#include "MainMenu.hpp"
#include "Player.h"


struct newgameslot
{
    string game;
    string status;
};


class NewGameMenuClass{

    static const int nchoices = 3;
    private:
        newgameslot NewGames[nchoices];
    
    public:
        //Constructors
        NewGameMenuClass();
        
        //Setters
        void setGame(int);
        void setStatus(string, int);

        //Getters 
        string getGame(int);
        string getStatus(int);
        
        void readFromFile();

        void changeSlot(WINDOW*, WINDOW*, WINDOW*, int, int); //this function changes the bgcolour of the selected slot

        void startNewGame(string&);

        void overrideGame(int, int, int, int, int, WindowGenerator, int, string&);

        void chooseName(int, int, int, int, int, string& name);

};