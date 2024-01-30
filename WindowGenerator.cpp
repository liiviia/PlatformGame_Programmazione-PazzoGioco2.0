#include "./Header Files/WindowGenerator.hpp"

//Constructors
WindowGenerator :: WindowGenerator(int y, int x, int height, int width){
    setY(y);
    setX(x);
    setHeight(height);
    setWidth(width);
    win = newwin(height, width, y, x);
}

WindowGenerator :: WindowGenerator(){
    setY(0);
    setX(0);
    setHeight(0);
    setWidth(0);
}

//Setters
void WindowGenerator :: setY(int y){this->y = y;}
void WindowGenerator :: setX(int x){this->x = x;}
void WindowGenerator :: setHeight(int height){this->height = height;}
void WindowGenerator :: setWidth(int width){this->width = width;}

//Getters
int WindowGenerator :: getY(){return y;}
int WindowGenerator :: getX(){return x;}
int WindowGenerator :: getHeight(){return height;}
int WindowGenerator :: getWidth(){return width;}
WINDOW* WindowGenerator :: getW(){return win;}

//Other Functions
void WindowGenerator :: show_window(){box(win, 0, 0); wrefresh(win);}