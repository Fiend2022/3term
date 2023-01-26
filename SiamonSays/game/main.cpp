#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "buttonsField.hpp"
#include "button.hpp"
#include <string>
#include "GamesField.hpp"
#include "game.hpp"


#include "options.hpp"
#include "values.hpp"



int main()
{

    sf::Vector2f buttonsStart = start;
    ButtonsField <MainMenuOptions,3> mainMenu(background, selectedButtonsMainMenuPath, notSelectedButtonsMainMenuPath, photoFormat, buttonsStart, stepY);
    ButtonsField <Difficulties, 3> choosingDifficults(difficultsBackground,difficultsSelectedButtonsPath,difficultsNotSelectedButtonsPath,photoFormat,buttonsStart,stepY);
    sf::RenderWindow window(sf::VideoMode(width, height), "Siamon Says");
    GamesField field(gamesBackground, gamesSelectedButtonsPath, gamesNotSelectedButtonsPath, circlePath, photoFormat, soundGamesButton);
    ButtonsField<PauseMenu,3> pauseMenu(pauseBackground,pauseSelectedButtonsPath, pauseNotSelectedButtonsPath,photoFormat, pausesButtonsStart);
    Player player;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        mainMenu.draw(window, event);
        MainMenuOptions click = mainMenu.buttonsPress();
        if(click == Exit)
           window.close();
        else if(click == singleplayer)
        {
            while(window.isOpen())
            {   
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    window.close();
                }
                window.clear();
                choosingDifficults.draw(window,event);
                Difficulties diff = choosingDifficults.buttonsPress();
                if(diff!=noActive)
                {
                    Player player;
                    Game game(player, diff, field, pauseMenu);
                    game.run(window,event);
                    break;
                    window.display();
                }
                window.display();
            }
        }
        window.display();
    }
    return 0;
}