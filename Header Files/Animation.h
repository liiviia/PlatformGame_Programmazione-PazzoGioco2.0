#pragma once

#include"util.h"
#include <list>
using namespace std;

class Game;

class Animation{

    public:

        enum animationType { GROUND_ATTACK };

        Animation(int animationIndex, animationType animationType, float startY, float startX, direction direction);

        void nextFrame();

        static void addAnimation(Game *game, Animation::animationType animationType, Entity *entity);

        // Getters

        int getAnimationIndex();
        int getFrameCount();
        Frame getCurFrame();
        int getCurFrameIndx();
        animationType getAnimationType();
        direction getAnimationDirection();
        bool getEliminationFlag();

        // Setters

        void setAnimationIndex(int index);
        void setFrameCount(int count);
        void setCurFrameIndx(int index);
        void setAnimationType(animationType type);
        void setAnimationDirection(direction direction);
        void setEliminationFlag(bool flag);

        bool isFramesEmpty();

    private:

        int frameCount;
        int curFrame;
        list<Frame> frames;
        animationType type;
        direction animationDir;
        int animationIndex;
        bool eliminationFlag;

};