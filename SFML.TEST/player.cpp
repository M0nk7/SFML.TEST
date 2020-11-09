
#include "Player.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	this->body.setSize(sf::Vector2f(70.0f, 160.0f));
	this->body.setOrigin(body.getSize() / 2.0f);
	this->body.setPosition(960.0f, 510.0f);
	this->body.setTexture(texture);
	
	this->Box.setSize(sf::Vector2f(70.0f, 80.0f));
	this->Box.setOrigin(Box.getSize() / 2.0f);
	this->Box.setPosition(960.0f, 500.0f);
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	speedMaxX = 400;
	time = clock.getElapsedTime().asMilliseconds();
	printf("   %.f\n", time);
	checkS = true;
	row = 0;
	
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && canJump == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		row = 3;
		checkS = false;
		faceRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& time > 800 && checkSlide)
	{
		checkS = false;
		checkSlide = false;
		faceRight = false;
		velocity.x -= speedMaxX;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && time > 800 && checkSlide)
	{
		checkS = false;
		checkSlide = false;
		faceRight = true;
		velocity.x += speedMaxX;
	}
	
	
	velocity.y += 1500.0f * deltaTime;
	if (canJump == false)
	{
	
		row = 2;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (checkSlide == false)
	{
		row = 4;
		if (stamina < 10)
		{
			if (velocity.x > 0.0f)
			{
				faceRight = true;
				speedMaxX = 1100;
				velocity.x += speedMaxX;

			}

			else
			{
				faceRight = false;
				speedMaxX = 1100;
				velocity.x -= speedMaxX;
			}
			stamina++;
		}
		else
		{
			clock.restart();
			stamina = 0;
			checkSlide = true;
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
	Box.move(velocity * deltaTime);
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


