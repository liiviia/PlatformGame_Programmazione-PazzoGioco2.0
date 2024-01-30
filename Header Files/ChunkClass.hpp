#pragma once
#include "MainMenu.hpp"

class ChunkClass{
    private:
        int y;
        int x;
        int height;
        int width;
        int chunkId;
    
    public:
        //Constructor
        ChunkClass (int, int, int);
        ChunkClass ();

        //Setters
        void setY(int, int);
        void setX(int, int);
        void setHeight(int, int);
        void setWidth(int, int);
        void setChunkId(int);

        //Getters
        int getY();
        int getX();
        int getHeight();
        int getWidth();
        int getChunkId();

        //Methods
        int genPlatNum(); // genera numero di piattaforme in un chunk
};
