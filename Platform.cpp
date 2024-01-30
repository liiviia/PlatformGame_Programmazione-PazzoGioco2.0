#include"./Header Files/Platform.hpp"

Platform::Platform(int map_id, ChunkClass ck[], int yMax, int xMax){
    createPlatformList(map_id, ck[4], yMax);
    for(int i = 1; i < 7; i++){
        int rn = ck[i].genPlatNum();
        for(int j = 0; j < rn; j++){ 
            addToPlatformList(map_id, ck[i]);
        }
    }
    addEndingPlatform(map_id, ck[6], yMax, xMax);
}

// Default constructor
Platform :: Platform(){}

// Getters  

int Platform :: getId(){return PlatList -> id;} //returns the obstacle id

//returns the id of the map where the obstacle is printed
int Platform :: getMapId(){return PlatList -> map_id;}

//returns the id of the portion of the map (chunk) where the obstacle is generated
int Platform :: getChunkId(){return PlatList -> chunk_id;}

//returns the coordinate of the height of where the obstacle is printed
float Platform :: getY(){return PlatList -> y;}

//returns the coordinate of the width of where the obstacle is printed
float Platform :: getX(){return PlatList -> x;}

//returns the length of the platform
int Platform :: getLength(){return PlatList -> length;}
char Platform :: getSymbol(){return PlatList -> drawSymbol;}

/* 
This method returns a Point object with
the coordinates of the starting point of the 
current platform.
*/
Point Platform:: getStart(){ 
    Point start;
    start.y = PlatList -> y;
    start.x = PlatList -> x;
    return start;
};

/* 
This method returns a Point object with
the coordinates of the ending point of the 
current platform.
*/
Point Platform :: getEnd(){
    Point end;
    end.y = PlatList-> y;
    end.x = PlatList-> x + PlatList->length;
    return end;
};

bool Platform::getIsGround(){ return PlatList -> isGround; }
int Platform :: getPairNum(){ return PlatList -> pairNum; }

bool Platform::getStandingPlatform(Point coord){
    while(PlatList -> next != NULL){
        if(PlatList -> isGround && PlatList -> y == coord.y - 1 && coord.x >= PlatList -> x && coord.x <= PlatList -> x + PlatList -> length){
            return true;
        }
        PlatList = PlatList -> next;
    }
    return false;
}

obPointer Platform :: getCurPlatform(Point coord){
    while(PlatList -> next != NULL){
        if(PlatList -> y == coord.y - 1 && coord.x >= PlatList -> x && coord.x <= PlatList -> x + PlatList -> length){
            return PlatList;
        }
        PlatList = PlatList -> next;
    }
    return NULL;
}

// Setters

void Platform :: setId(int id){PlatList -> id = id;}
void Platform :: setMapId(int map_id){PlatList -> map_id = map_id;}
void Platform :: setChunkId(int chunk_id){PlatList -> chunk_id = chunk_id;}
void Platform :: setY(ChunkClass ck){
    PlatList -> y = ck.getY() + ck.getHeight() - (rand() % (ck.getHeight()*2)/3 + 4*ck.getChunkId()/4);
}
void Platform :: setYTerrain(float y){
    PlatList -> y = y;
}
void Platform :: setX(ChunkClass ck){
    PlatList -> x = rand() % (ck.getWidth()/2 - 3) + ck.getX();
}
void Platform :: setXTerrain(float x){
    PlatList -> x = x;
}
void Platform :: setLength(ChunkClass ck){
    PlatList -> length = rand() % (ck.getWidth()/2 - 3) + 15;
}

void Platform :: setPairNum(int color){
    PlatList -> pairNum = color;
}

void Platform::setIsGround(bool isGround){ 
    PlatList -> isGround = isGround; 
}
void Platform :: setObPointer(obPointer list){
    PlatList = list;
}
// Other Methods
void Platform :: createPlatformList(int map_id, ChunkClass ck, int yMax){
    PlatList = new obstacle;
    setId(1);
    setMapId(map_id);
    setChunkId(ck.getChunkId());    
    setYTerrain((float)yMax - 2);
    setXTerrain(0.0);
    setLength(ck);
    setPairNum(15);
    setIsGround(true);
    
    PlatList -> next = NULL;
    PlatList -> prev = NULL;
}

void Platform :: addToPlatformList(int map_id, ChunkClass ck){
    PlatList -> next = new obstacle;
    PlatList -> next -> prev = PlatList;
    int id = PlatList -> id;
    PlatList = PlatList -> next;
    PlatList -> next = NULL;
        
    setId(id + 1);
    setMapId(map_id);
    setChunkId(ck.getChunkId());
    setLength(ck);
    setPairNum(4);
    setY(ck);
    setX(ck);
    setIsGround(false);
}

void Platform :: addEndingPlatform(int map_id, ChunkClass ck, int yMax, int xMax){
    PlatList -> next = new obstacle;
    PlatList -> next -> prev = PlatList;
    int id = PlatList -> id;
    PlatList = PlatList -> next;
    PlatList -> next = NULL;
    setId(id + 1);
    setMapId(map_id);
    setChunkId(ck.getChunkId());
    setLength(ck);
    setPairNum(15);
    setYTerrain((float)yMax - 2);
    setXTerrain((float)(xMax - getLength()));
    setIsGround(true);
}

void Platform :: rewindPlatformList(){
    while(PlatList -> prev != NULL)
        PlatList = PlatList -> prev;
}
void Platform :: advancePlatformList(){ 
    PlatList = PlatList -> next;
}
bool Platform :: checkNext(){
    if(PlatList -> next != NULL)
        return true;
    return false;
}

bool Platform :: checkExistPlatform(){
    if(PlatList != NULL)
        return true;
    return false;
}

// This method prints a single platform
void Platform :: printPlatform(WindowGenerator w){
    wattron(w.getW(), COLOR_PAIR(getPairNum()));
    for(int i = 0; i < getLength(); i++){
        mvwprintw(w.getW(), getY(), getX() + i, "%c", PlatList -> drawSymbol);
    }
    wattroff(w.getW(), COLOR_PAIR(getPairNum()));
}

/* 
This method prints every platform in PlatList with the same id as the
current playable map. It calls printPlatform to print every single platform.
*/
void Platform :: printPlatformsToMap(WindowGenerator win, int map_id){
    int i = 0;
    while(PlatList -> prev != NULL && PlatList -> map_id == map_id){
        printPlatform(win);
        PlatList = PlatList -> prev;
        i++;
        
    }
    if(PlatList != NULL && PlatList -> prev == NULL)
        printPlatform(win);
    PlatList = PlatList -> next;
}