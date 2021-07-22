#pragma once
#include "Enemy.h"
//#include "FireBall.h"
class Imp :
    public Enemy
{
public:
enum class ImpStates{IDLE, ATTACK, TORNADO_ATTACK,TORNADO_RETURN, DEAD};

    Imp();
    ~Imp();

    ImpStates state= ImpStates::IDLE;
    void update(float dt) override;
    void handleAnimation() override;
    void initialiseAnimations() override;
    void updateState() override;
    void checkPlayer(GameObject player);
    bool shouldSpawnFireball();
    void collisionResponse(GameObject* gameobject) override;

private:

    bool can_attack, can_tornado;
    Animation idle, attack, tornado_attack, tornado_return; 

};

