#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
class Shuriken
{
public:
	Shuriken(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size , float randx);
	~Shuriken();

	void OnCollision(sf::Vector2f direction);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setDestroy(bool isDestroy);
	void Move(sf::Vector2f move_, float deltaTime);
	bool isDestroy() { return isDestroyBool; }

	sf::Vector2f GetPosition() { return	body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	
	

private:
	sf::RectangleShape body;
	Animation animation;
	bool faceRight;
	bool isDestroyBool;
	sf::Vector2f move;
	sf::Clock timeClock;
};

