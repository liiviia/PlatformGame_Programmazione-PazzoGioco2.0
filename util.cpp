#include"./Header Files/util.h"

#include"./Header Files/Entity.h"
#include"./Header Files/Player.h"
#include"./Header Files/Platform.hpp"

#include<random>
#include<cmath>
using namespace std;

float randomFloatInRange(float min, float max){

    //  Ho dovuto usare la libreria random perchè la funzione rand() non era abbastanza robusta, dato che
    //  come seed utilizza l'orario del sistema e ci sono buone probabilità che i numeri random
    //  vengano generati a pochi millisecondi di distanza l'uno dall'altro, generando numeri praticamente identici

    //  utilizzato per generare un seed casuale
    random_device rd;   
    //  mt19937 è il generatore Mersenne Twister di numeri random, lo inizializzo con il seed rd
    mt19937 gen(rd());  
    //  crea un oggetto di distribuzione uniforme che genera numeri random all'interno dell'intervallo
    uniform_real_distribution<float> dis(min, max); 

    //  uso il generatore combinato all'oggetto di distribuzione per generare un numero float random
    return dis(gen);

}

int approxFloat(float n){

    int a = (int)n;
    float temp = n - (float)a;

    if(temp >= 0.5)
        return ceil(n);
    else
        return floor(n);

}

bool isInSet(set<float> recordedPos, float xPos){

    set<float>::iterator it = recordedPos.find(xPos);

    if(it != recordedPos.end())
        return true;
    else
        return false;

}

bool isInSafeZone(Player player, float xPos){

    if(xPos <= player.getPos().x + 10 && xPos >= player.getPos().x - 10)
        return true;
    else
        return false;

}


//  Funzione booleana che ritorna 1 o -1 se la piattaforma del nemico è compresa completamente
//  o parzialmente nell'area superiore (1) o inferiore (-1) compresa tra il punto d'inizio e il punto
//  di fine della piattaforma del player. Ritorna 0 altrimenti.
short int isInPlatformArea(obPointer playerPlatform, obPointer enemyPlatform){
    Platform player = Platform ();
    Platform enemy = Platform ();
    player.setObPointer(playerPlatform);
    enemy.setObPointer(enemyPlatform); 
    if(playerPlatform == enemyPlatform)
        return 1;

    Point playerPlatformStart = player.getStart();
    Point playerPlatformEnd = player.getEnd();

    Point enemyPlatformStart = enemy.getStart();
    Point enemyPlatformEnd = enemy.getEnd();
    

    bool s;


    //  Controllo se la piattaforma dell'enemy è inclusa o totalmente o parzialmente all'interno dell'area della piattaforma del player
    if(enemyPlatformStart.x > playerPlatformStart.x && enemyPlatformEnd.x < playerPlatformEnd.x)
        s = true;
    else if((enemyPlatformStart.x < playerPlatformStart.x && (enemyPlatformEnd.x > playerPlatformStart.x && enemyPlatformEnd.x < playerPlatformEnd.x))
            || ((enemyPlatformStart.x > playerPlatformStart.x && enemyPlatformStart.x < playerPlatformEnd.x) && enemyPlatformEnd.x > playerPlatformEnd.x))
        s = true;
    else if(enemyPlatformStart.x < playerPlatformStart.x && enemyPlatformEnd.x > playerPlatformEnd.x)
        s = true;
    else
        s = false;

    // Se s è vero (quindi la enemyPlatform è inclusa nell'area di playerPlatform), controllo se è sopra o sotto
    if(s){

        if(enemyPlatformStart.y < playerPlatformStart.y)
            return 1;
        else
            return -1;

    }
    else
        return 0;

    return 0;

}

/*Platform* getStandingPlatform(Entity entity, list<Platform*> platforms){

    if(!entity.getIsFalling()){

        Point standingPos;
        standingPos.y = entity.getPos().y; standingPos.x = entity.getPos().x;

        for(list<Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it){

            if(standingPos.y == ((*it)->getStart().y - 1)){

                if(standingPos.x >= (*it)->getStart().x && standingPos.x <= (*it)->getEnd().x)

                    return (Platform*)*it;

            }

        }

    }

    return NULL;

}*/

int orientation(Point p, Point q, Point r){

        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

        return (val > 0) ? 1 : 2;

}

bool isBetween(Point p, Point q, Point r) {
    if (r.x >= std::min(p.x, q.x) && r.x <= std::max(p.x, q.x) &&
        r.y >= std::min(p.y, q.y) && r.y <= std::max(p.y, q.y))
        return true;
    return false;
}

bool trajectory(Entity entity, Platform *platforms){

    Point p1, p2, p3, p4;
    int o1, o2, o3, o4;

    p1 = platforms->getStart();
    p2 = platforms->getEnd();
    p3 = entity.getPrevPos();
    p4 = entity.getPos();

    o1 = orientation(p1, p2, p3);
    o2 = orientation(p1, p2, p4);
    o3 = orientation(p3, p4, p1);
    o4 = orientation(p3, p4, p2);

    if(o1 != o2 && o3 != o4)
        return true;
    
    if (o1 == 0 && isBetween(p1, p2, p3)) return true;
    if (o2 == 0 && isBetween(p1, p2, p4)) return true;
    if (o3 == 0 && isBetween(p3, p4, p1)) return true;
    if (o4 == 0 && isBetween(p3, p4, p2)) return true;

    return false;

}
