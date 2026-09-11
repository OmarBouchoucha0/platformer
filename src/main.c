#include "raylib.h"

int main(void) {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  ToggleFullscreen();
  screenWidth = GetScreenWidth();
  screenHeight = GetScreenHeight();

  Image tileset = LoadImage("assets/background/corridor/layers/tileset.png");
  Texture2D tilesetTexture = LoadTextureFromImage(tileset);
  UnloadImage(tileset);

  Image back = LoadImage("assets/background/corridor/layers/back.png");
  Texture2D backTexture = LoadTextureFromImage(back);
  UnloadImage(back);

  Image far = LoadImage("assets/background/corridor/layers/far.png");
  Texture2D farTexture = LoadTextureFromImage(far);
  UnloadImage(far);

  Image middle = LoadImage("assets/background/corridor/layers/middle.png");
  Texture2D middleTexture = LoadTextureFromImage(middle);
  UnloadImage(middle);

  Image near = LoadImage("assets/background/corridor/layers/near.png");
  Texture2D nearTexture = LoadTextureFromImage(near);
  UnloadImage(near);

  Image foreground =
      LoadImage("assets/background/corridor/layers/foreground.png");
  Texture2D foregroundTexture = LoadTextureFromImage(foreground);
  UnloadImage(foreground);

  SetTargetFPS(60);

  float globalScale = (float)screenHeight / 224.0f;

  Camera2D camera = {0};
  camera.zoom = 1.0f;

  while (!WindowShouldClose()) {

    if (IsKeyDown(KEY_RIGHT))
      camera.target.x += 5.0f;
    if (IsKeyDown(KEY_LEFT))
      camera.target.x -= 5.0f;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    for (int i = 0; i < 100; i++) {
      float yPos = screenHeight - (backTexture.height * globalScale);
      float xPos =
          (i * (backTexture.width * globalScale)) + (camera.target.x * 0.9f);
      DrawTextureEx(backTexture, (Vector2){xPos, yPos}, 0.0f, globalScale,
                    WHITE);
    }

    for (int i = 0; i < 100; i++) {
      float yPos = screenHeight - (farTexture.height * globalScale);
      float xPos =
          (i * (farTexture.width * globalScale)) + (camera.target.x * 0.8f);
      DrawTextureEx(farTexture, (Vector2){xPos, yPos}, 0.0f, globalScale,
                    WHITE);
    }

    for (int i = 0; i < 100; i++) {
      float yPos = screenHeight - (middleTexture.height * globalScale);
      float xPos =
          (i * (middleTexture.width * globalScale)) + (camera.target.x * 0.7f);
      DrawTextureEx(middleTexture, (Vector2){xPos, yPos}, 0.0f, globalScale,
                    WHITE);
    }

    for (int i = 0; i < 100; i++) {
      float yPos = screenHeight - (nearTexture.height * globalScale);
      float xPos =
          (i * (nearTexture.width * globalScale)) + (camera.target.x * 0.4f);
      DrawTextureEx(nearTexture, (Vector2){xPos, yPos}, 0.0f, globalScale,
                    WHITE);
    }

    for (int i = 0; i < 100; i++) {
      float tilesetY = (224 - 42) * globalScale;
      float xPos =
          (i * (tilesetTexture.width * globalScale)) + (camera.target.x * 0.2f);

      DrawTextureEx(tilesetTexture, (Vector2){xPos, tilesetY}, 0.0f,
                    globalScale, WHITE);
    }

    for (int i = 0; i < 100; i++) {
      float yPos = screenHeight - (foregroundTexture.height * globalScale);
      float xPos = (i * (foregroundTexture.width * globalScale));
      DrawTextureEx(foregroundTexture, (Vector2){xPos, yPos}, 0.0f, globalScale,
                    WHITE);
    }
    EndMode2D();
    EndDrawing();
  }
  UnloadTexture(tilesetTexture);
  UnloadTexture(farTexture);
  UnloadTexture(backTexture);
  UnloadTexture(middleTexture);
  UnloadTexture(nearTexture);
  UnloadTexture(foregroundTexture);
  CloseWindow();

  return 0;
}
