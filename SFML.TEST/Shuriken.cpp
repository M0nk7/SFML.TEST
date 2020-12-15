#include "Shuriken.h"
#include "Animation.h"
Shuriken::Shuriken(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, float randx,sf::Color color):
animation(texture, imageCount, switchTime)
{

	this->body.setSize(size);
	this->body.setOrigin(size / 2.0f);
	this->body.setTexture(texture);
	this->body.setPosition(sf::Vector2f(randx,-50));
	this->body.setFillColor(color);
	isDestroyBool = false;
}
Shuriken::~Shuriken()
{
}

void Shuriken::Update(float deltaTime)
{
	animation.Update(0, deltaTime,faceRight);
	body.setTextureRect(animation.uvRect);
	//body.move(move* deltaTime);
}

void Shuriken::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
void Shuriken::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left.
		move.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right.
		move.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		move.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		move.y = 0.0f;
	}
}
void Shuriken::Move(sf::Vector2f move_,float deltaTime)
{
	this->move = move_;

	body.move(move* deltaTime);
}
void Shuriken::setDestroy(bool isDestroyBool)
{
	this->isDestroyBool = isDestroyBool;
}
void Shuriken::magicMove(float deltaTime)
{
	body.move(move * deltaTime);
}