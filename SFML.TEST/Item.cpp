#include "Item.h"
#include "Animation.h"
Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, float randx) :
	animation(texture, imageCount, switchTime)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(sf::Vector2f(randx, 0));
	isDestroyBool = false;
}

Item::~Item()
{
}

void Item::Update(float deltaTime)
{
	move.x = 0;
	move.y = 200;
	animation.Update(0, deltaTime, 1);
	body.setTextureRect(animation.uvRect);
	body.move(move* deltaTime);
}
void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
void Item::setDestroy(bool isDestroyBool)
{
	this->isDestroyBool = isDestroyBool;
}