#include "raylib.h"
#include <iostream>
#include <iterator>
#include <cstddef>

struct AnimationData
{
    // used to select sprite from spritesheet
    Rectangle sprite;
    // position on screen
    Vector2 position;
    // track current frame of animation
    int frame;
    int maxFame;
    // Frame rate(1 frame per xth of a second, eg x fps)
    float updateTime;
    // track when to update to next frame
    float runningTime;
};

struct BackgroundLayer
{
    Texture2D texture; // Texture for layer
    Vector2 position;  // Position for screen scroll
    int velocity;      // Speed for screen scroll
    float scale;       // Scale for texture
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

// Function to update which sprite we need for an animation
AnimationData updateSelectedSprite(AnimationData data)
{
    data.sprite.x = data.frame * data.sprite.width;
    return data;
};

// Function to update the vector of an object
float updateVector(float vector, int velocity, float deltaTime)
{
    return vector += velocity * deltaTime;
};

// Function to update background position
BackgroundLayer UpdateBackgroundPosition(BackgroundLayer data, float deltaTime)
{
    // if off the screen
    if (data.position.x <= -data.texture.width * data.scale)
    {
        // reset the position to 0
        data.position.x = 0.0;
    }
    else
    {
        // otherwise, move the layer
        data.position.x = updateVector(data.position.x, data.velocity, deltaTime);
    }
    return data;
}

int main()
{

    // Window size variables
    int windowDimensions[2];
    windowDimensions[0] = 1024; // width (x)
    windowDimensions[1] = 768;  // height (y)

    // Initialize the window and set target framerate
    InitWindow(windowDimensions[0], windowDimensions[1], "Dasher");
    SetTargetFPS(60);

    // Spritesheet reference
    Texture2D PlayerSpriteSheet = LoadTexture("textures/scarfy.png");

    // Animation Data for the Player
    AnimationData PlayerData{
        {0.0, 0.0, static_cast<float>(PlayerSpriteSheet.width) / 6, static_cast<float>(PlayerSpriteSheet.height)},     // Rectangle sprite
        {(windowDimensions[0] / 2) - (PlayerData.sprite.width / 2), (windowDimensions[1] - PlayerData.sprite.height)}, // Vector2 position
        0,                                                                                                             // int frame
        5,                                                                                                             // int maxFame
        {1.0 / 12.0},                                                                                                  // float updateTime
        0.0};                                                                                                          // float runningTime

    // Player gameplay variables
    const int minimum_Y{windowDimensions[1] - static_cast<int>(PlayerData.sprite.height)};
    float player_velocity{0};

    // check if player is jumping
    bool is_jumping{false};

    // World gravity (Pixels/second)/second
    const int gravity{1000};
    const int jump_velocity{-600};

    // Hazard sprite
    Texture2D NebulaSpriteSheet = LoadTexture("textures/nebula_spritesheet.png");
    // AnimationData
    AnimationData Nebulae[3]{};
    for (unsigned i = 0; i < (sizeof(Nebulae) / sizeof(*Nebulae)); i++)
    {
        Nebulae[i].sprite.x = 0.0;
        Nebulae[i].sprite.y = 0.0;
        Nebulae[i].sprite.width = static_cast<float>(NebulaSpriteSheet.width) / 8;    // Rectangle sprite
        Nebulae[i].sprite.height = static_cast<float>(NebulaSpriteSheet.height) / 8;  // Rectangle sprite
        Nebulae[i].position.x = static_cast<float>(windowDimensions[0]) + (1000 * i); // Vector2 position
        Nebulae[i].position.y = windowDimensions[1] - Nebulae[i].sprite.height;       // Vector2 position
        Nebulae[i].frame = 0;                                                         // int frame
        Nebulae[i].maxFame = 8;                                                       // int maxFrame
        Nebulae[i].updateTime = 1.0 / 12.0;                                           // float updateTime
        Nebulae[i].runningTime = 0;                                                   // float runningTime
    }
    // float finishLine{Nebulae[(sizeof(Nebulae) / sizeof(*Nebulae)) - 1].position.x};

    // speed at which the hazard moves across the screen (pixels/second)
    int NebulaVelocity = -500;

    // Background Data
    BackgroundLayer Background{
        LoadTexture("textures/far-buildings.png"),                         // Texture for layer
        {},                                                                // Position for screen scroll
        -50,                                                               // Speed for screen scroll
        windowDimensions[0] / static_cast<float>(Background.texture.width) // Scale for texture
    };
    // Midground Data
    BackgroundLayer Midground{
        LoadTexture("textures/back-buildings.png"), // Texture for layer
        {},                                         // Position for screen scroll
        -100,                                       // Speed for screen scroll
        Background.scale                            // Scale for texture
    };
    // Foreground Data
    BackgroundLayer Foreground{
        LoadTexture("textures/foreground.png"), // Texture for layer
        {},                                     // Position for screen scroll
        -150,                                   // Speed for screen scroll
        Background.scale                        // Scale for texture
    };

    bool collision{};

    // Core game logic
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Get deltaTime(Time since last frame)
        float dT{GetFrameTime()};

        // Get position for 2nd background panel
        Vector2 Background2Position{Background.position.x + (Background.texture.width * Background.scale), Background.position.y};
        // Draw the background panels
        DrawTextureEx(Background.texture, Background.position, 0.0, Background.scale, WHITE);
        DrawTextureEx(Background.texture, Background2Position, 0.0, Background.scale, WHITE);
        // Update the background panel positions for next frame
        Background = UpdateBackgroundPosition(Background, dT);

        // Get position for 2nd Midground panel
        Vector2 Midground2Position{Midground.position.x + (Midground.texture.width * Midground.scale), Midground.position.y};
        // Draw the Midground panels
        DrawTextureEx(Midground.texture, Midground.position, 0.0, Midground.scale, WHITE);
        DrawTextureEx(Midground.texture, Midground2Position, 0.0, Midground.scale, WHITE);
        // Update the Midground panel positions for next frame
        Midground = UpdateBackgroundPosition(Midground, dT);

        // Get position for 2nd Foreground panel
        Vector2 Foreground2Position{Foreground.position.x + (Foreground.texture.width * Foreground.scale), Foreground.position.y};
        // Draw the Foreground panels
        DrawTextureEx(Foreground.texture, Foreground.position, 0.0, Foreground.scale, WHITE);
        DrawTextureEx(Foreground.texture, Foreground2Position, 0.0, Foreground.scale, WHITE);
        // Update the Foreground panel positions for next frame
        Foreground = UpdateBackgroundPosition(Foreground, dT);

        // check if player is touching the ground
        if (PlayerData.position.y >= minimum_Y)
        {
            // player is on the ground
            player_velocity = 0;
            PlayerData.position.y = minimum_Y;
            is_jumping = false;
        }
        else
        {
            // player is in the air
            player_velocity += gravity * dT;
        }

        // check for jumping request, if the player is in the air do nothing
        if (IsKeyPressed(KEY_SPACE) && !is_jumping)
        {
            // If player isnt jumping, add velocity and set them as jumping
            player_velocity += jump_velocity;
            is_jumping = true;
        }

        // Check for collision
        for (AnimationData nebula : Nebulae)
        {
            float pad{50};
            Rectangle nebulaRectangle{
                nebula.position.x + pad,
                nebula.position.y + pad,
                nebula.sprite.width - (2 * pad),
                nebula.sprite.height - (2 * pad)};

            Rectangle playerRectangle{
                PlayerData.position.x,
                PlayerData.position.y,
                PlayerData.sprite.width,
                PlayerData.sprite.height};
            if (CheckCollisionRecs(nebulaRectangle, playerRectangle))
            {
                collision = true;
            }
        }

        // check for win/loss
        if (collision)
        {
            // If collison is true, stop rendering and display loss text
            DrawText("GAME OVER!", windowDimensions[0] / 2, windowDimensions[1] / 2, 50, WHITE);
        }
        // if the last nebula is off the screen, display the win text
        else if (Nebulae[(sizeof(Nebulae) / sizeof(*Nebulae)) - 1].position.x + Nebulae->sprite.width < 0)
        {
            DrawText("YOU HAVE WON", windowDimensions[0] / 2, windowDimensions[1] / 2, 50, WHITE);
        }
        // otherwise, the game continues
        else
        {
            // update player position
            PlayerData.position.y = updateVector(PlayerData.position.y, player_velocity, dT);
            PlayerData = updateSelectedSprite(PlayerData);
            //  draw player sprite
            DrawTextureRec(PlayerSpriteSheet, PlayerData.sprite, PlayerData.position, WHITE);

            // update nebula positions and draw sprites
            for (unsigned i = 0; i < (sizeof(Nebulae) / sizeof(*Nebulae)); i++)
            {
                Nebulae[i].position.x = updateVector(Nebulae[i].position.x, NebulaVelocity, dT);
                Nebulae[i] = updateSelectedSprite(Nebulae[i]);
                DrawTextureRec(NebulaSpriteSheet, Nebulae[i].sprite, Nebulae[i].position, WHITE);
            }
            //  if player is not jumping check if we should update player animation
            if (!is_jumping)
            {
                PlayerData = updateAnimationFrame(PlayerData, dT);
            }

            // update each Nebulae
            for (unsigned i = 0; i < (sizeof(Nebulae) / sizeof(*Nebulae)); i++)
            {
                Nebulae[i] = updateAnimationFrame(Nebulae[i], dT);
            }
        }
        EndDrawing();
    }
    // Unload textures
    UnloadTexture(Background.texture);
    UnloadTexture(Midground.texture);
    UnloadTexture(Foreground.texture);
    UnloadTexture(PlayerSpriteSheet);
    UnloadTexture(NebulaSpriteSheet);
    // Terminate the program
    CloseWindow();
    return 0;
}
