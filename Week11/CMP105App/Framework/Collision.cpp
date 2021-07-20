#include "Collision.h"
#include<iostream>

// Check AABB for collision. Returns true if collision occurs.
bool Collision::checkBoundingBox(GameObject* s1, GameObject* s2)
{
	if (s1->getPosition().x ==100 && s1->getPosition().y<96)
	{
	
		std::cout << "End" << std::endl;
		int a = 3;
	}
	sf::FloatRect colBox = s1->getCollisionBox();
	sf::FloatRect colBox2=s2->getCollisionBox();

	//std::cout << "UNO:" << s1->getCollisionBox().left << " " << s1->getCollisionBox().width << " " << s2->getCollisionBox().left << std::endl;
	if (s1->getCollisionBox().left + s1->getCollisionBox().width < s2->getCollisionBox().left)
		return false;
	//std::cout << "DOS:" << s1->getCollisionBox().left << " " << s2->getCollisionBox().left << " " << s2->getCollisionBox().width << std::endl;
	if (s1->getCollisionBox().left > s2->getCollisionBox().left + s2->getCollisionBox().width)
		return false;
	//std::cout << "TRE:" << s1->getCollisionBox().top << " " << s1->getCollisionBox().height << " " << s2->getCollisionBox().top << std::endl;
	if (s1->getCollisionBox().top + s1->getCollisionBox().height < s2->getCollisionBox().top)
		return false;
		
	//std::cout << "QUA:" << s1->getCollisionBox().top << " " << s2->getCollisionBox().top << " " << s2->getCollisionBox().height << std::endl;
	if (s1->getCollisionBox().top > s2->getCollisionBox().top + s2->getCollisionBox().height)
		return false;

	//std::cout << "SUCCESS" << std::endl;
	return true;
}

// Check for bounding box collision with a point/vector2 rather than two boxes.
bool Collision::checkBoundingBox(GameObject* s1, sf::Vector2i s2)
{
	if (s1->getCollisionBox().left + s1->getCollisionBox().width < s2.x)
		return false;
	if (s1->getCollisionBox().left > s2.x)
		return false;
	if (s1->getCollisionBox().top + s1->getCollisionBox().height < s2.y)
		return false;
	if (s1->getCollisionBox().top > s2.y)
		return false;

	return true;
}

// Check bounding circle collision. Returns true if collision occurs.
bool Collision::checkBoundingCircle(GameObject* s1, GameObject* s2)
{
	// Get radius and centre of sprites.
	float radius1 = s1->getSize().x / 2;
	float radius2 = s2->getSize().x / 2;
	float xpos1 = s1->getPosition().x + radius1;
	float xpos2 = s2->getPosition().x + radius2;
	float ypos1 = s1->getPosition().y + radius1;
	float ypos2 = s2->getPosition().y + radius2;

	if (pow(xpos2 - xpos1, 2) + pow(ypos2 - ypos1, 2) < pow(radius1 + radius2, 2))
	{
		return true;
	}
	return false;
}

