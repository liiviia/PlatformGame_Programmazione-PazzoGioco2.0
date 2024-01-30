#pragma once
#include "MainMenu.hpp"


struct gameslot
{
    string game;
    string status;
};


class ContinueMenuClass{

    static const int nchoices = 3;
    private:
        gameslot Games[nchoices];
    
    public:
        //Constructors
        ContinueMenuClass();
        
        //Setters
        void setGame(int);
        void setStatus(string, int);

        //Getters 
        string getGame(int);
        string getStatus(int);
        
        void readFromFile();

        void changeSlot(WINDOW*, WINDOW*, WINDOW*, int, int); //this function changes the bgcolour of the selected slot

        void startContinue(string&);

};