#include "./Header Files/NewGameMenuClass.hpp"
#include "./Header Files/MapClass.hpp"

const int nchoices = 3; //the set number of choices 

//Constructor
NewGameMenuClass :: NewGameMenuClass(){
    readFromFile();
}

//Setters
void NewGameMenuClass :: setGame(int i){
    NewGames[i].game = "Game " + to_string(i+1);
}
void NewGameMenuClass :: setStatus(string value, int i){
    NewGames[i].status = value;
}

//Getters
string NewGameMenuClass :: getGame(int i){
    return NewGames[i].game;
}
string NewGameMenuClass :: getStatus(int i){
    return NewGames[i].status;
}

//Other Function
void NewGameMenuClass :: readFromFile(){
    ifstream info;
    info.open("informations.txt");
    bool isEmpty = info.peek() == EOF;
    //int nchoices = 3; //total number of slots
    string status[nchoices] = {"Empty", "Empty", "Empty"};
    int i = 0;
    if(!info.is_open() || isEmpty == true){
        ofstream infoout;
        infoout.open("informations.txt");
        while(i < 2){
            infoout << "Empty" << endl;
            i++;
        }
        infoout<<"Empty";
        infoout.close();
    }
    else{
        string p;
        int j = 0;
        while(!info.eof() || j < 3){
            getline(info, p);
            setStatus(p, j);
            setGame(j);
            j++;
        }
    }
    info.close();
}

void NewGameMenuClass :: changeSlot(WINDOW* slot1, WINDOW* slot2, WINDOW* slot3, int highlight, int i){
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

void NewGameMenuClass :: startNewGame(string& name){
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WindowGenerator border = WindowGenerator(0, 0, yMax, xMax); //screen border
    WindowGenerator mw = WindowGenerator(1, 1, yMax - 2, xMax - 2); //main window

    string ng = "New Game";
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

    overrideGame(cvmwin, comwin, mheight, mwidth, highlight, mw, highlight, name);
    endwin();
}

void NewGameMenuClass :: overrideGame(int y, int x, int height, int width, int n_slot, WindowGenerator mw, int nslot, string& name){
    //this functions has the purpose to ask the user
    //if he wants to start a new game in the selected slot
    WindowGenerator selwin = WindowGenerator(y, x, height, width);
    string quest = "Are you sure you want to use this save slot?";
    mvwprintw(selwin.getW(), 2, selwin.getWidth()/2 - quest.length()/2, "%s", quest.c_str());

    WindowGenerator select[2];

    select[0] = WindowGenerator(selwin.getHeight()/2 + 4, mw.getWidth()/2 - 9, 5, 20);
    select[1] = WindowGenerator(selwin.getHeight()/2 + select[0].getHeight() * 2, mw.getWidth()/2 - 9, 5, 20);

    refresh();
    selwin.show_window();

    keypad(selwin.getW(), true);

    int choice;
    int highlight = 0;
    init_pair(8,COLOR_WHITE, COLOR_BLACK);
    init_pair(9,COLOR_BLACK, COLOR_WHITE);
    box(select[0].getW(), 0, 0);
    box(select[1].getW(), 0, 0);
    while(1){
        for(int i = 0; i < nchoices - 1; i++){
            if(i == highlight && i == 0){
                wbkgd(select[0].getW(), COLOR_PAIR(8));
                wbkgd(select[1].getW(), COLOR_PAIR(9));
            }
            else if(i == highlight && i == 1){
                wattron(selwin.getW(), A_REVERSE);
                wbkgd(select[0].getW(), COLOR_PAIR(9));
                wbkgd(select[1].getW(), COLOR_PAIR(8));
            }
            wrefresh(select[0].getW());
            wrefresh(select[1].getW());
            mvwprintw(selwin.getW(), selwin.getHeight()/3, selwin.getWidth()/2 - 3, "%s", "ACCEPT");
            mvwprintw(selwin.getW(), selwin.getHeight()/3 + select[1].getHeight() + 1, selwin.getWidth()/2 - 3, "%s", "CANCEL");
            wattroff(selwin.getW(), A_REVERSE);
        }
        
        choice = wgetch(selwin.getW());

        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 1;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 2)
                    highlight = 0;
                break;
            default:
                break;
        }
        if(choice == 10)
            break;
    }

    switch(highlight){
        case 0:
            startNewGame(name);
            break;
        case 1:{
            chooseName(y, x, height, width, nslot, name);
            break;
        }
        default:
            break; 
    }
}

void NewGameMenuClass :: chooseName(int y, int x, int height, int width, int nslot, string& FileGame){
    WindowGenerator namewin = WindowGenerator(y, x, height, width);
    string quest = "Choose your name";
    mvwprintw(namewin.getW(), 2, namewin.getWidth()/2 - quest.length()/2, "%s", quest.c_str());

    refresh();
    namewin.show_window();

    keypad(namewin.getW(), true);
    char nameLetters[nchoices] = {'A', 'A', 'A'};
    int choice;
    int highlight = 0;

    while(1){
        for(int i = 0; i < nchoices; i++){
            if(i == highlight){
                wattron(namewin.getW(), A_REVERSE);
            }
            mvwprintw(namewin.getW(), namewin.getHeight()/2 - nchoices/2, namewin.getWidth()/2 - 3 + i + i*1, "%c", nameLetters[i]);
            wattroff(namewin.getW(), A_REVERSE);
        }
        choice = wgetch(namewin.getW());
        switch(choice){
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = nchoices - 1;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == nchoices)
                    highlight = 0;
                break;
            case KEY_DOWN:
                nameLetters[highlight]++;
                if(nameLetters[highlight] > 90)
                    nameLetters[highlight] = 65;
                break;
            case KEY_UP:
                nameLetters[highlight]--;
                if(nameLetters[highlight] < 65)
                    nameLetters[highlight] = 90;
                break;
            default:
                break;
        }
        if(choice == 10)
            break;

        string name;
        name.push_back(nameLetters[0]); 
        name.push_back(nameLetters[1]);
        name.push_back(nameLetters[2]);

        ifstream slotNames;
        slotNames.open("informations.txt");
        string GameNames[3];
        string p;
        int j = 0;
        while(!slotNames.eof() || j < 3){
            getline(slotNames, p);
            if(j == nslot)
                GameNames[j] = name;
            else
                GameNames[j] = p;
            j++;
        }
        slotNames.close();
        ofstream infowrite;
        infowrite.open("informations.txt");
        int i = 0;
        while(i < 2){
            infowrite << GameNames[i] <<endl;
            i++;
        }
        infowrite << GameNames[2];
    }
    FileGame = "game" + to_string(nslot+1) + ".txt";
}