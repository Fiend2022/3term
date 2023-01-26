#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>



template <typename Opt>
class Button
{
private:
    sf::Texture selectedTexture;
    sf::Texture notSelectedTexture;
    sf::Sprite selectedSprite;
    sf::Sprite  notSelectedSprite;
    bool press = false;
    bool flag = false;
    bool colision = false;
    sf::Vector2f position;
	sf::Vector2u size;
    Opt option;
    sf::SoundBuffer soundBuff;
    sf::Sound sound;
    bool haveSound = false;
public:
    Button<Opt>(const sf::Vector2f& buttonPos, const std::string& textureSelectedButton, const std::string& textureNotSelectedButton, Opt opt, std::string soundFile = "")
    {
        this->position = buttonPos;
        this->colision = false;
        this->selectedTexture.loadFromFile(textureSelectedButton);
        this->notSelectedTexture.loadFromFile(textureNotSelectedButton);

        this->selectedSprite.setTexture(this->selectedTexture);
        this->notSelectedSprite.setTexture(this->notSelectedTexture);

        this->selectedSprite.setPosition(this->position);
        this->notSelectedSprite.setPosition(this->position);
        this->option = opt;
        this->size = selectedTexture.getSize();
        if (soundFile != "")
        {
            this->soundBuff.loadFromFile(soundFile);
            this->sound.setBuffer(this->soundBuff);
            this->haveSound = true;
        }
    }
    Button<Opt>()=default;

    bool pressed()
    {
        return this->press;
    }

    sf::Sound::Status getSoundStatus()
    {
        return this->sound.getStatus();
    }

    bool check(sf::Vector2i &mousePos)
    {
        if (mousePos.x > this->position.x && mousePos.x < this->position.x + size.x)
        {
            if (mousePos.y > this->position.y && mousePos.y < this->position.y + size.y)
                return true;
            else
                return false;
        }
        else 
            return false;
    }

    void uppdate(sf::Vector2i& mousePos, sf::Event& event)
    {
        this->colision = this->check(mousePos);
        this->press = false;
        if (this->colision)
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && flag == false)
            {
                this->flag = true;
                this->press = false;
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && flag == true)
            {
                this->press = true;
                this->flag = false;
            }
        }
    }

    sf::Sprite* getSpritePointer()
    {
        if (this->colision)
            return &(this->selectedSprite);
        else
            return &(this->notSelectedSprite);
    }

    void draw(sf::RenderWindow &window, sf::Event& event, bool playerActive = true)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        this->uppdate(mousePos,event);
        if (playerActive == true)
            window.draw(*this->getSpritePointer());
        else
            window.draw(this->notSelectedSprite);
        if (this->press && this->haveSound)
            this->sound.play();
    }   

    Opt getOption()
    {
        return this->option;
    }

    sf::Sprite* getSelectedSpritePointer()
    {
        return &(this->selectedSprite);
    }

    sf::Sprite* getNotSelectedSpritePointer()
    {
        return &(this->notSelectedSprite);
    }
    
    void soundPlay()
    {
        this->sound.play();
    }
    sf::Vector2u& getSize()
    {
        return this->size;
    }
};