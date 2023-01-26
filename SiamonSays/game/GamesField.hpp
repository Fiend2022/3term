#pragma once

#include "button.hpp"
#include "buttonsField.hpp"
#include "SFML/Graphics.hpp"
#include "options.hpp"
#include <string>
#include <math.h>
#include "values.hpp"

#define PAUSE this->numOfOptions-1






const std::vector<sf::Vector2f> buttonPos = { {396, 90},  {864, 90 }, {396,563},{864,563} };


class GamesField : public ButtonsField<GamesButton, gamesButtonsNumMin>
{
private:
    sf::Texture circleTexture;
    sf::Sprite circle;
public:
    GamesField(const std::string& backgroundPath, const std::string&  selectedButtonsPath, const std::string& notSelectedButtonsPath,
    const std::string& circlePath, const std::string& format, std::string soundFile, std::string _soundFormat = soundFormat)
    {
        this->backgroundTexture.loadFromFile(backgroundPath);
        this->background.setTexture(this->backgroundTexture);
        this->circleTexture.loadFromFile(circlePath);
        this->circle.setTexture(this->circleTexture);

        this->numOfOptions = gamesButtonsNumMin;
        this->numOfOptions++;
        this->circle.setPosition(circlePos);
       
        this->buttons.resize(this->numOfOptions);
        for (int i = 0; i < this->numOfOptions - 1; i++)
        {
            std::string selectedButton = selectedButtonsPath + std::to_string(i+1) + format;
            std::string notSelectedButton = notSelectedButtonsPath + std::to_string(i+1) + format;
            std::string sound = soundGamesButton + std::to_string(i + 1) + _soundFormat;
            this->buttons[i] = new Button<GamesButton>(buttonPos[i],selectedButton,notSelectedButton, static_cast<GamesButton>(i+1), sound);
        }
        this->buttons[PAUSE] = new Button<GamesButton>(pausePos,pausePath,pausePath,pause);
    }
    virtual void draw(sf::RenderWindow& window, sf::Event& event, bool playerActive = true) override
    {
        window.draw(this->background);
        window.draw(this->circle);
        for (int i = 0; i < this->numOfOptions - 1;i++)
            this->buttons[i]->draw(window, event, playerActive);
        this->buttons[PAUSE]->draw(window,event);
    }
    void lightUpTheButton(GamesButton but,sf::RenderWindow& window)
    {
        window.draw(*(this->buttons[but-1]->getSelectedSpritePointer()));

        this->buttons[but-1]->soundPlay();
    }
    void makeASounds()
    {
        for (int i = 0;i < buttons.size()-1;i++)
        {
            if (buttons[i]->pressed() == true)
                buttons[i]->soundPlay();
        }
    }
    void drawWithLightsUpButton(sf::RenderWindow& window, sf::Event& event, GamesButton button)
    {
        this->buttons[button - 1]->soundPlay();
        while (window.isOpen() && this->buttons[button - 1]->getSoundStatus() == sf::Sound::Playing)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            window.draw(this->background);
            window.draw(this->circle);
            for (int i = 0; i < this->numOfOptions - 1;i++)
            {
                if (i != button-1)
                    window.draw(*this->buttons[i]->getNotSelectedSpritePointer());
                else
                    window.draw(*this->buttons[i]->getSelectedSpritePointer());
            }
            this->buttons[PAUSE]->draw(window, event);
            window.display();
        }
    }
};