#include "./Header Files/ContinueMenu.hpp"

//Constructor
ContinueMenuClass :: ContinueMenuClass(){
    readFromFile();
}

//Setters
void ContinueMenuClass :: setGame(int i){
    Games[i].game = "Game" + to_string(i+1);
}
void ContinueMenuClass :: setStatus(string value, int i){
    Games[i].status = value;
}

//Getters
string ContinueMenuClass :: getGame(int i){
    return Games[i].game;
}
string ContinueMenuClass :: getStatus(int i){
    return Games[i].status;
}

//Other Function
void ContinueMenuClass :: readFromFile(){
    ifstream info;
        info.open("informations.txt");
        int i = 0;
        string f;
        while(!info.eof()){
            getline(info, f);
            setStatus(f, i);
            setGame(i);
            i++;
        }
    info.close();
}

void ContinueMenuClass :: changeSlot(WINDOW* slot1, WINDOW* slot2, WINDOW* slot3, int highlight, int i){
    box(slot1, 0, 0);
    box(slot2, 0, 0);
    box(slot3, 0, 0);
    wbkgd(slot1, COLOR_PAIR(2 - i%2 - i/2));
    wbkgd(slot2, COLOR_PAIR(i%2 +1));
    wbkgd(slot3, COLOR_PAIR(2 - i%2 - (1 - i/2)));
    wrefresh(slot1);
    wrefresh(slot2);
    wrefresh(slot3);
}

void ContinueMenuClass :: startContinue(string& name){
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WindowGenerator border = WindowGenerator(0, 0, yMax, xMax); //screen border
    WindowGenerator mw = WindowGenerator(1, 1, yMax - 2, xMax - 2); //main window

    string ng = "Continue";
    mvwprintw(mw.getW(), 2, mw.getWidth()/2 - ng.length()/2, "%s", ng.c_str()); 

    int mheight = 20;
    int mwidth = xMax-40;
    int cvmwin = yMax/2 - mheight/2; //centre menuwin vertically  
    int comwin = xMax/2 - mwidth/2; //centre menuwin horizzontally 
    WindowGenerator menuwin = WindowGenerator(cvmwin, comwin, mheight, mwidth);
    
    int sheight = 6;
    int swidth = 46;
    WindowGenerator slot[nchoices];
    int k = 0;
    while(k < nchoices){
        slot[k] = WindowGenerator(cvmwin + 1 + k*6, mwidth/2 - 3, sheight, swidth);
        k++;
    }

    refresh();
    border.show_window();
    mw.show_window();
    menuwin.show_window();

    keypad(menuwin.getW(), true); 

    int choice;
    int highlight = 0;
    init_pair(1,COLOR_WHITE, COLOR_BLACK);
    init_pair(2,COLOR_BLACK, COLOR_WHITE);
    while(1){
        for(int i = 0; i < nchoices; i++){
            if(i == highlight){
                wattron(menuwin.getW(), A_REVERSE);
                changeSlot(slot[0].getW(), slot[1].getW(), slot[2].getW(), highlight, i);
                //changeSlot(slot1, slot2, slot3, highlight, i);
            }
            mvwprintw(menuwin.getW(), 3 + i*6, mwidth/2 - swidth/3, "%s", getGame(i).c_str());
            mvwprintw(menuwin.getW(), 4 + i*6, mwidth/2 - swidth/3, "%s", getStatus(i).c_str());
            wattroff(menuwin.getW(), A_REVERSE);
        }
        choice = wgetch(menuwin.getW());

        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = nchoices - 1;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == nchoices)
                    highlight = 0;
                break;
            default:
                break;
        }
        if(choice == 10)
            break;
    }

     //make sure program waits before exiting...
    getch();
    endwin();
}