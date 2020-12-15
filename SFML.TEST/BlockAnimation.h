#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
class BlockAnimation
{
public:
	BlockAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f(position));
	~BlockAnimation();
	void Updata(float deltaTime, sf::RenderWindow& window);
	float time;
	bool dead = false;
private:
	sf::RectangleShape body;
	Animation animation;
	
	sf::Clock clock;
	
};
