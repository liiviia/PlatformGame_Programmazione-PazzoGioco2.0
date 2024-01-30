#pragma once
#include <curses.h>

using namespace std;


class WindowGenerator{
    private:
        int y;
        int x;
        int height;
        int width;
        WINDOW* win;

    public:
        //Constructors
        WindowGenerator(int, int, int, int);
        WindowGenerator();

        //Setters
        void setY(int);
        void setX(int);
        void setHeight(int);
        void setWidth(int);

        //Getters
        int getY();
        int getX();
        int getHeight();
        int getWidth();
        WINDOW* getW();
        
        //Other Functions
        void show_window();

};