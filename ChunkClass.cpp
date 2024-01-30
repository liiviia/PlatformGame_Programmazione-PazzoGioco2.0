#include "./Header Files/ChunkClass.hpp"

//Constructor
ChunkClass :: ChunkClass (int i, int yMax, int xMax) {
    setY(i, yMax);
    setX(i, xMax);
    setHeight(i, yMax);
    setWidth(i, xMax);
    setChunkId(i);
}
ChunkClass :: ChunkClass(){}

//Setters 
void ChunkClass :: setY(int i, int yMax){
    if(i <= 3)
        y = 1;
    else
        y = yMax/2 + 1;
}
void ChunkClass :: setX(int i, int xMax){x = (xMax/3)*((i-1)%3)+1;}
void ChunkClass :: setHeight(int i, int yMax){
    if(i <= 3)
        height = yMax/2 - 1;
    else
        height = yMax/2;
}
void ChunkClass :: setWidth(int i, int xMax){width = xMax/3;}
void ChunkClass :: setChunkId(int i){chunkId = i;}

//Getters
int ChunkClass :: getY(){return y;}
int ChunkClass :: getX(){return x;}
int ChunkClass :: getHeight(){return height;}
int ChunkClass :: getWidth(){return width;}
int ChunkClass :: getChunkId(){return chunkId;}

int ChunkClass :: genPlatNum(){
    if(chunkId <= 5) return rand()%3 + 1;
    return rand()%3 + 2;
}