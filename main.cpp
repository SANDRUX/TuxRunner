#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>

#define STEP_LENGTH 10
#define WIN_STEP_X 1
#define WIN_STEP_Y 2
#define APPEAR_DISTANCE 500

struct pos
{
    int x,y;
};

int main()
{   
game_start:
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TUX RUNNER");

    window.setFramerateLimit(60);

    pos map_pos {0, 0};
    pos win_pos {1920, 1080};
    pos text_pos {400, 0};
    pos pos {0, 0};

    sf::Event event;

    sf::Texture texture;
    texture.loadFromFile("/home/sandro/tux_runner/tux_runner/tux/penguin.png");

    sf::Texture windwosTexture;
    windwosTexture.loadFromFile("/home/sandro/tux_runner/tux_runner/tux/windows.png");

    sf::Sprite windows;
    windows.setTexture(windwosTexture);

    sf::Texture mapTexture;
    mapTexture.loadFromFile("/home/sandro/tux_runner/tux_runner/tux/map.jpg");

    sf::Sprite map;
    map.setTexture(mapTexture);

    sf::IntRect rectSourceSprite(129, 0, 129, 903);

    sf::Sprite pengo(texture, rectSourceSprite);

    pos.x = sf::VideoMode::getDesktopMode().width / 2;
    pos.y = sf::VideoMode::getDesktopMode().height / 2;

    pengo.setPosition(pos.x, pos.y);

    sf::Clock clock;

    unsigned int points = 0;

    sf::Font font;
    font.loadFromFile("/home/sandro/tux_runner/tux_runner/tux/geopixel.ttf");

    sf::Text text;
    text.setFont(font);
    text.setPosition(text_pos.x, text_pos.y);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);

    std::string score_string;

    text.setString("daaWire enTers TamaSis dasawyebad");

    while (window.isOpen())
    {
        bool status = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                status = true;
                break;
            }
        }

        if (status == true)
        {
            break;
        }

        window.clear(sf::Color::Yellow);
        window.draw(text);
        window.display();
    }

    text.setString("qula - 0");

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {          
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                pos.y -= STEP_LENGTH;
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                pos.y += STEP_LENGTH;
            }                        

            if (event.key.code == sf::Keyboard::Right)
            {
                pos.x += STEP_LENGTH;
            }

            if (event.key.code == sf::Keyboard::Left)
            {
                pos.x -= STEP_LENGTH;
            }

        }

        if (clock.getElapsedTime().asSeconds() > 0.1f)
        {
            if (rectSourceSprite.left == 774)
            {
                rectSourceSprite.left = 0;
            }

            else
            {
                rectSourceSprite.left += 129;
            }

            pengo.setTextureRect(rectSourceSprite);

            clock.restart();
        }

        if (win_pos.x > pos.x)
        {
            win_pos.x -= WIN_STEP_X;
        }

        else if (win_pos.x + 150 < pos.x)
        {
            points ++;
            score_string = "qula - " + std::to_string(points);

            text.setString(score_string);

            win_pos.x = pos.x + APPEAR_DISTANCE + rand() % APPEAR_DISTANCE;
        }

        if (win_pos.y > pos.y)
        {
            win_pos.y -= WIN_STEP_Y;
        }

        else
        {
            win_pos.y += WIN_STEP_Y;
        }

        if (map_pos.x == -1920)
        {
            map_pos.x = 0;
        }

        if (pos.x < win_pos.x + 129 &&
            pos.x + 129 > win_pos.x &&
            pos.y < win_pos.y + 138 &&
            pos.y + 138 > win_pos.y)
        {
            break;
        }

        map_pos.x -= 2;

        window.clear();

        pengo.setPosition(pos.x, pos.y);
        windows.setPosition(win_pos.x, win_pos.y);
        map.setPosition(map_pos.x, map_pos.y);

        window.draw(map);
        window.draw(pengo);
        window.draw(windows);
        window.draw(text);

        window.display();
    }

    text_pos.x = 50;
    text_pos.y = sf::VideoMode::getDesktopMode().height/2;

    text.setCharacterSize(50);
    text.setPosition(text_pos.x, text_pos.y);

    score_string = "TamaSi dasrulda, Tqveni mimdinare qula aris - " + std::to_string(points) + "\nxelaxla dasawyebad daaCireT enTer-s";

    text.setString(score_string);

    while (window.isOpen())
    {        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                goto game_start;
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(text);
        window.display();      
    }

    return 0;
}
