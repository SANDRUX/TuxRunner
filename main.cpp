#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>

#define STEP_LENGTH 10

float WIN_STEP_X = 0.5;
float WIN_STEP_Y = 0.5;
int APPEAR_DISTANCE = 200;

struct pos
{
    float x,y;
};

int main()
{
game_start:
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TUX RUNNER");

    window.setFramerateLimit(60);

    pos map_pos {0, 0};
    pos win_pos {0, 0};
    pos text_pos {400, 0};
    pos pos {0, 0};

    sf::Event event;

    sf::Texture texture;
    texture.loadFromFile("tux/penguin.png");

    sf::Texture windwosTexture;
    windwosTexture.loadFromFile("tux/windows.png");

    sf::Sprite windows;
    windows.setTexture(windwosTexture);

    sf::Texture mapTexture;
    mapTexture.loadFromFile("tux/map.jpg");

    sf::Sprite map;
    map.setTexture(mapTexture);


    float scale = float(sf::VideoMode::getDesktopMode().width) / float(mapTexture.getSize().x / 2.f); // get screen to texture size factor
    
    map.setScale({scale, scale}); // set background scale correctly

    sf::Texture startBackground;
    startBackground.loadFromFile("tux/tux.png");

    sf::Sprite startBackgroundSprite;
    startBackgroundSprite.setTexture(startBackground);

    startBackgroundSprite.setPosition(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2);

    sf::Texture gameOver;
    gameOver.loadFromFile("tux/game_over.png");

    sf::Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOver);

    sf::IntRect rectSourceSprite(129, 0, 129, 903);

    sf::Sprite pengo(texture, rectSourceSprite);

    pos.x = sf::VideoMode::getDesktopMode().width / 2;
    pos.y = sf::VideoMode::getDesktopMode().height / 2;

    win_pos.x = sf::VideoMode::getDesktopMode().width;
    win_pos.y = sf::VideoMode::getDesktopMode().height;

    pengo.setPosition(pos.x, pos.y);

    sf::Clock clock;

    unsigned int points = 0;
    unsigned int last_points = 0;

    sf::Font font;
    font.loadFromFile("tux/geopixel.ttf");

    sf::Text text;
    text.setFont(font);
    text.setPosition(text_pos.x, text_pos.y);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);

    sf::Music soundTrack;
    soundTrack.openFromFile("tux/beeh.wav");

    sf::Music gameOverSound;
    gameOverSound.openFromFile("tux/game_over.wav");

    sf::Music awardSound;
    awardSound.openFromFile("tux/award.wav");

    sf::Music startSound;
    startSound.openFromFile("tux/start.wav");

    std::string score_string;

    startSound.play();
    startSound.setLoop(true);

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

        if (status)
        {
            break;
        }

        window.clear(sf::Color::Cyan);
        window.draw(startBackgroundSprite);
        window.draw(text);
        window.display();
    }

    startSound.stop();

    soundTrack.play();
    soundTrack.setVolume(50);
    soundTrack.setLoop(true);

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
            awardSound.stop();
            awardSound.play();

            points ++;
            score_string = "qula - " + std::to_string(points);

            text.setString(score_string);

            win_pos.x = pos.x + APPEAR_DISTANCE + rand() % APPEAR_DISTANCE;
            win_pos.y = pos.y + APPEAR_DISTANCE + rand() % APPEAR_DISTANCE;
        }

        if (win_pos.y > pos.y)
        {
            win_pos.y -= WIN_STEP_Y;
        }

        else
        {
            win_pos.y += WIN_STEP_Y;
        }
        
        
        // map_pos.x < -(float(mapTexture.getSize().x * scale) / 2.f) // this is another way involving more math

        if (map_pos.x < -(map.getGlobalBounds().width / 2.f))
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

        if (!(points % 5))
        {
            if (last_points != points)
            {
                APPEAR_DISTANCE -= 50;
                WIN_STEP_Y += 0.5;
                WIN_STEP_X += 0.1;
            }
        }

        last_points = points;

        map_pos.x -= 20;

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

    sf::sleep(sf::seconds(1));

    soundTrack.stop();

    text.setCharacterSize(50);
    text.setPosition(200, 0);

    gameOverSprite.setPosition(200, 200);

    gameOverSound.play();

    score_string = "TamaSi dasrulda, Tqveni mimdinare qula aris - " + std::to_string(points) + "\ngasagrZeleblad daaWireT enTer-s";

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
        window.draw(gameOverSprite);
        window.display();      
    }

    return 0;
}
