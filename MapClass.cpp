#include "./Header Files/MapClass.hpp"

//Constructor
MapClass :: MapClass(string name){
    srand(time(NULL));
    setGameSlot(name);
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    xMax -= 20;
    setYMax(yMax);
    setXMax(xMax);
    createList(0, 0, yMax, xMax);
    //start_game();
}

MapClass :: MapClass(){}

//Getters & Setters

string MapClass :: getGameSlot(){return gameSlot;}
int MapClass :: getYMax(){return yMax;}
int MapClass :: getXMax(){return xMax;}
int MapClass :: getId(){return NSchermate -> id;}
Platform* MapClass :: getPList(){ return &NSchermate -> PList; }
pScreen MapClass :: getNSchermate(){ return this->NSchermate; }
ChunkClass* MapClass :: getCksPtr(){ return this->Cks; }
int MapClass :: getLastGenLevelId(){ return lastGenLevelId;}
WindowGenerator MapClass :: getWinLevel(){return NSchermate -> win;}

void MapClass :: setGameSlot(string name){gameSlot = name;}
void MapClass :: setYMax(int yMax){ this -> yMax = yMax;}
void MapClass :: setXMax(int xMax){ this -> xMax = xMax;}
void MapClass :: setLastGenLevelId(int last){ this -> lastGenLevelId = last;}

//Other Methods
void MapClass :: createList(int y, int x, int height, int width){
    NSchermate = new lvScreen;
    NSchermate -> win = WindowGenerator (y, x, height, width);
    NSchermate -> id = 1;
    setLastGenLevelId(NSchermate -> id); 
    NSchermate -> xPositionConfront = getXMax();
    NSchermate -> next = NULL;
    NSchermate -> prev = NULL;

    for(int i = 0; i < 6; i++){
        Cks[i+1] = ChunkClass(i+1, getYMax(), getXMax());
    }
    Platform plt = Platform(NSchermate -> id, Cks, yMax, xMax); //debug
    NSchermate -> PList = plt;
}

void MapClass :: addList(){
    if(NSchermate != NULL){
        pScreen copy = NSchermate;
        int id = copy -> id;
        while(copy -> next != NULL){
            copy = copy -> next;
            id = copy -> id;
        }
        
        copy -> next = new lvScreen;
        copy -> next -> prev = copy; 
        copy = copy -> next;
        copy -> win = WindowGenerator (0, 0, getYMax(), getXMax());
        if(id % 10 != 0)
            copy -> id = id + 1;
        else
            copy -> id = id + 2;

        setLastGenLevelId(copy -> id); 
        copy -> xPositionConfront = getXMax();
        copy -> next = NULL;
        NSchermate = copy;
        NSchermate = NSchermate -> prev;
    }
}

void MapClass :: show_win(WindowGenerator schema){
    char sp = ' ';
    if(NSchermate -> id != 1)
        //wborder(window, lb, rb, top, bottom, top-left, top-right, bottom-left, bottom-right); 
        wborder(schema.getW(), NSchermate -> bl, NSchermate -> bl, 0, 0, 0, 0, 0, 0);
    else
        wborder(schema.getW(), 0, NSchermate -> bl, 0, 0, 0, 0, 0, 0);
    
    wrefresh(schema.getW());
}

int MapClass :: checkBoundaries(float xPos){
    int pos = (int)xPos;

    if(pos < 0)
        return 0;
    else if(pos + 1 >= NSchermate -> xPositionConfront){
        return 1;
    }

    return -2;
}

int MapClass :: advanceMap(){
    if(NSchermate -> next == NULL){ 
        addList();
        int mId = NSchermate -> PList.getMapId();
        NSchermate = NSchermate -> next;
        if(NSchermate -> id % 10 != 0){
            if(mId < NSchermate -> id){
                Platform plt = Platform(NSchermate -> id, Cks, yMax, xMax); // win per debug
                NSchermate -> PList = plt;
                NSchermate -> PList.printPlatformsToMap(NSchermate -> win, NSchermate -> id);
            }    

    //else{
        //Qui per il livello negozio. Entra se NSchermate -> id % 10 == 0.
        //Io ho messo 10 perché non so ogni quanto vogliate renderlo accessibile.
        //Se è un valore diverso comunicatemelo. 
        //Shop shop = Shop();
        //}
    }
        NSchermate = NSchermate -> prev;
    }
    NSchermate = NSchermate -> next;
    show_win(NSchermate -> win);
    return 1;
}

int MapClass :: previousMap(){
    if(NSchermate -> id == 1)
        return 1;
    else if (NSchermate -> id % 10 != 0){
        NSchermate = NSchermate -> prev;
        show_win(NSchermate -> win);
    }
    else{
        //Qui per il livello negozio. Entra se NSchermate -> id % 10 == 0.
        //Io ho messo 10 perché non so ogni quanto vogliate renderlo accessibile.
        //Se è un valore diverso comunicatemelo. 
        //Shop shop = Shop();
    }
    return NSchermate -> xPositionConfront - 2;
}

void MapClass :: scoreWindow(){
    WindowGenerator score = WindowGenerator(0, getXMax(), getYMax(), 20);
    string titleScore = "Score & Power-Ups";
    mvwprintw(score.getW(), 1, score.getWidth()/2 - (titleScore.length()/2 + titleScore.length()%2), "%s", titleScore.c_str());
    score.show_window();
}