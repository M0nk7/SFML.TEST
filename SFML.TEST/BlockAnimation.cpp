#include "BlockAnimation.h"

BlockAnimation::BlockAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size,sf::Vector2f(position)) :
	animation(texture, imageCount, switchTime)
{
	this->body.setSize(size);
	this->body.setOrigin(size / 2.0f);
	this->body.setTexture(texture);
	this->body.setPosition(position);
}

BlockAnimation::~BlockAnimation()
{
	
}

void BlockAnimation::Updata(float deltaTime, sf::RenderWindow& window)
{
	time = clock.getElapsedTime().asMilliseconds();
	if(time < 500)
	{
		if (time > 50) 
		{
			window.draw(body);
		}
		
		animation.Update(0, deltaTime, 1);
		body.setTextureRect(animation.uvRect);
	}
	else
	{
		dead = true;
	}
	printf("%.f\n", time);
}
