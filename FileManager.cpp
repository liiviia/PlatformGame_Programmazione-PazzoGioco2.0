#include "./Header Files/FileManager.hpp"


//Constructor
FileManager :: FileManager(){
    for(int i = 0; i < getNumFiles(); i++){
        setFile(FileNames[i]);
    }
}

//Getters
string FileManager :: getCurScore() {return FileNames[0];}
string FileManager :: getBstScore() {return FileNames[1];}
string FileManager :: getCoins()    {return FileNames[2];}
string FileManager :: getATK()      {return FileNames[3];}
string FileManager :: getDEF()      {return FileNames[4];}
string FileManager :: getHP()       {return FileNames[5];}
string FileManager :: getJMP()      {return FileNames[6];}
int FileManager :: getNumFiles()    {return numFiles;}

//This methods returns an integer corresponding
//the value saved on a file passed as a parameter.
//It converts the string of the type file into an 
//integer and returns it.
//If the file doesn't exist or si empty, the method
//returns -1
int FileManager :: getFileValue(string filename){
    if(!check_exist(filename)){
        string v;
        ifstream value;
        value.open(filename);
        getline(value, v);
        value.close();
        return stoi(v);
    }

    return -1;
};

//Setters
void FileManager :: setFile(string filename){
    if(check_exist(filename)){
        ofstream createFile;
        createFile.open(filename);
        
        //set the defeault value of the scores and power-up to 0
        createFile<<0; 
        createFile.close();
    } 
}

//Other Methods

//Return true if a file doesn't exist or it's empty.  
bool FileManager :: check_exist(string filename){
    ifstream file;
    file.open(filename);
    bool contr = !file.is_open() || file.peek() == EOF;
    file.close();
    return contr;
}

//This method update the value saved in the file with a new value
void FileManager :: updateFile(string filename, int value){
    if(!check_exist(filename)){
        ofstream update;
        update.open(filename);
        update << value;
        update.close(); 
    }
}


//This method updates the best score if at the end of a level,
//the current score is greater then the best.
void FileManager :: updateScore(){
    if(!check_exist(getCurScore()) && !check_exist(getBstScore())){
        ifstream update;
        int v1, v2;
        string s;
        //Value of the currentScore
        update.open(getCurScore());
        getline(update, s);
        v1 = stoi(s);
        update.close();
        
        //Value of the best score
        update.open(getBstScore());
        getline(update, s);
        v2 = stoi(s);
        update.close();

        if(v1 > v2){
            ofstream update;
            update.open(getBstScore());

            update << v1;
        }
    }
}