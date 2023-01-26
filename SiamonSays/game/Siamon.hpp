#pragma once

#include <iostream>
#include <vector>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "options.hpp"
#include "player.hpp"
#include "GamesField.hpp"
#include "values.hpp"
#include <random>
#include <algorithm>

class Siamon : public Player
{
private:
    std::mt19937 gen;
    size_t steps;
public:
    Siamon(Difficulties diff = easy)
    {
        this->steps = diff == hard ? hardStep : diff;
        this->name = "Siamon";
        this->turn =true;
        this->inGame = true;
        this->currentLenOfSequnce = 0;
    }
    virtual void updateSequence()
    {

       for(size_t i =0; i < this->steps; i++)
       {
            std::random_device rd;
            std::mt19937 gen2(rd());
            this->gen = gen2;
            GamesButton button = static_cast<GamesButton>((this->gen()%gamesButtonsNumMin)+1);
            this->sequence.push_back(button);
            this->currentLenOfSequnce++;
       }
    }


    bool correctSequence(size_t currnetSequnceSize, std::vector<GamesButton> currentSequence)
    { 
        for (size_t i = 0;i < currnetSequnceSize; i++)
        {
            if (currentSequence[i] != this->sequence[i])
                return false;
        }
        return true;
    } 
    void saySequnce(sf::RenderWindow& window, GamesField& field, sf::Event& event)
    {
        for (int i = 0; i < this->currentLenOfSequnce; i++)
            field.drawWithLightsUpButton(window, event,this->sequence[i]);
    }
};