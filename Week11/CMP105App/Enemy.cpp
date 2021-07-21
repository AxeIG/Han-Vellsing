#include "Enemy.h"

Enemy::Enemy() {

	health = 100;
	detection_radius = 0;

}

Enemy::~Enemy() {


}





void Enemy::setDetectionRadius(float detection_radius) {

	this->detection_radius = detection_radius;
}

float Enemy::getDetectionRadius() {

	return detection_radius;
}
