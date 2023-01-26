#pragma once

#include <iostream>
#include <vector>
#include "SFML/System.hpp"
#include "options.hpp"

class Player
{
protected:
    std::vector<GamesButton> sequence;
    size_t currentLenOfSequnce =0 ;
    sf::String name = "You";
    bool inGame = true;
    bool turn = false;
public:

    Player() = default;
    ~Player()
    {
        this->turn = 0;
        this->name.clear();
        this->sequence.clear();
        this-> inGame = false;
    }
    virtual void updateSequence(GamesButton numOfButton)
    {
        this->sequence.push_back(numOfButton);
        this->currentLenOfSequnce++;

    }
    void setName(const sf::String playersName);
    sf::String* getName();
    void changeStatus(bool inMatch, unsigned int _turn);
    void exit();
    size_t getCurrentSequenceLen()
    {
        return this->currentLenOfSequnce;
    }
    const std::vector<GamesButton>& getSequnce()
    {
        return this->sequence;
    }
    virtual void setTurn(bool _turn)
    {
        this->turn = _turn;
    }
    bool getTurn()
    {
        return this->turn;
    }
    void removeSequnce()
    {
        this->sequence.clear();
        this->currentLenOfSequnce = 0;
    }
};