#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"

Game::Game()
    : m_pLeft(Game::WindowWidth / 20, 0.30 * Game::WindowHeight),
    m_pRight(Game::WindowWidth / 20, 0.30 * Game::WindowHeight),
    m_ball(30),
    m_paddleState(PaddleState::None)
{
    m_pLeft.GetShape().setPosition(sf::Vector2f(50, Game::WindowHeight / 2 - 50));
    m_pRight.GetShape().setPosition(Game::WindowWidth - 135, Game::WindowHeight / 2 - 50);
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

static void ChangePosByInt(sf::Shape& shape, float x, float y, sf::Time& deltaTime)
{
    sf::Vector2f oldPos = shape.getPosition();
    shape.setPosition(oldPos.x + x * static_cast<float>(deltaTime.asMilliseconds()), oldPos.y + y * static_cast<float>(deltaTime.asMilliseconds()));
}

void Game::UpdatePosition()
{
    switch (m_paddleState)
    {
        case PaddleState::LeftPaddleUp:
            ChangePosByInt(m_pLeft.GetShape(), 0, -0.8f, m_deltaTime);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::RightPaddleUp:
            ChangePosByInt(m_pRight.GetShape(), 0, -0.8f, m_deltaTime);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::LeftPaddleDown:
            ChangePosByInt(m_pLeft.GetShape(), 0, 1.0f, m_deltaTime);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::RightPaddleDown:
            ChangePosByInt(m_pRight.GetShape(), 0, 1.0f, m_deltaTime);
            m_paddleState = PaddleState::None;
            break;
    }
}
