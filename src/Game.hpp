#pragma once

#include <array>

#include "Entity/Entity.hpp"
#include "Entity/Paddle.hpp"
#include "Entity/Ball.hpp"

enum class PaddleState
{
    LeftPaddleUp,
    RightPaddleUp,
    LeftPaddleDown,
    RightPaddleDown,
    None,
};

class Game
{
public:
    Game();
    void Run();

public:
    static constexpr int WindowHeight = 720;
    static constexpr int WindowWidth = 1280;

private:
    void DrawEntities();
    void HandleInput();
    void UpdatePosition();
    void DetectPaddleWindowCollision(Paddle& paddle);
    void DetectBallWindowCollision();
    void DetectBallPaddleCollision();
    void PushBall();
    void MoveBall();

private:
    Paddle m_pLeft;
    Paddle m_pRight;
    Ball m_ball;

    sf::RenderWindow* m_window = nullptr;
    std::array<Entity*, 3> m_entities = { &m_pLeft, &m_pRight, &m_ball };
    PaddleState m_paddleState;
    
    sf::Time m_deltaTime = sf::Time::Zero;
};