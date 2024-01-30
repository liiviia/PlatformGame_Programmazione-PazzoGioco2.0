#include "./Header Files/MainMenu.hpp"
#include "./Header Files/ContinueMenu.hpp"
#include "./Header Files/NewGameMenuClass.hpp"

MainMenu :: MainMenu(){
    setGameName(startMenu());
}

void MainMenu :: setGameName(string gameName){
    GameName = gameName;
}

string MainMenu :: getGameName(){return GameName;}

string MainMenu :: startMenu(){    
    string name;
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    WindowGenerator border = WindowGenerator(0, 0, yMax, xMax);
    WindowGenerator mw = WindowGenerator(1, 1, yMax - 2, xMax - 2);

    int mwinHeight = 10; //Altezza della finestra del menu
    int mwinWidth = 20; //Larghezza della finestra del menu
    
    //File I/0
    string filename[2] = {"points.txt", "dummy.txt"};
    //ifstream points; //inizialization of a file object
    //bool Open = check_exist(filename, 0);
    ofstream pointsdummy;
    pointsdummy.open("dummy.txt");
    //points.open("points.txt", ios::in); //opens the file both in input and in output

    int cur_score = 0, bst_score = 0, coins = 0;
    int p_upindex = 6;
    //string p_up_values[p_upindex];
    string p;
    p_ups perks[p_upindex];
    int i = 0;
 
    if(check_exist(filename, 0)){
        ofstream pointsout;
        pointsout.open("points.txt");
        //The while loop print in the file the default value of 0 for the
        //Current Score, Best Score, 
        //Current Coins and th ATK+, GUN+, MOV+, HP+ and ARM+ Power-Ups
        while(i < 9){
            if(i < 8)
                pointsout<<0<<endl;
            else
                pointsout << 0;
            i++;
        }
        pointsout.close(); 
    }
    ifstream points;
    points.open(filename[0]);
    i = 0;
    while (!points.eof()){
        getline(points, p);
        switch(i){
            case 0:
                cur_score = stoi(p);
                i++;
                break;
            case 1:
                bst_score = stoi(p);
                i++;
                break;
            case 2:
                coins = stoi(p);
                i++;
                break;
            default:
                perks[i-3].value = p;
                i++;
                break;
        }
        if(i < 9)
            pointsdummy << p << endl;
        else
            pointsdummy << p;
    }
    pointsdummy.close();
    points.close(); //Closes the file containing the scores and power-up of the player
    
    if(cur_score > bst_score){ //checks if the current_score is greater than the best_score
        bst_score = cur_score; //if it's greater it copies cur_score in bst_score
        ofstream writeOnpoints;
        ifstream readFrompoints;
        writeOnpoints.open("points.txt");
        readFrompoints.open("dummy.txt");
        int i = 0;
        while (!readFrompoints.eof())
        {
            getline(readFrompoints, p);
            if(i != 1 && i < 8)
                writeOnpoints << p <<endl;
            else if(i >= 8)
                writeOnpoints << p;
            else
                writeOnpoints << to_string(bst_score) <<endl;
            i++;
        }
        writeOnpoints.close();
        readFrompoints.close();
    }
    
    int pNcWidth = 30;
    WINDOW * pointsNCoinswin = newwin(mwinHeight, pNcWidth, yMax/2 - mwinHeight/2, xMax/2 - mwinWidth/2 - 30);
    
    int n = 3;
    string scoring[n] = {"Current Score", "Best Score", "Coins"};
    
    int j = 0;
    
    //Shows the score of the last game. 
    //It displays as a score from 1 to 9999 + T (T is the tier and its
    //calculated by 9999*tier_number e.g. T1 = 9999, T2 = 9999 * 2) 
    score_displays(pointsNCoinswin, pNcWidth, scoring, j, cur_score);
    j++;

    //Estimates the best score ever. 
    //It displays as a score from 1 to 9999 + T (T is the tier and its
    // calculated by 9999*tier_number e.g. T1 = 9999, T2 = 9999 * 2) 
    score_displays(pointsNCoinswin, pNcWidth, scoring, j, bst_score);
    j++;
    //Shows the number of coins of the last started game
    //The number of coins can't increase over 999
    score_displays(pointsNCoinswin, pNcWidth, scoring, j, coins);
    

    WINDOW * menuwin = newwin(mwinHeight, mwinWidth, 
    yMax/2 - mwinHeight/2,  // yMax/2-minwHeight/2 serve a centrare verticalmente la finestra
    xMax/2 - mwinWidth/2); // xMax/2-minwWidth/2 serve a centrare orizzontalmente la finestra
    
    int pupHeight = 10;
    int pupWidth = 30;
    WINDOW * power_upwin = newwin(pupHeight, pupWidth, yMax/2 - mwinHeight/2, xMax/2 + mwinWidth/2);
    string p_up[p_upindex] = {"ATK+", "GUN+", "MOV+", "JMP+", "ARM+", "HP+"};

    mvwprintw(power_upwin, 1, pupWidth/2 - 12, "%s", "Current Game Power-Ups");
    power_up_displays(power_upwin, perks, pupWidth, p_upindex);
    
    refresh();
    border.show_window();
    mw.show_window();
    box(pointsNCoinswin, 0, 0);
    box(menuwin, 0, 0);
    box(power_upwin, 0, 0);
    wrefresh(pointsNCoinswin);
    wrefresh(menuwin);
    wrefresh(power_upwin);

    keypad(menuwin, true);
    int nchoices = 4; //the set number of choices 
    string choices[nchoices] = {"New Game", "Continue", "Exit Game", "Controls"};
    int choice;
    int highlight = 0;

    while(1){
        for(int i = 0; i < nchoices; i++){
            if(i == highlight){
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, mwinHeight/2 - nchoices/2 + i, mwinWidth/2 - 8/2, "%s", choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);
        bool skip = check_continue();
        switch(choice){
            case KEY_UP:
                highlight--;
                if(skip == true && highlight == 1)
                    highlight --;
                if(highlight == -1)
                    highlight = nchoices - 1;
                break;
            case KEY_DOWN:
                highlight++;
                if(skip == true && highlight == 1)
                    highlight ++;
                if(highlight == nchoices)
                    highlight = 0;
                break;
            default:
                break;
        }
        if(choice == 10)
            break;
    }

    switch(highlight){
            case 0:{  //case highlight == 0 ("New Game") calls the constructor for the NewGameMenu
                NewGameMenuClass NewGame = NewGameMenuClass();
                NewGame.startNewGame(name);
                break;
            }
            case 1:{ //case highlight == 1 ("Continue") calls the constructor for the ContinueGameMenu
                ContinueMenuClass Continue = ContinueMenuClass();
                Continue.startContinue(name);
                break;
            }
            case 2: //case highlight == 2 ("Exit Game") ends the session
                endwin();
                break;
            case 3: //case highlight == 3 ("Controls") shows the window with information on how to play
            default:
                break;
    }

    return name;
}

string MainMenu :: tier_calculator(int score){
    return "xT" + to_string(score/10000);
}

int MainMenu :: score_calculator(int score){
    return score%10000;
}

void MainMenu :: score_displays(WINDOW *pointsNCoinswin, int pNcWidth, string s[], int n, int tscore){
    string tier = "";
    int score = tscore;
    if(n != 2){
        tier = tier_calculator(tscore);
        score = score_calculator(tscore);
    }
    mvwprintw(pointsNCoinswin, n*3+1, pNcWidth/2 - s[n].length()/2, "%s", s[n].c_str());
    mvwprintw(pointsNCoinswin, n*3+2, pNcWidth/2 - to_string(score).length()/2, "%d", score);
    mvwprintw(pointsNCoinswin, n*3+2, pNcWidth/3*2 + 1, "%s", tier.c_str());
}

void MainMenu :: power_up_displays(WINDOW* power_upwin, p_ups perks[], int pupWidth, int n){
    int i = 0;
    while(i < n){
        mvwprintw(power_upwin, ((i/3)+1)*3, (pupWidth/(3-((i%3)%2)) + (pupWidth/3*(((n-i)%3)%2))) - (perks[i].name.length()-(n-i)%3-3*(((n-i)%3)%2)), "%s", perks[i].name.c_str());
        mvwprintw(power_upwin, ((i/3)+1)*3 + 1, (pupWidth/(3-((i%3)%2)) + (pupWidth/3*(((n-i)%3)%2))) - (perks[i].name.length()-(n-i)%3-3*(((n-i)%3)%2)) + 1, "%s", perks[i].value.c_str());
        i++;
    }
}

bool MainMenu :: check_continue(){
    ifstream info;
    info.open("informations.txt");
    string contr = "Empty";
    bool skip = true;
    if(info.is_open()){
        string t;
        while(!info.eof() && contr == "Empty"){
            getline(info, contr);
        }
        if(contr != "Empty")
            skip = false;
    }
    return skip;
}

bool MainMenu :: check_exist(string name[], int i){
    ifstream file;
    file.open(name[i]);
    return !file.is_open() || file.peek() == EOF;
}