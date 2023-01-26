#pragma once

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "button.hpp"
#include <strstream>
#include <iostream>
#include "values.hpp"

using namespace std;
template <typename Options, int numOfOpt>
class ButtonsField
{
protected:
    std::vector<Button<Options>*> buttons;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    size_t numOfOptions;
public:
    ButtonsField<Options,numOfOpt>(const std::string& backgroundFile, const std::string& buttonsSelectedPath, const std::string& buttonsNotSelectedPath, 
    const std::string& format, const sf::Vector2f& firstButtPos, size_t _stepY = stepY, std::string buttonsSound = "")
    {
        this->numOfOptions = numOfOpt;
        this->backgroundTexture.loadFromFile(backgroundFile);
        this->background.setTexture(this->backgroundTexture);
        this->buttons.resize(this->numOfOptions);
        sf::Vector2f vec = firstButtPos;
        for( int i =0; i < this->numOfOptions;i++)
        { 
            if(i>0)
                vec.y += _stepY + this->buttons[i-1]->getSize().y;
            std::string selectedButton = buttonsSelectedPath + std::to_string(i+1)  + format;
            std:: string notSelctedButton = buttonsNotSelectedPath + std::to_string(i+1)  + format;
            this->buttons[i] = new Button<Options>(vec, selectedButton, notSelctedButton, static_cast<Options>(i+1), buttonsSound);
        }
    } 
    ButtonsField<Options,numOfOpt>() = default;

    virtual void draw(sf::RenderWindow& window, sf::Event& event, bool playerActive = true)
    {
        window.draw(this->background);
        for (int i = 0; i < this->numOfOptions;i++)
            this->buttons[i]->draw(window,event, playerActive);
    }


    virtual Options buttonsPress()
    {
        for(size_t i =0; i < this->buttons.size();i++)
        {
            bool press =this->buttons[i]->pressed();
            if(press == true)
                return this->buttons[i]->getOption();
        }
        return static_cast<Options>(0);
    }
};