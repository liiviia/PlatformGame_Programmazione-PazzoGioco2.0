#pragma once

#include<string>
#include<list>
#include<set>
using namespace std;

class Entity;
class Player;
class Platform;

struct obstacle{
    int id;
    int map_id;
    int chunk_id;
    float y, x; 
    int length;
    int pairNum;
    char drawSymbol = '=';
    bool isGround;
    obstacle * next;
    obstacle * prev;
};

typedef obstacle * obPointer;

struct Point{

    float y, x;

};

enum direction { LEFT , RIGHT, UP , DOWN};

struct Frame{

    string frameChar;
    Point framePos;

};

float randomFloatInRange(float min, float max);
int approxFloat(float n);
bool isInSet(set<float> recordedPos, float xPos);
bool isInSafeZone(Player player, float xPos);
short int isInPlatformArea(obPointer playerPlatform, obPointer enemyPlatform);
//Platform* getStandingPlatform(Entity entity, list<Platform*> platforms);
int   orientation(Point p, Point q, Point r);
bool  isBetween(Point p, Point q, Point r);
bool  trajectory(Entity entity, Platform *platforms);    // Per collisioni tra entità e piattaforme