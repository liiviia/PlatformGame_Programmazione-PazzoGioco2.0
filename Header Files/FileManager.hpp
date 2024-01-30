#pragma once
#include <string>
#include <fstream>

using namespace std;

class FileManager{
    private:
        string FileNames[15]{
            "cur_score.txt",
            "best_score.txt",
            "coins.txt"
            "ATK.txt",
            "DEF.txt",
            "HP.txt",
            "JMP.txt"
        };
        int numFiles = 7;
    public:
        FileManager();

        //Getters
        string getCurScore();
        string getBstScore();
        string getCoins();
        string getATK();
        string getDEF();
        string getHP();
        string getJMP();
        int getNumFiles();
        int getFileValue(string);

        //Setters
        void setFile(string);

        //Other methods
        bool check_exist(string);
        void updateFile(string, int);

        void updateScore(); 
};