#pragma once
#include <curses.h>
#include <string>
#include <fstream>
#include <time.h>
#include "WindowGenerator.hpp"

using namespace std;

struct p_ups{
    string name;
    string value;
};

class MainMenu{
    private:
        string GameName;

    public:

    //Constructor
    MainMenu();

    //Setters
    void setGameName(string);
    //Getters
    string getGameName();

    //Others

    string startMenu();
    //score_calculator is a function that gets an int in input and returns a string 
    //it returns the result of the % (modulus) operation between 
    //the integer and 10000 (e.g. n%10000) as a string
    int score_calculator(int);

    //tier_calculator is a function that gets an int in input and returns a string 
    //it returns the result of the / (division) operation between 
    //the integer and 10000 (e.g. n/10000) as a string
    string tier_calculator(int);

    //score_displays is a void function that prints the Current Score, Best Score and Number of Coins owned
    void score_displays(WINDOW*, int, string [], int, int);

    //power_up_displays prints the values of the stats of the player in the last started game
    void power_up_displays(WINDOW*, p_ups[], int, int);

    bool check_continue(); //this function checks if there is at least one started game in a slot

    bool check_exist(string[], int);

};