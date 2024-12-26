#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"

using std::uint64_t;

Game::Game()
    : m_pLeft(Game::WindowWidth / 20, 0.30 * Game::WindowHeight),
    m_pRight(Game::WindowWidth / 20, 0.30 * Game::WindowHeight),
    m_ball(30),
    m_paddleState(PaddleState::None)
{
    m_pLeft.GetShape().setPosition(sf::Vector2f(50, Game::WindowHeight / 2 - 50));
    m_pRight.GetShape().setPosition(Game::WindowWidth - 115, Game::WindowHeight / 2 - 50);
    m_ball.GetShape().setPosition(Game::WindowWidth / 2, Game::WindowHeight / 2);
}

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode(Game::WindowWidth, Game::WindowHeight), "PongClone"); 
    m_window = &window;

    uint64_t framesPassed = 0;
    
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    while (window.isOpen())
    {
        framesPassed++;
        
        if (framesPassed == 1)
        {
            PushBall();
        }

        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break; // never reaches this
                case sf::Event::MouseButtonPressed:
                    std::cout << "Frames passed till now: " << framesPassed << "\n";
                    PushBall();
                    break;
            }
        }

        window.clear(sf::Color(102, 51, 153, 1));
        
        HandleInput();
        UpdatePosition();
        DrawEntities();

        m_deltaTime = clock.restart();

        window.display();
    }
}

void Game::DrawEntities()
{
    for (auto& entity : m_entities)
    {
        m_window->draw(entity->GetShape());
    }
}

void Game::HandleInput()
{
    using Kb = sf::Keyboard;

    if (Kb::isKeyPressed(Kb::Scan::W))
    {
        m_paddleState = PaddleState::LeftPaddleUp;
    }
    else if (Kb::isKeyPressed(Kb::Scan::Up))
    {
        m_paddleState = PaddleState::RightPaddleUp;
    } 
    else if (Kb::isKeyPressed(Kb::Scan::S))
    {
        m_paddleState = PaddleState::LeftPaddleDown;
    }
    else if (Kb::isKeyPressed(Kb::Scan::Down))
    {
        m_paddleState = PaddleState::RightPaddleDown;
    }
}

void Game::UpdatePosition()
{
    switch (m_paddleState)
    {
        case PaddleState::LeftPaddleUp:
            m_pLeft.GetShape().move(sf::Vector2f(0.0f, -350.0f * m_deltaTime.asSeconds()));
            DetectWindowCollision(m_pLeft);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::RightPaddleUp:
            m_pRight.GetShape().move(sf::Vector2f(0.0f, -350.0f * m_deltaTime.asSeconds()));
            DetectWindowCollision(m_pRight);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::LeftPaddleDown:
            m_pLeft.GetShape().move(sf::Vector2f(0.0f, 350.0f * m_deltaTime.asSeconds()));
            DetectWindowCollision(m_pLeft);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::RightPaddleDown:
            m_pRight.GetShape().move(sf::Vector2f(0.0f, 350.0f * m_deltaTime.asSeconds()));
            DetectWindowCollision(m_pRight);
            m_paddleState = PaddleState::None;
            break;
    }
}

void Game::DetectWindowCollision(Entity& entity)
{
    auto& shape = entity.GetShape();
    sf::FloatRect bb = shape.getGlobalBounds();
    
    if (bb.left < 0)
    {
        auto oldPos = shape.getPosition();
        shape.setPosition(sf::Vector2f(0, oldPos.y));
    }
    else if (bb.top < 0)
    {
        auto oldPos = shape.getPosition();
        shape.setPosition(sf::Vector2f(oldPos.x, 0));
    }
    else if ((bb.left + bb.getSize().x) > Game::WindowWidth)
    {
        auto oldPos = shape.getPosition();
        shape.setPosition(sf::Vector2f(Game::WindowWidth - bb.getSize().x, oldPos.y));
    }
    else if ((bb.top + bb.getSize().y) > Game::WindowHeight)
    {
        auto oldPos = shape.getPosition();
        shape.setPosition(sf::Vector2f(oldPos.x, Game::WindowHeight - bb.getSize().y));
    }
}

void Game::PushBall()
{
    float rotation = m_ball.GetShape().getRotation();
    std::cout << "Rotation of the ball: " << rotation << "\n";
}
