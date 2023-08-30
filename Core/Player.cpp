#include "pch.h"
#include "Player.h"
#include "systemHandle.h"

Player::Player()
{
	initTexture("NONE");
}

Player::~Player()
{
	if (this->texture)
		delete this->texture;
}

void Player::update()
{

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(shape);

}

void Player::Move(float x, float y)
{
	shape.move(x, y);
}

void Player::initTexture(const std::string filePath)
{
	this->shape.setSize(sf::Vector2f(32.f, 96.f));
	this->shape.setOrigin(this->shape.getSize() / 2.f);
	this->shape.setPosition(systemHandle::getView()->getCenter());
}
