#pragma once 

#include<sstream>
#include<fstream>
#include<list>
#include<string>
#include<string.h>
#include<ncurses.h>
#include<set>
using namespace std;


struct shopItem{
    string name;
    int price; 
    bool purchased; 

    shopItem() : name(""), price(0), purchased(false) {}
    shopItem(const string& n, int p, bool pur) : name(n), price(p), purchased(pur) {}
}; 

class Coin;
class Game;
class Player;

class Shop{

    public: 
        Shop(); 

        void loadItemsFromFile(const std::string& filename); 

        void drawShop(int y, int x, int widht, int height, char *title); 

        void displayHouse(Player *player); 

        bool checkOpenShop(Player player); 
        
        // Verifica sel'acquisto è valido
        bool isPurchaseValid(shopItem* itemIndex, int &playerCoins);
        
        bool checkItems(shopItem* purchasedItem); 

        void savePurchaseToFile(shopItem* purchasedItem); 

        void updateBudget(int &playerCoins); 

        void displayShopWithSelection(shopItem* selectedItem); 

        void navigateShop(int &playerCoins); 

        void incrementColorItDelay();

        void returnToDisplayHouse();


    // Getters
    int getMaxY(); 
    int getMaxX(); 
    int getWidth(); 
    int getHeight(); 
    shopItem getItem();
    list<shopItem*> *getItemList();
    int getColorIt();
    int getColorItDelay();
    bool getInDisplayHouse(); 
    

    // Setter
    void setMaxY(int y); 
    void setMaxX(int x); 
    void setItem(shopItem item);
    void setWidth(int width); 
    void setHeight(int height); 
    void setColorIt(int color);
    void setColorItDelay(int delay);
    void setInDisplayHouse(bool in); 
    

    private: 
        int maxY, maxX; 
        shopItem Item; 
        list<shopItem*> items; 
        int shopWidth;
        int shopHeight;
        int colorIt = 1;
        int colorItDelay = 0;
        bool inDisplayHouse; 
        WINDOW *shopWin; 
        
};