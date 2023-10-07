#include "raylib.h"

#define PADDLE_WIDTH            10
#define PADDLE_HEIGHT           100
#define BALL_SIZE               10

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static const int screenWidth = 800;
static const int screenHeight = 450;

static Rectangle p1, p2, ball;
static Vector2 ball_speed;
static Rectangle field_top, field_bot, field_left, field_right;
static int p1_score, p2_score;

static void GameReset(void) {
    p1.width = PADDLE_WIDTH;
    p1.height = PADDLE_HEIGHT;
    p1.x = 10.0f;
    p1.y = screenHeight/2.0f - p1.height/2.0f;

    p2.width = PADDLE_WIDTH;
    p2.height = PADDLE_HEIGHT;
    p2.x = screenWidth - 10.0f - p2.width;
    p2.y = screenHeight/2.0f - p2.height/2.0f;

    ball.width = BALL_SIZE;
    ball.height = BALL_SIZE;
    ball.x = screenWidth/2.0f - ball.width/2.0f;
    ball.y = screenHeight/2.0f - ball.height/2.0f;
    ball_speed.x = -2.0f;
    ball_speed.y = -2.0f;

    field_top.width = screenWidth;
    field_top.height = 1.0f;
    field_top.x = 0.0f;
    field_top.y = -field_top.height;

    field_bot.width = screenWidth;
    field_bot.height = 1.0f;
    field_bot.x = 0.0f;
    field_bot.y = screenHeight;

    field_left.width = 1.0f;
    field_left.height = screenHeight;
    field_left.x = -field_left.width;
    field_left.y = 0.0f;

    field_right.width = 1.0f;
    field_right.height = screenHeight;
    field_right.x = screenWidth;
    field_right.y = 0.0f;
}

static void InitGame(void) {
    GameReset();
    p1_score = 0;
    p2_score = 0;
}

static void UpdateGame(void) {
    if (IsKeyDown(KEY_S)) p1.y += 3.0f;
    else if (IsKeyDown(KEY_W)) p1.y -= 3.0f;

    if (IsKeyDown(KEY_DOWN)) p2.y += 3.0f;
    else if (IsKeyDown(KEY_UP)) p2.y -= 3.0f;

    ball.x += ball_speed.x;
    ball.y += ball_speed.y;

    if (CheckCollisionRecs(ball, p1) ||
        CheckCollisionRecs(ball, p2)) {
        ball_speed.x *= -1.0f;
    }
    if (CheckCollisionRecs(ball, field_top) ||
        CheckCollisionRecs(ball, field_bot)) {
        ball_speed.y *= -1.0f;
    }
    if (CheckCollisionRecs(ball, field_left)) {
        p2_score++;
        GameReset();
    }
    if (CheckCollisionRecs(ball, field_right)) {
        p1_score++;
        GameReset();
    }
}

static void DrawGame(void) {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawRectangleRec(p1, RED);
    DrawRectangleRec(p2, BLUE);
    DrawRectangleRec(ball, RAYWHITE);
    
    DrawText(TextFormat("%i", p1_score), screenWidth/2.0f - 20.0f, 10, 10, RAYWHITE);
    DrawText(TextFormat("%i", p2_score), screenWidth/2.0f + 50.0f, 10, 10, RAYWHITE);

    EndDrawing();
}

static void UnloadGame(void) {
}

static void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "this is NOT pong");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        UpdateDrawFrame();
    }
#endif

    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

