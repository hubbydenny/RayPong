#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include "../RayPongClean/Headers/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../RayPongClean/Headers/raygui.h"

bool fps60 = false;
bool ismenuopen = false;
bool dropdownEditMode = false;
bool colorDropdownEditMode = false;
bool gameover = false;
bool onscreen = true;
bool pause = false;
float volume = 0.5f;

class Ball {
public:
    float x = 400;
    float y = 225;
    int radius = 10;
    int speedX = 4;
    int speedY = 3;

    void Update() {
        x += speedX;
        y += speedY;
        if (y <= radius || y >= GetScreenHeight() - radius) {
            speedY *= -1;
        }
    }

    void Reset() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speedX = (GetRandomValue(0, 1) == 0 ? -1 : 1) * GetRandomValue(3, 12);
        speedY = (GetRandomValue(0, 1) == 0 ? -1 : 1) * GetRandomValue(3, 12);
    }
};

class Player1 {
public:
    float x = 10;
    float y = 200;
    int Width = 10;
    int Height = 80;
    int speedY = 5;

    void Update() {
        if (IsKeyDown(KEY_W)) y -= speedY;
        if (IsKeyDown(KEY_S)) y += speedY;
        if (y < 0) y = 0;
        if (y > GetScreenHeight() - Height) y = GetScreenHeight() - Height;
    }
};

class Player2 {
public:
    float y = 200;
    int Width = 10;
    int Height = 80;
    int speedY = 5;

    void Update() {
        if (IsKeyDown(KEY_UP)) y -= speedY;
        if (IsKeyDown(KEY_DOWN)) y += speedY;
        if (y < 0) y = 0;
        if (y > GetScreenHeight() - Height) y = GetScreenHeight() - Height;
    }
    void Clear() {
        onscreen = false;
    }
};

static float clampf(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

bool CircleRectCollisionNew(float cx, float cy, float r, float rx, float ry, float rw, float rh) {
    float ClosestX = clampf(cx, rx, rx + rw);
    float ClosestY = clampf(cy, ry, ry + rh);
    float dx = cx - ClosestX;
    float dy = cy - ClosestY;
    return (dx * dx + dy * dy) <= r * r;
}

int main() {
    int screenWidth = 800;
    int screenHeight = 450;

    Ball ball;
    Player1 player1;
    Player2 player2;
    int score1 = 0;
    int score2 = 0;
    bool fullscreen = false;
    bool boo = false;
    int difficulty = 0;
    bool showfps = false;
    int color = 0;

    Rectangle fullscreenRect = { 180, 130, 20, 20 };
    Rectangle booRect = { 180, 155, 20, 20 };
    Rectangle difficultyRect = { 180, 215, 200, 25 };
    Rectangle saveButtonRect = { 100, 340, 100, 30 };
    Rectangle backButtonRect = { 100, 390, 100, 30 };
    Rectangle fpsRect = { 180, 180, 20, 20 };
    Rectangle colorRect = { 570, 215, 200, 25 };

    InitWindow(screenWidth, screenHeight, "RayPong");
	InitAudioDevice();
	Music music = LoadMusicStream("Audio/Music.mp3");
	SetMusicVolume(music, volume);
    SetTargetFPS(60);
    fps60 = true;
    ::SetExitKey(0);
    Texture2D meme = LoadTexture("Textures/Meme.png");

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) ismenuopen = !ismenuopen;

        int sw = GetScreenWidth();
        int sh = GetScreenHeight();

        BeginDrawing();
        {
            if (ismenuopen) {
                ClearBackground(RAYWHITE);
                DrawText("Settings", 300, 50, 24, DARKGRAY);

                DrawText("Volume:", 100, 107, 16, DARKGRAY);
                DrawText("Fullscreen:", 93, 130, 15, DARKGRAY);
                GuiCheckBox(fullscreenRect, NULL, &fullscreen);

                DrawText("Noname", 100, 155, 16, DARKGRAY);
                GuiCheckBox(booRect, NULL, &boo);

                DrawText("Fps", 100, 180, 16, DARKGRAY);
                GuiCheckBox(fpsRect, NULL, &showfps);

                DrawText("Difficulty:", 100, 215, 16, DARKGRAY);
                if (GuiDropdownBox(difficultyRect, "Easy;Medium;Hard", &difficulty, dropdownEditMode)) {
                    dropdownEditMode = !dropdownEditMode;
                }
                DrawText("Background:", 470, 215, 16, DARKGRAY);
                if (GuiDropdownBox(colorRect, "Pink-Red;Green;Purple;Blue", &color, colorDropdownEditMode)) {
                    colorDropdownEditMode = !colorDropdownEditMode;
                }

                if (GuiButton(saveButtonRect, "Save")) {
                    if (fullscreen && !IsWindowFullscreen()) ToggleFullscreen();
                    if (!fullscreen && IsWindowFullscreen()) ToggleFullscreen();

                    if (difficulty == 0) ::SetTargetFPS(60);
                    else if (difficulty == 1) ::SetTargetFPS(120);
                    else if (difficulty == 2) ::SetTargetFPS(240);
                }

                if (GuiButton(backButtonRect, "Back")) {
                    ismenuopen = false;
                }
            }
            else {
                if (!IsMusicStreamPlaying(music)) PlayMusicStream(music);
                UpdateMusicStream(music);
                ball.Update();
                player1.Update();
                player2.Update();

                float player2x = (float)(sw - player2.Width - 10);

                if (CircleRectCollisionNew(ball.x, ball.y, (float)ball.radius, player1.x, player1.y, (float)player1.Width, (float)player1.Height)) {
                    ball.speedX *= +1;
                }
                if (CircleRectCollisionNew(ball.x, ball.y, (float)ball.radius, player2x, player2.y, (float)player2.Width, (float)player2.Height)) {
                    ball.speedX *= +1;

                }

                if (ball.x <= 0) {
                    score2++;
                    ball.Reset();
                }
                if (ball.x >= sw) {
                    score1++;
                    ball.Reset();
                }

                if (score1 == 5) {
                    ball.Reset();
                    gameover = true;
                }
                else if (score2 == 5) {
                    ball.Reset();
                    gameover = true;
                }

                if (color == 0) ClearBackground({ 247, 64, 86 });
                else if (color == 1) ClearBackground({ 0, 158, 96 });
                else if (color == 2) ClearBackground({ 200, 180, 230 });
				else if (color == 3) ClearBackground({0, 127, 255 });
            
                ::DrawRectangle(0, sh / 2 - 40, 5, 80, RED);
                ::DrawRectangle(sw - 5, sh / 2 - 40, 5, 80, RED);

                DrawText(TextFormat("%i", score1), sw / 4 - 10, 20, 40, BLACK);
                DrawText(TextFormat("%i", score2), sw * 3 / 4 - 10, 20, 40, BLACK);

                ::DrawLine((int)(sw / 2), 0.0f, (int)(sw / 2), (int)sh, BLACK);

                DrawCircle((float)ball.x, (float)ball.y, ball.radius, WHITE);
                DrawRectangle((float)player1.x, (float)player1.y, player1.Width, player1.Height, WHITE);
                DrawRectangle((float)player2x, (float)player2.y, player2.Width, player2.Height, WHITE);

                if (showfps) {
                    DrawFPS(10, 10);
                }

                if (gameover) {
                    DrawRectangle(0, 0, sw, sh, { 0, 0, 0, 200 });

                    float scale = std::fmin(sw * 0.6f / meme.width, sh * 0.5f / meme.height);
                    float scaledW = meme.width * scale;
                    float scaledH = meme.height * scale;
                    float memeX = sw / 2.0f - scaledW / 2.0f;
                    float memeY = sh / 2.0f - scaledH / 2.0f + 30;
                    Vector2 textSize = MeasureTextEx(GetFontDefault(), "Game over!", 60, 0);

                    DrawTexturePro(meme, Rectangle{0, 0, (float)meme.width, (float)meme.height},
                        Rectangle{memeX, memeY, scaledW, scaledH}, Vector2{0, 0}, 0, WHITE);
                    DrawText("Game over!", (int)(sw / 2 - textSize.x / 2), (int)(memeY - 80), 60, WHITE);

                    DrawText("Press ENTER to Restart", sw / 2 - 110, sh - 50, 20, LIGHTGRAY);
                    if (IsKeyPressed(KEY_ENTER)) {
                        score1 = 0;
                        score2 = 0;
                        gameover = false;
                        ball.Reset();
                    }
                }
            }

            EndDrawing();
        }
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    UnloadTexture(meme);
	UnloadMusicStream(music);
    return 0;
}
