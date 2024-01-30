#pragma once
#include "ChunkClass.hpp"
#include "util.h"

class Platform{
    private:
        obPointer PlatList;
    public:
        //Constructors
        Platform(int, ChunkClass[], int, int);
        Platform();
        //Setters 
        void setId(int); 
        void setMapId(int);
        void setChunkId(int);
        void setY(ChunkClass);
        void setYTerrain(float);
        void setX(ChunkClass);
        void setXTerrain(float);
        void setLength(ChunkClass);
        void setIsGround(bool);
        void setPairNum(int);
        void setObPointer(obPointer);

        //Getters
        int getId();
        int getMapId();
        int getChunkId();
        float getY();
        float getX();
        int getLength();
        char getSymbol();
        Point getStart();
        Point getEnd();
        bool getIsGround();
        int getPairNum();
        bool getStandingPlatform(Point);
        obPointer getCurPlatform(Point);

        //Other Methods
        void createPlatformList(int, ChunkClass, int);
        void addToPlatformList(int, ChunkClass);
        void addEndingPlatform(int, ChunkClass, int, int);

        void rewindPlatformList();
        void advancePlatformList();
        bool checkNext();
        bool checkExistPlatform();
        void printPlatform(WindowGenerator);
        void printPlatformsToMap(WindowGenerator, int);
};