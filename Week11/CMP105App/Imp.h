#pragma once
#include "Enemy.h"
//#include "FireBall.h"
class Imp :
    public Enemy
{
public:
enum class ImpStates{IDLE, ATTACK, TORNADO_ATTACK, DEAD};

    Imp();
    ~Imp();

    ImpStates state= ImpStates::IDLE;
    void update(float dt) override;
    void handleAnimation() override;
    void initialiseAnimations() override;

    void checkPlayer(GameObject player);

    void collisionResponse(GameObject* gameobject) override;

private:

    Animation idle, attack, tornado_attack; 

};

