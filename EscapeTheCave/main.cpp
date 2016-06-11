/*
 Kha H Nguyen
 This project was created by me when I first learned C/C++
 Copy Right Reserved!!!
 This was created in April 2015
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include "ResourcePath.hpp"
sf::Sprite sprite;
sf::Texture myPic;
sf::Texture kirbyRight;
sf::Texture kirbyUp;
sf::Texture kirbyDown;
sf::Texture background;
sf::Texture potion;
sf::Texture poison;
sf::Texture obstacle;
sf::Texture light;
sf::Sprite potionSprite[6];
sf::Sprite poisonSprite[6];
sf::Sprite obstacleSprite[15];
sf::RectangleShape rectangle(sf::Vector2f(750, 400));
sf::Text text;
int const ITEMS = 6;
int const POISON = 6;
int const OBSTACLES = 15;
int const APPLET_SIZE = 750;
int const CHARACTER_SIZE = 50;
double const MOVEMENT = 3.5;
int score = 20000;
double  lightDy = 0.5;
bool preScreenBool = true;
int maxScore = 0;
//declare
void moveKeyboard(); //keyboard
void setUpBackGround();
void collision();
void scoreLabel();



int main()
{
    //preScreen: This is the introduction for the game.
    if (preScreenBool)
    {
        sf::RenderWindow preScreen(sf::VideoMode(600, 600), "Kha Nguyen- Escape the Cave");
        sf::Font font;
        if (!font.loadFromFile(resourcePath() + "sansation.ttf")) return -1;
        sf::Text text;
        text.setFont(font);
        text.setString("     \t      KHA H NGUYEN \n  \n\tPress\"D\" for Description\nPress \"Y\" to start the game");
        text.setStyle(sf::Text::Bold);
        text.setCharacterSize(30);
        text.setColor(sf::Color::Blue);
        while (preScreen.isOpen())
        {
            sf::Event event;
            while (preScreen.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    preScreen.close();
                    return -1; //exit the game
                }
            }
            
            preScreen.clear();
            preScreen.draw(text);
            preScreen.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            {
                preScreen.close();
                preScreenBool = false;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                
                text.setCharacterSize(24);
                
                text.setColor(sf::Color::Green);
                text.setString("First you have 20000 points,\nit will automatically decreases.\nAs  long as you get 0 point\n you will love the game.\nTry to eat potions \nand be careful with poisons.\n\nPress Y to start the game");
            }
        }
    }
    //set picture/background/character
    //potion
    if (!potion.loadFromFile(resourcePath() + "Potion.png")) return 1;
    if (!poison.loadFromFile(resourcePath() + "Poison.png")) return 1;
    if (!obstacle.loadFromFile(resourcePath() + "Obstacle.png")) return 1;
    if (!myPic.loadFromFile(resourcePath() +  "Kirby.png")) return 1; //load the pikachu picture.
    sprite.setScale(0.07f, 0.07f); //each picture have different scale
    if (!kirbyRight.loadFromFile(resourcePath() + "KirbyRight.png")) return 1; //load the pikachu picture.
    if (!kirbyUp.loadFromFile(resourcePath() + "KirbyUp.png")) return 1; //load the pikachu picture.
    if (!kirbyDown.loadFromFile(resourcePath() + "KirbyDown.png")) return 1; //load the pikachu picture.
    if (!background.loadFromFile(resourcePath() + "Background.png", sf::IntRect(0, 0, APPLET_SIZE, APPLET_SIZE))) return 1; //load the pikachu picture.
    
    //light
    
    if (!light.loadFromFile(resourcePath() + "Light.jpg")) return 1;
    sf::Sprite lightSprite;
    lightSprite.setTexture(light);
    lightSprite.setScale(1.7, 1.7);
    rectangle.setPosition(0, 200);
    rectangle.setFillColor(sf::Color::Black);
    
    //write the score labels
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        return 1;
    }
    text.setFont(font);
    text.setString("Score: 0");
    text.setColor(sf::Color::Red);
    
    
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(2.0, 2.0);
    srand(95); //i choose this one because it will make the obstacles look nice and clear.
    
    setUpBackGround();
    
    // absolute scale factor
    //sprite.scale(sf::Vector2f(1.5f, 3.f));
    sf::RenderWindow window(sf::VideoMode(APPLET_SIZE, APPLET_SIZE), "KHA NGUYEN");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(backgroundSprite);
        for (int i = 0; i < OBSTACLES; i++)
        {
            window.draw(obstacleSprite[i]);
        }
        for (int i = 0; i < ITEMS; i++)
        {
            window.draw(potionSprite[i]);
            window.draw(poisonSprite[i]);
        }
        window.draw(text);
        window.draw(sprite);
        window.draw(rectangle);
        window.display();
        score--;
        
        sprite.setTexture(myPic); //change back to the default pic
        moveKeyboard(); //move the keyboard
        
        collision();
        scoreLabel();
        
        rectangle.move(0, lightDy);
        if (rectangle.getPosition().y + 300 >= APPLET_SIZE || rectangle.getPosition().y < 0)
        {
            lightDy = -lightDy;
        }
        
        //end the game
        if (score < 0)
        {
            window.close();
            sf::RenderWindow window(sf::VideoMode(300, 300), "GAME OVER!");
            sf::Font gameOver;
            if (!gameOver.loadFromFile(resourcePath() + "sansation.ttf")) return 1;
            
            sf::Text lastText;
            lastText.setFont(gameOver);
            std::string newLabel("GAME OVER \n MAX SCORE: ");
            newLabel = newLabel + std::to_string(maxScore);
            lastText.setString(newLabel);
            
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                
                window.clear();
                window.draw(lastText);
                window.display();
                
            }
            
            return 0;
        }
    }
    
    return 0;
}
void setUpBackGround()
{
    for (int i = 0; i < OBSTACLES; i++)
    {
        obstacleSprite[i].setTexture(obstacle);
        obstacleSprite[i].setScale(0.17f, 0.17f);
        obstacleSprite[i].setPosition((rand() % 765), (rand() % 675));
    }
    
    //add potion
    
    for (int k = 0; k < POISON; k++)
    {
        poisonSprite[k].setTexture(poison);
        poisonSprite[k].setScale(0.07f, 0.07f);
        poisonSprite[k].setPosition((rand() % 765), (rand() % 675));
        for (int i = 0; i < OBSTACLES; i++)
        {
            while (poisonSprite[k].getGlobalBounds().intersects(obstacleSprite[i].getGlobalBounds()))
            {
                poisonSprite[k].setPosition((rand() % 765), (rand() % 675));
            }
        }
    }
    
    for (int j = 0; j < ITEMS; j++) //check for collision of those 3 items
    {
        potionSprite[j].setTexture(potion);
        potionSprite[j].setScale(0.04f, 0.04f);
        potionSprite[j].setPosition((rand() % 765), (rand() % 675));
        for (int i = 0; i < OBSTACLES; i++)
        {
            for (int k = 0; k < POISON; k++)
            {
                while (potionSprite[j].getGlobalBounds().intersects(obstacleSprite[i].getGlobalBounds()) ||
                       potionSprite[j].getGlobalBounds().intersects(poisonSprite[k].getGlobalBounds()))
                {
                    potionSprite[j].setPosition((rand() % 765), (rand() % 675));
                }
            }
        }
    }
}
void collision()
{
    //when character eat the items
    for (int i = 0; i < ITEMS; i++)
    {
        if (sprite.getGlobalBounds().intersects(potionSprite[i].getGlobalBounds()))
        {
            score+= 4000;
            scoreLabel();
            //set new position for the items
            potionSprite[i].setPosition((rand() % (APPLET_SIZE - CHARACTER_SIZE)), (rand() % (APPLET_SIZE - CHARACTER_SIZE)));
            for (int j = 0; j < OBSTACLES; j++) //check for collision with obstacles
            {
                while (potionSprite[i].getGlobalBounds().intersects(obstacleSprite[j].getGlobalBounds()))
                {
                    potionSprite[i].setPosition((rand() % (APPLET_SIZE - CHARACTER_SIZE)), (rand() % (APPLET_SIZE - CHARACTER_SIZE)));
                }
            }
        }
        
        //if character eats poision
        for (int i = 0; i < POISON; i++)
        {
            if (sprite.getGlobalBounds().intersects(poisonSprite[i].getGlobalBounds()))
            {
                score -= 7000;
                scoreLabel();
                //set new position for the items
                poisonSprite[i].setPosition((rand() % (APPLET_SIZE - CHARACTER_SIZE)), (rand() % (APPLET_SIZE - CHARACTER_SIZE)));
                for (int j = 0; j < OBSTACLES; j++) //check for collision with obstacles
                {
                    while (poisonSprite[i].getGlobalBounds().intersects(obstacleSprite[j].getGlobalBounds()))
                    {
                        poisonSprite[i].setPosition((rand() % (APPLET_SIZE - CHARACTER_SIZE)), (rand() % (APPLET_SIZE - CHARACTER_SIZE)));
                        
                    }
                }
            }
        }
    }
}

void scoreLabel()
{
    std::string newLabel("Score: ");
    newLabel = newLabel + std::to_string(score);
    text.setString(newLabel); //set new labels
    
    if (maxScore < score)
    {
        maxScore = score;
    }
}

void moveKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (sprite.getPosition().x < (APPLET_SIZE - CHARACTER_SIZE)) //50 is the width of the character
        {
            sprite.setTexture(kirbyRight);
            // left key is pressed: move our character
            sprite.move(MOVEMENT, 0);
            for (int i = 0; i < OBSTACLES; i++)
            {
                if (sprite.getGlobalBounds().intersects(obstacleSprite[i].getGlobalBounds()))
                {
                    sprite.move(-MOVEMENT, 0);
                }
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (sprite.getPosition().x > 0)
        {
            // left key is pressed: move our character
            sprite.move(-MOVEMENT, 0);
            
            for (int i = 0; i < OBSTACLES; i++)
            {
                if (sprite.getGlobalBounds().intersects(obstacleSprite[i].getGlobalBounds()))
                {
                    sprite.move(MOVEMENT, 0);
                }
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (sprite.getPosition().y > 0)
        {
            sprite.setTexture(kirbyUp);
            // left key is pressed: move our character
            sprite.move(0, -MOVEMENT);
            
            for (int i = 0; i < OBSTACLES; i++)
            {
                if (sprite.getGlobalBounds().intersects(obstacleSprite[i].getGlobalBounds()))
                {
                    sprite.move(0, MOVEMENT);
                }
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (sprite.getPosition().y < (APPLET_SIZE - CHARACTER_SIZE)) //APPLET_HEIGHT - 50 (character height)
        {
            sprite.setTexture(kirbyDown);
            // left key is pressed: move or character
            sprite.move(0, MOVEMENT);
            for (int i = 0; i < OBSTACLES; i++)
            {
                if (sprite.getGlobalBounds().intersects(obstacleSprite[i].getGlobalBounds()))
                {
                    sprite.move(0, -MOVEMENT);
                }
            }
            
        }
    }
}