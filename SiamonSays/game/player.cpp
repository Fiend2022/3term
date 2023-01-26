#include <iostream>

#include <vector>
#include "SFML/System.hpp"
#include "player.hpp"

void Player::setName(const sf::String playersName)
{
    this->name = playersName;
}

void Player::exit()
{
    this->turn = 0;
    this->sequence.clear();
    this->inGame = false;
}

sf::String* Player::getName()
{
    return &this->name;
}

void Player::changeStatus(bool inMatch, unsigned int _turn)
{
    this->inGame = inMatch;
    this->turn = _turn;
}