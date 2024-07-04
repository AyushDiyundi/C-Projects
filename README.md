#Pong
A simple Pong game implemented using C++ and Raylib.
Introduction

This project implements the classic Pong game using the Raylib library for graphics and input handling. The game features a player-controlled paddle and a CPU-controlled paddle, bouncing a ball between them. The objective is to score points by getting the ball past the opponent's paddle.
Features

    Player-controlled paddle movement using UP and DOWN arrow keys.
    CPU-controlled paddle automatically tracks the ball's vertical position.
    Score tracking for both player and CPU.
    Basic collision detection between the ball and paddles.
    Simple graphical elements using Raylib.

How to Play

    Controls:
        Player Paddle: Use UP arrow key to move up and DOWN arrow key to move down.
        CPU Paddle: Automatically adjusts its position to track the ball vertically.

    Objective:
        Score points by hitting the ball past the opponent's paddle.
        The game ends when one player reaches a set score limit (not implemented in this version).

    Gameplay:
        The ball will bounce off the top and bottom edges of the screen.
        Scoring:
            When the ball passes the right edge of the screen, the CPU scores.
            When the ball passes the left edge of the screen, the player scores.

How the Computer Plays

The CPU-controlled paddle employs a simple strategy to track the ball's vertical position:

    Update Method:
        In the CpuPaddle::Update(int ball_y) method:
            If the center of the CPU paddle (y + height / 2) is above the ball's y position, it moves up.
            If the center of the CPU paddle is below the ball's y position, it moves down.
        This basic logic allows the CPU to follow the ball vertically, attempting to intercept it.

Dependencies

    Raylib library for graphics and input handling.
