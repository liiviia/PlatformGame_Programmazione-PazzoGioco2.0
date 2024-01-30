#include"./Header Files/Shop.h"
#include"./Header Files/Coin.h"
#include"./Header Files/Game.h"
#include"./Header Files/Player.h"

#include<iostream> 
using namespace std; 

Shop::Shop(){

    setMaxY(getmaxy(stdscr)); 
    setMaxX(getmaxx(stdscr)); 
    setWidth(40); 
    setHeight(25);
    setColorIt(1);
    setColorItDelay(0);
    setInDisplayHouse(true); 


    loadItemsFromFile("Items.txt"); 
    
}


/* Questa funzione fa in modo che gli elementi all'interno del file siano 
   trasformati in una lista*/
void Shop::loadItemsFromFile(const string& filename) {
   ifstream input(filename);
    if (!input.is_open()) {
        cout << "Errore nell'apertura del file " << filename << endl;
        return;
    }
    string line;
    while (getline(input, line)) {  // Assegna ad ogni elemento in input la stringa line 
        istringstream iss(line); // Crea un oggetto istringstream chiamato iss che permette di leggere dalla stringa line
        shopItem* newItem = new shopItem;  // Alloca memoria per il nuovo elemento

        if (!(iss >> newItem->name >> newItem->price >> newItem->purchased)) {
            cout << "Errore nella lettura della riga: " << line << endl;
            delete newItem;  // Libera la memoria in caso di errore
            continue; // Salta il resto del ciclo e passa all'iterazione successiva 
        }
        items.push_back(newItem); // aggiunge il puntatore newItem all'oggetto items, che è una lista 
    }
    input.close();
}


void Shop::drawShop(int y, int x, int width, int height, char *title) {
    // Bordo esterno del riquadro
    mvaddch(y, x, ACS_ULCORNER);
    mvhline(y, x + 1, ACS_HLINE, width - 2);
    mvaddch(y, x + width - 1, ACS_URCORNER);
    mvvline(y + 1, x, ACS_VLINE, height - 2);
    mvvline(y + 1, x + width - 1, ACS_VLINE, height - 2);
    mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);
    mvhline(y + height - 1, x + 1, ACS_HLINE, width - 2);
    mvaddch(y + height - 1, x, ACS_LLCORNER);

    // Titolo al centro del riquadro
    attron(A_BOLD);
    mvprintw(y, x + (width - strlen(title)) / 2, title);
    attroff(A_BOLD);
}


void Shop::displayHouse(Player *player){
    
    if(inDisplayHouse){

    int shopStart = (maxX / 2) - 7;

    const char* myString;

    if(getColorItDelay() >= 20){
    
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"( _____  _)";
        mvprintw(maxY - 20, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));

        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(/  ___|| |)";
        mvprintw(maxY - 19, (maxX/2)-12, myString);                
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(\ `--. | |__    ___   _ __)";
        mvprintw(maxY - 18, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"( `--. \| '_ \  / _ \ | '_ \)";
        mvprintw(maxY - 17, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(/\__/ /| | | || (_) || |_) |)";
        mvprintw(maxY - 16, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(\____/ |_| |_| \___/ | .__/)";
        mvprintw(maxY - 15, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(                     | |)";
        mvprintw(maxY - 14, (maxX/2)-12, myString);  
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(                     |_|)";
        mvprintw(maxY - 13, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));

        setColorItDelay(0);
    
    }
    else{
        int temp = colorIt;

        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"( _____  _)";
        mvprintw(maxY - 20, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));

        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(/  ___|| |)";
        mvprintw(maxY - 19, (maxX/2)-12, myString);                
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(\ `--. | |__    ___   _ __)";
        mvprintw(maxY - 18, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));    
        myString = R"( `--. \| '_ \  / _ \ | '_ \)";
        mvprintw(maxY - 17, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(/\__/ /| | | || (_) || |_) |)";
        mvprintw(maxY - 16, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(\____/ |_| |_| \___/ | .__/)";
        mvprintw(maxY - 15, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(                     | |)";
        mvprintw(maxY - 14, (maxX/2)-12, myString);  
        attroff(COLOR_PAIR(colorIt));
        
        attron(COLOR_PAIR(colorIt = (colorIt % 5) + 1));
        myString = R"(                     |_|)";
        mvprintw(maxY - 13, (maxX/2)-12, myString);
        attroff(COLOR_PAIR(colorIt));

        colorIt = temp;
    }


    // Per settare disegno e colore casa
    attron(COLOR_PAIR(12));
    for(int j = (shopStart - 1); j < (shopStart + 19); j++){         
        mvprintw(maxY - 9, j, "#");
    }

    for(int j = (shopStart - 2); j < (shopStart + 20); j++){       
        mvprintw(maxY - 8, j, "#");
    }

    for(int j = (shopStart - 2); j < (shopStart + 20); j++){         
        mvprintw(maxY - 7, j, "#");
    }
  
    for(int i = maxY - 2; i > (maxY - 7); i--){
        for(int j = shopStart; j < (shopStart + 18); j++){
            mvprintw(i, j, "#");
        }
    }
    attroff(COLOR_PAIR(12));

    // Per settare disegno e colore porta 
    attron(COLOR_PAIR(9)); 
    int centerX = shopStart + 7;
    int centerY = maxY - 3; // Incrementa la coordinata Y per la piattaforma

    for (int i = centerY - 1; i <= centerY + 1; i++) {
        for (int j = centerX ; j <= centerX + 3; j++) {
            mvprintw(i, j, " ");
        }
    }
    attroff(COLOR_PAIR(9));
    }
}


bool Shop::checkOpenShop(Player player){
   int shopDoorR = (maxX / 2) + 2 ;  
   int shopDoorL = (maxX / 2) - 2; 

   if (shopDoorL <= player.getPos().x && shopDoorR >= player.getPos().x)
        return true; 
    else
        return false;  
}


bool Shop::isPurchaseValid(shopItem* itemIndex, int &playerCoins) {
    for (auto it = items.begin(); it != items.end(); ++it) {
       if ((*it)->name == itemIndex->name && !(*it)->purchased && itemIndex->price <= playerCoins && !checkItems((*it))) {
            (*it)->purchased = true;
            playerCoins -= (*it)->price; 
            updateBudget(playerCoins); 
            savePurchaseToFile(itemIndex);
            return true; // L'acquisto è valido
        } 
    }
    return false; // L'acquisto non è valido
}


// Controlla se l'item è gia presente nel file itemsPurchase.txt
bool Shop::checkItems(shopItem* purchasedItem) {
    ifstream inputFile("itemsPurchase.txt");
    
    if (inputFile.is_open()) {
        string itemName; 
        while (inputFile >> itemName) {
            if (itemName == purchasedItem->name) {
                inputFile.close(); // Chiudi il file
                return true; 
            } 
        }
        inputFile.close();
    }
    return false;    
}


// Funzione per salvataggio nel file itemsPurchase.txt
void Shop::savePurchaseToFile(shopItem* purchasedItem){
    ofstream outputFile("itemsPurchase.txt", ios::app); 
    if (outputFile.is_open()){
        outputFile << purchasedItem->name << endl; 
        outputFile.close(); 
    }
}


// Aggiorna e salva budget ad ogni acquisto 
void Shop::updateBudget(int &playerCoins){

    ofstream outfile("budget.txt");

    outfile << playerCoins << endl;
    outfile.close();   

}


void Shop::displayShopWithSelection(shopItem* selectedItem) {

    int shopWidth = getWidth();  // Larghezza del riquadro del negozio
    int shopHeight = getHeight(); // Altezza del riquadro del negozio

    // Calcolo per la posizione per il riquadro del negozio al centro dello schermo
    int y = (maxY - shopHeight) / 2;
    int x = (maxX - shopWidth) / 2;

    drawShop(y, x, shopWidth, shopHeight, "SHOP");

    int itemY = y + 2; 
    int itemX = x + 2; 

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (selectedItem == *it) {
            attron(A_REVERSE);
        }
        if ((*it)->purchased){
            attron(COLOR_PAIR(13));
        }

        mvwprintw(stdscr, itemY, itemX, "%ld. %s - $%d", distance(items.begin(), it) + 1, (*it)->name.c_str(), (*it)->price); 
    
        attroff(COLOR_PAIR(13));
        attroff(A_REVERSE); 
        
        itemY++;
    }
}


void Shop::navigateShop(int &playerCoins) {
    //this->setInDisplayHouse(false); 

    auto it = items.begin();

    string itemName; 

    while (true) {
        displayShopWithSelection(*it);

        int ch = getch();

        if (ch == KEY_UP && it != items.begin()) {
            --it;
        } 
        else if (ch == KEY_DOWN) {
            auto lastItem = prev(items.end());
            if (it != lastItem) {
                ++it;
            }
        } 
        else if (ch == 10) { // 10 è il codice ASCII per il tasto "Invio"
            if (checkItems((*it))){
                mvprintw(0, 0, "Acquisto GIA' effettuato                             ");
            }
            else if(isPurchaseValid((*it), playerCoins)) { 
                mvprintw(0, 0, "Acquisto riuscito! Budget attuale: $%d", playerCoins);
                getch();   
            } else {
                mvprintw(0, 0, "Acquisto NON riuscito!                               ");
                getch(); 
            }
        }
    }
}


void Shop::incrementColorItDelay(){ this->colorItDelay += 1; }

void Shop::returnToDisplayHouse() { this->setInDisplayHouse(true); }

// Getters 
int Shop::getMaxY() { return this->maxY; }
int Shop::getMaxX() { return this->maxX; } 
int Shop::getWidth(){ return this->shopWidth; } 
int Shop::getHeight(){ return this->shopHeight; }
shopItem Shop::getItem(){ return this->Item; }
list<shopItem*> *Shop::getItemList(){ return &this->items; }
int Shop::getColorIt() { return this->colorIt; }
int Shop::getColorItDelay() { return this->colorItDelay; }
bool Shop::getInDisplayHouse() { return this->inDisplayHouse; }


// Setters
void Shop::setMaxY(int maxY) {this->maxY = maxY; }
void Shop::setMaxX(int maxX) {this->maxX = maxX; }
void Shop::setItem(shopItem item) {this->Item = item; }
void Shop::setWidth(int widht) { this->shopWidth = widht; }
void Shop::setHeight(int height) { this->shopHeight = height; }
void Shop::setColorIt(int color) { this->colorIt = color; }
void Shop::setColorItDelay(int delay) { this->colorItDelay = delay; }
void Shop::setInDisplayHouse(bool in) { this->inDisplayHouse = in; }
