#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, float randx);
	~Item();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setDestroy(bool isDestroyBool);
	void GetGlobalBouns() { body.getGlobalBounds(); }
	bool isDestroy() { return isDestroyBool; }
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation animation;
	sf::Vector2f move;
	bool isDestroyBool;
};

