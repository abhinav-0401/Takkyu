#include <cstdint>
#include <ctime>
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
        MoveBall();

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
            DetectPaddleWindowCollision(m_pLeft);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::RightPaddleUp:
            m_pRight.GetShape().move(sf::Vector2f(0.0f, -350.0f * m_deltaTime.asSeconds()));
            DetectPaddleWindowCollision(m_pRight);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::LeftPaddleDown:
            m_pLeft.GetShape().move(sf::Vector2f(0.0f, 350.0f * m_deltaTime.asSeconds()));
            DetectPaddleWindowCollision(m_pLeft);
            m_paddleState = PaddleState::None;
            break;
        case PaddleState::RightPaddleDown:
            m_pRight.GetShape().move(sf::Vector2f(0.0f, 350.0f * m_deltaTime.asSeconds()));
            DetectPaddleWindowCollision(m_pRight);
            m_paddleState = PaddleState::None;
            break;
    }
}

void Game::DetectPaddleWindowCollision(Paddle& paddle)
{
    auto& shape = paddle.GetShape();
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
    
    if ((bb.left + bb.getSize().x) > Game::WindowWidth)
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

void Game::DetectBallWindowCollision()
{
    auto& shape = m_ball.GetShape();
    sf::FloatRect bb = shape.getGlobalBounds();
    auto velocity = m_ball.GetVelocity();
    bool collisionOccurred = false;

    if (bb.left <= 0)
    {
        shape.setPosition(0, bb.top);
        velocity.x = std::abs(velocity.x);
        std::cout << velocity.x << " " << velocity.y << "\n";
        collisionOccurred = true;
    }
    else if ((bb.left + bb.width) >= Game::WindowWidth)
    {
        shape.setPosition(Game::WindowWidth - bb.width, bb.top);
        velocity.x = -std::abs(velocity.x);
        collisionOccurred = true;
    }
    
    if (bb.top <= 0)
    {
        shape.setPosition(bb.left, 0);
        velocity.y = std::abs(velocity.y);
        collisionOccurred = true;
    }
    else if ((bb.top + bb.height) >= Game::WindowHeight)
    {
        shape.setPosition(bb.left, Game::WindowHeight - bb.height);
        velocity.y = -std::abs(velocity.y);
        collisionOccurred = true;
    }

    if (collisionOccurred)
    {
        m_ball.SetVelocity(velocity);
    }
}

void Game::DetectBallPaddleCollision()
{
    auto& ballShape = m_ball.GetShape();
    auto& leftPaddleShape = m_pLeft.GetShape();
    auto& rightPaddleShape = m_pRight.GetShape();

    sf::FloatRect ballBB = ballShape.getGlobalBounds();
    sf::FloatRect leftPaddleBB = leftPaddleShape.getGlobalBounds();
    sf::FloatRect rightPaddleBB = rightPaddleShape.getGlobalBounds();

    if (ballBB.intersects(leftPaddleBB))
    {
        ballShape.setPosition(leftPaddleBB.left + leftPaddleBB.width, ballBB.top);
        m_ball.SetVelocity(-m_ball.GetVelocity().x, m_ball.GetVelocity().y);
    }
    else if (ballBB.intersects(rightPaddleBB))
    {
        ballShape.setPosition(Game::WindowWidth - 115 - (30 * 2), ballBB.top);
        m_ball.SetVelocity(-m_ball.GetVelocity().x, m_ball.GetVelocity().y);
    }
}

void Game::PushBall()
{
    auto vel = m_ball.GetVelocity();
    if (vel.x == 0 && vel.y == 0)
    {
        m_ball.SetVelocity(sf::Vector2f(m_ball.GetInitVelocity(), m_ball.GetInitVelocity()));
    }
}

void Game::MoveBall()
{
    auto& shape = m_ball.GetShape();
    shape.move(m_ball.GetVelocity() * m_deltaTime.asSeconds() * 200.0f);
    DetectBallWindowCollision();
    DetectBallPaddleCollision();
}

