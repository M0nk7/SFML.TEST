#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void SetPosition(sf::Vector2f Position) { body.setPosition(Position); }
	sf::Vector2f GetSize() { body.getSize(); }
	sf::Vector2f GetPosition() {return	body.getPosition();}
	Collider GetCollider() { return Collider(body); }
	float stamina = 0;		
	float maxStamina = 30;
	bool faceRight;
	float drag = 0.97;
	

private:
	sf::RectangleShape body;
	sf::RectangleShape bodyImmortal;
	Animation animation;
	unsigned int row;
	float speed = 100;
	float speedMaxX = 400;
	
	
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

};
