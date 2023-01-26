#pragma once

#include "buttonsField.hpp"
#include "GamesField.hpp"
#include "player.hpp"
#include "Siamon.hpp"
#include "values.hpp"
#include "options.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"


class Game
{
private:
    Player player;
    Siamon gameHost;
    GamesField field;
    bool gameOver = false;
    size_t winLen;
    ButtonsField<PauseMenu,3> pauseMenu;
    Difficulties diff;
    sf::Texture winTexture;
    sf::Sprite win;
    sf::Texture loseTexture;
    sf::Sprite lose;
    sf::Music music;
    sf::Sound winSound;
    sf::SoundBuffer winSoundBuff;
    void SiamonsTurn(sf::RenderWindow& window, sf::Event& event)
    {
        gameHost.updateSequence();
        gameHost.saySequnce(window, field, event);
        gameHost.setTurn(false);
        player.setTurn(true);
    }

    void playersTurn(sf::RenderWindow& window,GamesButton button)
    {
        player.updateSequence(button);
        if(gameHost.correctSequence(player.getCurrentSequenceLen(), player.getSequnce()))
        {
            if(gameHost.getCurrentSequenceLen() == player.getCurrentSequenceLen())
            {
                player.setTurn(false);
                gameHost.setTurn(true);
                window.draw(win);
                window.display();
                player.removeSequnce();
                if (gameHost.getCurrentSequenceLen() == winLen)
                {
                    gameHost.removeSequnce();
                    gameOver = true;
                    winSound.play();
                }
                sf::sleep(sf::seconds(1));
            }
        }    
        else
        {
            player.setTurn(false);
            gameHost.setTurn(true);
            window.draw(lose);
            window.display();
            sf::sleep(sf::seconds(1));
            player.removeSequnce();
            gameHost.removeSequnce();
            gameOver = true;
        }
    }

    void pauseRun(sf::RenderWindow& window, sf::Event& event)
    {
        PauseMenu click = none;
        while(window.isOpen() && click == none)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            pauseMenu.draw(window,event);
            click = pauseMenu.buttonsPress();
            if(click != none)
            {
                if(click == exitGame)
                {
                    window.close();
                    gameOver = true;
                }
                else if(click == mainMenu) 
                    gameOver = true;
                else if(click == Continue)
                {
                    gameOver = false;
                    break;
                }
                
            }
            window.display();
        }
    }
public:    
    Game(Player& _player, Difficulties _diff, GamesField& _field, ButtonsField<PauseMenu,3>& _pauseMenu,std::string winSign = goodSign ,std::string loseSign = badSign, std::string winPlay = winerSound) 
    : player(_player), diff(_diff), field(_field), pauseMenu(_pauseMenu)
    {
        this->gameHost = Siamon(_diff);
        if (_diff == easy)
            this->winLen = easyMaxSequence;
        if (_diff == medium)
            this->winLen = mediumMaxSequence;
        if (_diff == hard)
            this->winLen = hardMaxSequence;
        this->loseTexture.loadFromFile(loseSign);
        this->winTexture.loadFromFile(winSign);
        this->win.setTexture(this->winTexture);
        this->lose.setTexture(this->loseTexture);
        this->winSoundBuff.loadFromFile(winPlay);
        this->winSound.setBuffer(this->winSoundBuff);
        this->gameOver = false;

    }
    void run(sf::RenderWindow& window, sf::Event& event)
    {
        player.setTurn(false);
        gameHost.setTurn(true);
        win.setPosition(window.getSize().x /2 -40, window.getSize().y/2 -40);
        lose.setPosition(window.getSize().x / 2 -40, window.getSize().y / 2 - 40);
        while (window.isOpen() && gameOver==false)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            field.draw(window, event, player.getTurn());
            window.display();
            if (gameHost.getTurn() == true && player.getTurn() == false)
            {
                sf::sleep(sf::seconds(1.f));
                window.setMouseCursorVisible(false);
                SiamonsTurn(window,event);
            }
            else if(gameHost.getTurn() == false && player.getTurn() == true)
            {
                window.setMouseCursorVisible(true);
                GamesButton button = field.buttonsPress();
                if (button != stay && button != pause)
                {
                    playersTurn(window, button);
                    if (gameOver == true)
                        pauseRun(window,event);
                }
                else if(field.buttonsPress()==pause)
                    pauseRun(window,event);
            }
        }
    }
};