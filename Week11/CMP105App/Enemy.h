#pragma once
#include"Character.h"
class Enemy:
	public Character
{
public:
	Enemy();
	~Enemy();

	
	void setDetectionRadius(float detection_radius);
	float getDetectionRadius();

protected:

	float detection_radius;

};

