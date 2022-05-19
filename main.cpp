#include "raylib.h"
#include "raymath.h"

struct AnimationData
{
    // used to select sprite from spritesheet
    Rectangle sprite;
    // track current frame of animation
    int frame;
    int maxFame;
    // Frame rate(1 frame per xth of a second, eg x fps)
    float updateTime;
    // track when to update to next frame
    float runningTime;
};

// Function to check and update which frame we're on
AnimationData updateAnimationFrame(AnimationData data, float deltaTime)
{
    // add deltaTime to time since last update
    data.runningTime += deltaTime;
    // if more time has passed than the fps of the animation
    if (data.runningTime >= data.updateTime)
    {
        // reset RunningTime
        data.runningTime = 0.0;

        // if we're at the last frame
        if (data.frame >= data.maxFame)
        {
            // go back to the first frame
            data.frame = 0;
        }
        else
        {
            // go to the next game
            data.frame++;
        }
    }
    // return the updated AnimationData
    return data;
}
AnimationData updateSelectedSprite(AnimationData data)
{
    data.sprite.x = data.frame * data.sprite.width;
    return data;
};


int main()
{
    int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");

    Texture2D playerIdle = LoadTexture("Textures/characters/knight_idle_spritesheet.png");
    Texture2D playerMove = LoadTexture("Textures/characters/knight_run_spritesheet.png");
    Texture2D playerSheet{playerIdle};
    float playerSpriteScale{4};   

    //animation variables
    float runningtime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1/12};
    // 1= right, -1 = left. Used for flipping sprite
    float rightleft{1.f};

    Vector2 playerPosition{
        (windowDimensions[0]/2) - (playerSpriteScale * playerIdle.width/maxFrame),
        (windowDimensions[1]/2) - (playerSpriteScale * playerIdle.height)
    };
    float playerSpeed{0.1}; 

    AnimationData playerAnimation{{(float)playerSheet.width/maxFrame, (float)playerSheet.height}, frame, maxFrame, updateTime, runningtime};

    Vector2 mapPosition{0.0, 0.0};



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        //check for directional inputs and apply force
        if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT)) direction.x -= 1;
        if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT)) direction.x += 1;
        if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP)) direction.y -= 1;
        if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN)) direction.y += 1;

        //if directional input found, set the new map position
        if (Vector2Length(direction) != 0.0)
        {
            mapPosition = Vector2Subtract(mapPosition, Vector2Scale(
                Vector2Normalize(direction), //normalized direction so diagonal movement isnt faster than cardinal
                playerSpeed)); //scale by player speed, to control rate of movement
            
            // if direction is less than zero, player must be moving right
            direction.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
            playerSheet = playerMove;
        }
        else playerSheet = playerIdle;
        

        //Draw the map
        DrawTextureEx(map, mapPosition, 0, 4, WHITE);
        //Draw the player
        Rectangle source{(float)(playerSheet.width/6)*frame, 0.f, rightleft * (float)(playerSheet.width/6), (float)playerSheet.height};
        Rectangle dest{playerPosition.x, playerPosition.y, playerSpriteScale * playerSheet.width/6, playerSpriteScale* playerSheet.height};
        
        playerAnimation =  updateSelectedSprite(playerAnimation);
        playerAnimation = updateAnimationFrame(playerAnimation, GetFrameTime());
        
        DrawTexturePro(playerSheet, source, dest, Vector2{}, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(map);

    return 1;
}