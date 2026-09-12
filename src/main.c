#include "raylib.h"

typedef struct {
  int frameCount;
  int frame;
  float frameTimer;
  float frameDuration;
} animation_state;

typedef struct {
  animation_state torchAnimation;
  animation_state mcIdleAnimation;
  animation_state mcWalkAnimation;
} animations;

typedef enum { LEFT, RIGHT } player_direction;
typedef enum { IDLE, WALK } player_condition;

typedef struct {
  Vector2 position;
  player_direction direction;
  player_condition condition;
} player_State;

void input(player_State *player, Camera2D *camera, float dt) {
  player->condition = WALK;
  if (IsKeyDown(KEY_RIGHT)) {
    camera->target.x += 5.0f;
    player->position.x += 5.0f;
    player->direction = RIGHT;
  } else if (IsKeyDown(KEY_LEFT)) {
    camera->target.x -= 5.0f;
    player->position.x -= 5.0f;
    player->direction = LEFT;
  } else {
    player->condition = IDLE;
  }
}

void ai();
void physics();

void updateTorchAnimation(float dt, animations *ani) {
  ani->torchAnimation.frameTimer += dt;
  if (ani->torchAnimation.frameTimer >= ani->torchAnimation.frameDuration) {
    ani->torchAnimation.frame =
        (ani->torchAnimation.frame + 1) % ani->torchAnimation.frameCount;
    ani->torchAnimation.frameTimer -= ani->torchAnimation.frameDuration;
  }
}

void updateMcIdleAnimation(float dt, animations *ani) {
  ani->mcIdleAnimation.frameTimer += dt;
  if (ani->mcIdleAnimation.frameTimer >= ani->mcIdleAnimation.frameDuration) {
    ani->mcIdleAnimation.frame =
        (ani->mcIdleAnimation.frame + 1) % ani->mcIdleAnimation.frameCount;
    ani->mcIdleAnimation.frameTimer -= ani->mcIdleAnimation.frameDuration;
  }
}

void updateMcWalkAnimation(float dt, animations *ani) {
  ani->mcWalkAnimation.frameTimer += dt;
  if (ani->mcWalkAnimation.frameTimer >= ani->mcWalkAnimation.frameDuration) {
    ani->mcWalkAnimation.frame =
        (ani->mcWalkAnimation.frame + 1) % ani->mcWalkAnimation.frameCount;
    ani->mcWalkAnimation.frameTimer -= ani->mcWalkAnimation.frameDuration;
  }
}

void animation(player_State player, float dt, animations *ani) {
  updateTorchAnimation(dt, ani);
  switch (player.condition) {
  case IDLE:
    updateMcIdleAnimation(dt, ani);
  case WALK:
    updateMcWalkAnimation(dt, ani);
  }
}

void drawTorch(Texture2D torchTexture, float x, float y, float globalScale,
               animations *ani) {
  float frameWidth = (float)torchTexture.width / ani->torchAnimation.frameCount;
  float frameHeight = (float)torchTexture.height;

  Rectangle frameRec = {(float)ani->torchAnimation.frame * frameWidth, 0.0f,
                        frameWidth, frameHeight};

  Rectangle destRec = {x, y, frameWidth * globalScale,
                       frameHeight * globalScale};

  DrawTexturePro(torchTexture, frameRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
}

void drawMc(Texture2D mcIdleTexture, Texture2D mcWalkTexture,
            player_State player, float globalScale, animations *ani) {
  if (player.condition == IDLE) {
    float frameWidth =
        (float)mcIdleTexture.width / ani->mcIdleAnimation.frameCount;
    float frameHeight = (float)mcIdleTexture.height;

    Rectangle frameRec = {(float)ani->mcIdleAnimation.frame * frameWidth, 0.0f,
                          frameWidth, frameHeight};

    Rectangle destRec = {player.position.x, player.position.y,
                         frameWidth * globalScale, frameHeight * globalScale};
    if (player.direction == LEFT) {
      frameRec.width = -frameRec.width;
    }
    DrawTexturePro(mcIdleTexture, frameRec, destRec, (Vector2){0, 0}, 0.0f,
                   WHITE);
  }

  if (player.condition == WALK) {
    float frameWidth =
        (float)mcWalkTexture.width / ani->mcWalkAnimation.frameCount;
    float frameHeight = (float)mcWalkTexture.height;

    Rectangle frameRec = {(float)ani->mcWalkAnimation.frame * frameWidth, 0.0f,
                          frameWidth, frameHeight};

    Rectangle destRec = {player.position.x, player.position.y,
                         frameWidth * globalScale, frameHeight * globalScale};
    if (player.direction == LEFT) {
      frameRec.width = -frameRec.width;
    }
    DrawTexturePro(mcWalkTexture, frameRec, destRec, (Vector2){0, 0}, 0.0f,
                   WHITE);
  }
}

void render(player_State player, int screenHeight, int screenWidth,
            Camera2D camera, Texture2D backTexture, Texture2D farTexture,
            Texture2D middleTexture, Texture2D nearTexture,
            Texture2D torchTexture, Texture2D tilesetTexture,
            Texture2D foregroundTexture, Texture2D mcIdleTexture,
            Texture2D mcWalkTexture, float globalScale, float dt,
            animations *ani) {
  ClearBackground(WHITE);
  BeginMode2D(camera);

  for (int i = 0; i < 100; i++) {
    float yPos = screenHeight - (backTexture.height * globalScale);
    float xPos =
        (i * (backTexture.width * globalScale)) + (camera.target.x * 0.9f);
    DrawTextureEx(backTexture, (Vector2){xPos, yPos}, 0.0f, globalScale, WHITE);
  }

  for (int i = 0; i < 100; i++) {
    float yPos = screenHeight - (farTexture.height * globalScale);
    float xPos =
        (i * (farTexture.width * globalScale)) + (camera.target.x * 0.8f);
    DrawTextureEx(farTexture, (Vector2){xPos, yPos}, 0.0f, globalScale, WHITE);
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
    DrawTextureEx(nearTexture, (Vector2){xPos, yPos}, 0.0f, globalScale, WHITE);
    drawTorch(torchTexture, xPos + (127 * globalScale),
              yPos + (95 * globalScale), globalScale, ani);
  }

  for (int i = 0; i < 100; i++) {
    float tilesetY = (224 - 42) * globalScale;
    float xPos =
        (i * (tilesetTexture.width * globalScale)) + (camera.target.x * 0.2f);

    DrawTextureEx(tilesetTexture, (Vector2){xPos, tilesetY}, 0.0f, globalScale,
                  WHITE);
  }
  drawMc(mcIdleTexture, mcWalkTexture, player, globalScale, ani);

  for (int i = 0; i < 100; i++) {
    float yPos = screenHeight - (foregroundTexture.height * globalScale);
    float xPos = (i * (foregroundTexture.width * globalScale));
    DrawTextureEx(foregroundTexture, (Vector2){xPos, yPos}, 0.0f, globalScale,
                  WHITE);
  }
  EndMode2D();
  EndDrawing();
}

int main(void) {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Platformer");
  ToggleFullscreen();
  screenWidth = GetScreenWidth();
  screenHeight = GetScreenHeight();

  Texture2D torchTexture =
      LoadTexture("assets/background/corridor/torch/torch-sheet.png");

  Texture2D tilesetTexture =
      LoadTexture("assets/background/corridor/layers/tileset.png");

  Texture2D backTexture =
      LoadTexture("assets/background/corridor/layers/back.png");

  Texture2D farTexture =
      LoadTexture("assets/background/corridor/layers/far.png");

  Texture2D middleTexture =
      LoadTexture("assets/background/corridor/layers/middle.png");

  Texture2D nearTexture =
      LoadTexture("assets/background/corridor/layers/near.png");

  Texture2D foregroundTexture =
      LoadTexture("assets/background/corridor/layers/foreground.png");

  Texture2D mcIdleTexture =
      LoadTexture("assets/character/spriteSheet/idle.png");
  Texture2D mcWalkTexture =
      LoadTexture("assets/character/spriteSheet/walk.png");

  animations ani = {};
  ani.torchAnimation.frameDuration = 0.25f;
  ani.torchAnimation.frameCount = 4;
  ani.mcIdleAnimation.frameDuration = 0.20f;
  ani.mcIdleAnimation.frameCount = 6;
  ani.mcWalkAnimation.frameDuration = 0.10f;
  ani.mcWalkAnimation.frameCount = 8;

  player_State player = {};
  player.position.x = 50.0f;
  player.position.y = 224 + 128 + 42;

  SetTargetFPS(60);

  float globalScale = (float)screenHeight / 224.0f;

  Camera2D camera = {0};
  camera.zoom = 1.0f;
  short fps = 0;
  char InfoBuffer[1024];
  float dt = 0.0f;

  while (!WindowShouldClose()) {
    fps = GetFPS();
    dt = GetFrameTime();
    globalScale = (float)screenHeight / 224.0f;
    input(&player, &camera, dt);
    animation(player, dt, &ani);
    render(player, screenHeight, screenWidth, camera, backTexture, farTexture,
           middleTexture, nearTexture, torchTexture, tilesetTexture,
           foregroundTexture, mcIdleTexture, mcWalkTexture, globalScale, dt,
           &ani);
  }
  CloseWindow();

  return 0;
}
