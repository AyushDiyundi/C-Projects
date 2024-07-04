#include <raylib.h>
#include <iostream>

// Define colors
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

// Game variables
int player_score = 0;
int cpu_score = 0;

// Class representing the ball
class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    // Draw the ball
    void Draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    // Update ball position and check boundaries
    void Update() {
        x += speed_x;
        y += speed_y;

        // Reflect from top and bottom boundaries
        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }

        // CPU scores if ball crosses right boundary
        if (x + radius >= GetScreenWidth()) {
            cpu_score++;
            ResetBall();
        }

        // Player scores if ball crosses left boundary
        if (x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }

    // Reset ball position and randomize speed
    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        // Randomize direction of ball
        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

// Class representing the player's paddle
class Paddle {
protected:
    // Limit paddle movement within screen boundaries
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    // Draw the paddle
    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    // Update paddle movement based on player input
    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }
        LimitMovement();
    }
};

// Class representing the CPU paddle (inherits from Paddle)
class CpuPaddle : public Paddle {
public:
    // Update CPU paddle movement based on ball position
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y -= speed;
        }
        if (y + height / 2 < ball_y) {
            y += speed;
        }
        LimitMovement();
    }
};

// Initialize game objects
Ball ball;
Paddle player;
CpuPaddle cpu;

int main() {
    std::cout << "Starting the game" << std::endl;

    // Initialize window and game settings
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(60);

    // Initialize ball properties
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    // Initialize player paddle properties
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    // Initialize CPU paddle properties
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Update game objects
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Check for collisions between ball and paddles
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        // Draw everything
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    // Clean up and close window
    CloseWindow();
    return 0;
}
