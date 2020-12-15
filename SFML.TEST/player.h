#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	void SetPosition(sf::Vector2f Position) { body.setPosition(Position); Box.setPosition(Position.x, Position.y - 10); }
	sf::Vector2f GetSize() { body.getSize(); }
	sf::Vector2f GetPosition() {return	body.getPosition();}
	Collider GetCollider() {return Collider(body);}
	Collider GetColliderBox() { return Collider(Box); }
	float stamina = 0;		
	float maxStamina = 0;
	bool faceRight;
	bool checkS;
	bool checkSlide;
	float drag = 0.97;
	

private:
	sf::RectangleShape body;
	sf::RectangleShape Box;
	Animation animation;
	unsigned int row;
	float speed = 100;
	float speedMaxX = 400;
	
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	float time;
	sf::Clock clock;

	sf::SoundBuffer soundb1;
	sf::Sound sound1;

	sf::SoundBuffer soundb2;
	sf::Sound sound2;

};
