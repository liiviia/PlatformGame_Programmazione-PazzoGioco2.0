#pragma once
#include "MainMenu.hpp"
#include "ChunkClass.hpp"
#include "Platform.hpp"
#include <time.h>

struct lvScreen{
    int id;
    int bl = (int)'|';
    int xPositionConfront;
    WindowGenerator win;
    Platform PList; //every map will have its list of platforms
    lvScreen * next;
    lvScreen * prev;
    
};

typedef lvScreen * pScreen;

class MapClass: public WindowGenerator, ChunkClass{
    private:
        string gameSlot;
        int yMax;
        int xMax;
        ChunkClass Cks [7];
        pScreen NSchermate;
        int lastGenLevelId; //Saves the id of the last generated level

    public:
        //Constructor
        MapClass(string);
        
        // Default constructor
        MapClass();

        //Getters & Setters
        string getGameSlot();
        int getYMax();
        int getXMax();
        int getId();
        Platform* getPList();
        pScreen getNSchermate();
        ChunkClass* getCksPtr();
        int getLastGenLevelId();
        WindowGenerator getWinLevel();

        void setYMax(int);
        void setXMax(int);
        void setGameSlot(string);
        void setLastGenLevelId(int);

        //Other Methods
        void createList(int, int, int, int);
        
        void addList();

        void show_win(WindowGenerator);
        
        int advanceMap();
        int previousMap();

        void scoreWindow();

        int checkBoundaries(float);


};