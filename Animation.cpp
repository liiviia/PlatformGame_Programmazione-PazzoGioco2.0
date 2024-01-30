#include"./Header Files/Animation.h"
#include"./Header Files/Game.h"

Animation::Animation(int animationIndex, Animation::animationType animationType, float startY, float startX, direction direction){

    setAnimationIndex(animationIndex);
    setAnimationType(animationType);
    
    if(animationType == GROUND_ATTACK){
        
        setFrameCount(2);
        setCurFrameIndx(0);
        setAnimationDirection(direction);
        setEliminationFlag(false);
        Frame frame;

        if(!direction){
            frame.framePos.y = startY - 1;
            frame.framePos.x = startX - 1;
            frame.frameChar = "\\";
            frames.push_back(frame);
            
            frame.framePos.y = startY;
            frame.framePos.x = startX - 1;
            frame.frameChar = "/";
            frames.push_back(frame);
        }
        else{
            frame.framePos.y = startY - 1;
            frame.framePos.x = startX + 1;
            frame.frameChar = "/";
            frames.push_back(frame);
            
            frame.framePos.y = startY;
            frame.framePos.x = startX + 1;
            frame.frameChar = "\\";
            frames.push_back(frame);
        }

    }

}

void Animation::nextFrame(){

    if(!frames.empty()){
        frames.pop_front();
        setCurFrameIndx(getCurFrameIndx() + 1);
    }
}

void Animation::addAnimation(Game *game, Animation::animationType animationType, Entity *entity){

    Animation *animation = new Animation(game->getGlobalAnimationCount(), animationType, entity->getPos().y, entity->getPos().x, entity->getDirection());
    
    if(animation != NULL)
        game->getAnimationList()->push_back(animation);

    game->setGlobalAnimationCount(game->getGlobalAnimationCount() + 1);

}

// Getters

int                      Animation::getAnimationIndex(){ return this->animationIndex; }
int                      Animation::getFrameCount(){ return this->frameCount; }
int                      Animation::getCurFrameIndx(){ return this->curFrame; }
Animation::animationType Animation::getAnimationType(){ return this->type; }
direction                Animation::getAnimationDirection(){ return this->animationDir; }
Frame                    Animation::getCurFrame(){ return this->frames.front(); }
bool                     Animation::getEliminationFlag(){ return this->eliminationFlag; }


// Setters

void Animation::setAnimationIndex(int index){ this->animationIndex = index; }
void Animation::setFrameCount(int count){ this->frameCount = count; }
void Animation::setCurFrameIndx(int index){ this->curFrame = index; }
void Animation::setAnimationType(Animation::animationType type){ this->type = type; }
void Animation::setAnimationDirection(direction direction){ this->animationDir = direction; }
void Animation::setEliminationFlag(bool flag){ this->eliminationFlag = flag; }

bool Animation::isFramesEmpty(){ return frames.empty(); }