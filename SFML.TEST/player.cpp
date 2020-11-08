
#include "Player.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	this->body.setSize(sf::Vector2f(70.0f, 160.0f));
	this->body.setOrigin(body.getSize() / 2.0f);
	this->body.setPosition(960.0f, 500.0f);
	this->body.setTexture(texture);
	
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	
	row = 0;
	if (stamina <= 0)
	{
		speedMaxX = 400;
	}
	else
	{
		speedMaxX = 400;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			velocity.x -= speed;
			stamina -= 1;
			speedMaxX = 650;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			velocity.x += speed;
			stamina -= 1;
			speedMaxX = 650;
		}
	}
	if (stamina < maxStamina && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)&& canJump == true)
	{
		stamina += 0.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
		row = 1;
		faceRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
		row = 1;
		faceRight = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& canJump)
	{
		canJump = false;
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
		
	}
	velocity.y += 1500.0f * deltaTime;
	if (canJump == false)
	{
		if (velocity.x == 0.0f)
		{
			row = 2;
		}
		else
		{
			row = 2;
			if (velocity.x > 0.0f)
				faceRight = true;
			else
				faceRight = false;
		}
	}
	
	if (abs(velocity.x) > speedMaxX)
	{
		if (velocity.x < 0)
		{
			velocity.x = -1 * speedMaxX;
		}
		else
		{
			velocity.x = speedMaxX;
		}
	}

	velocity.x *= drag;
	

	if (abs(velocity.x) < 20)
	{
		velocity.x = 0;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x< 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if(direction.x >0.0f)
	{
		//Collision on the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}

