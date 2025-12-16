#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

// Originally had the camera looking around, can't remember why I
// disabled it but some code remains.
const int LOOKUP_WIDTH = WINDOW_WIDTH * 2;
const int LOOKUP_HEIGHT = WINDOW_HEIGHT * 2;

// Function to apply tunnel effect using angle and distance tables
void applyTunnelEffect(const std::vector<std::vector<float>>& angleTable,
                       const std::vector<std::vector<float>>& distanceTable,
                       SDL_Surface* textureSurface,
                       std::vector<Uint32>& outputPixels,
                       int textureWidth, int textureHeight,
                       float tunnel_rotated, float tunnel_zoomed,
                       int x_offset, int y_offset,
                       int iteration = 0) {
    
    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            
            // Look up the coordinates
            int lookup_x = x + x_offset;
            int lookup_y = y + y_offset;
            
            float angle = angleTable[lookup_y][lookup_x];
            float distance = distanceTable[lookup_y][lookup_x];
            
            // Normalize angle then map to texture width
            float normalizedAngle = angle;
            if (normalizedAngle < 0) normalizedAngle += 360.0f;
            float texture_x_f = (normalizedAngle / 360.0f) * textureWidth + tunnel_rotated;
            
            // Map distance directly to texture coordinates
            float texture_y_f = distance + tunnel_zoomed;
            
            // Convert to screen coordinates
            int texture_x = (int)texture_x_f;
            int texture_y = (int)texture_y_f;
            
            // Fix the values so they are in range of the texture
            texture_x = texture_x % textureWidth;
            if (texture_x < 0) texture_x += textureWidth;
            
            texture_y = texture_y % textureHeight;
            if (texture_y < 0) texture_y += textureHeight;
            
            // Draw it
            Uint32* pixels = (Uint32*)textureSurface->pixels;
            Uint32 texturePixel = pixels[texture_y * textureWidth + texture_x];
            
            // Apply rotation
            int rotated_x = y;
            int rotated_y = WINDOW_WIDTH - 1 - x;
            int outputIndex = rotated_y * WINDOW_WIDTH + rotated_x;
            
            outputPixels[outputIndex] = texturePixel;
        }
    }
}

int main(int argc, char* argv[]) {
    srand((unsigned int)time(nullptr));
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tunnel",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
    
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    // build angle table
    std::vector<std::vector<float>> angleTable(LOOKUP_HEIGHT, std::vector<float>(LOOKUP_WIDTH));

    for (int y = 0; y < LOOKUP_HEIGHT; ++y) {
        for (int x = 0; x < LOOKUP_WIDTH; ++x) {
            float relative_x = x - LOOKUP_WIDTH / 2;
            float relative_y = LOOKUP_HEIGHT / 2 - y;
            
            float angle = 0;
            
            if (relative_y == 0) {
                // Use a very small value instead of zero to avoid discontinuity
                relative_y = 0.001f;
            }

            angle = atanf(relative_x/relative_y) * 180.0f / M_PI;

            if (relative_y > 0) {
                angle = angle + 180;
            }

            angleTable[y][x] = angle;
        }
    }

    // build the distance table
    std::vector<std::vector<float>> distanceTable(LOOKUP_HEIGHT, std::vector<float>(LOOKUP_WIDTH));
    const float BIG_NUMBER = 8388608.0f;
    
    for (int y = 0; y < LOOKUP_HEIGHT; ++y) {
        for (int x = 0; x < LOOKUP_WIDTH; ++x) {
            float relative_x = x - LOOKUP_WIDTH / 2;
            float relative_y = LOOKUP_HEIGHT / 2 - y;
            
            // Avoid division by zero at center
            // Prevent extremely large distances
            float distance_squared = relative_x * relative_x + relative_y * relative_y;
            if (distance_squared < 1.0f) {
                distance_squared = 1.0f; 
            }
            
            // Calculate depth
            float depth = BIG_NUMBER / distance_squared;
            distanceTable[y][x] = depth;
        }
    }

    SDL_Surface* textureSurface = IMG_Load("texture.png");
    if (textureSurface == nullptr) {
        std::cerr << "Unable to load texture.png! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tunnelTexture = SDL_CreateTextureFromSurface(renderer, textureSurface);
    if (tunnelTexture == nullptr) {
        std::cerr << "Unable to create texture from texture.png! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textureSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    int textureWidth, textureHeight;
    SDL_QueryTexture(tunnelTexture, nullptr, nullptr, &textureWidth, &textureHeight);

    SDL_Texture* tunnelEffectTexture = SDL_CreateTexture(renderer, textureSurface->format->format, 
                                                        SDL_TEXTUREACCESS_STATIC, 
                                                        WINDOW_WIDTH, WINDOW_HEIGHT);
    
    if (tunnelEffectTexture == nullptr) {
        std::cerr << "Tunnel effect texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textureSurface);
        SDL_DestroyTexture(tunnelTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Pixel Buffer
    std::vector<Uint32> tunnelPixels(WINDOW_WIDTH * WINDOW_HEIGHT);

    // The end of the tunnel produces a moire like effect
    // So we cover it with a false distance fade
    SDL_Surface* tunnelEndSurface = IMG_Load("tunnel-end.png");
    if (tunnelEndSurface == nullptr) {
        std::cerr << "Unable to load tunnel-end.png! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(textureSurface);
        SDL_DestroyTexture(tunnelEffectTexture);
        SDL_DestroyTexture(tunnelTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tunnelEndTexture = SDL_CreateTextureFromSurface(renderer, tunnelEndSurface);
    if (tunnelEndTexture == nullptr) {
        std::cerr << "Unable to create texture from tunnel-end.png! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(tunnelEndSurface);
        SDL_FreeSurface(textureSurface);
        SDL_DestroyTexture(tunnelEffectTexture);
        SDL_DestroyTexture(tunnelTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_SetTextureBlendMode(tunnelEndTexture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(tunnelEndSurface);

    // Animation variables
    float tunnel_rotated = 0.0f;
    float tunnel_zoomed = 0.0f;
    int iteration = 0; // For debugging purposes
    
    // Looking around offsets
    int x_offset = WINDOW_WIDTH / 2;
    int y_offset = WINDOW_HEIGHT / 2;
    
    // Rotation control system
    float current_rotation_speed = 0.0f;
    float target_rotation_speed = 0.0f;       // Target rotation speed (-1 to 1)
    float rotation_speed_change_rate = 0.005f;
    float rotation_duration = 0.0f;
    float rotation_timer = 0.0f;
    const float FRAME_TIME = 1.0f / 60.0f;
    
    target_rotation_speed = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    rotation_duration = 1.0f + ((float)rand() / RAND_MAX) * 4.0f;

    // Main loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

        SDL_RenderClear(renderer);

        applyTunnelEffect(angleTable, distanceTable, textureSurface, tunnelPixels, textureWidth, textureHeight, tunnel_rotated, tunnel_zoomed, x_offset, y_offset, iteration);
        
        SDL_UpdateTexture(tunnelEffectTexture, nullptr, tunnelPixels.data(), WINDOW_WIDTH * sizeof(Uint32));
        
        SDL_RenderCopy(renderer, tunnelEffectTexture, nullptr, nullptr);
        
        int tunnel_center_x_unrotated = (LOOKUP_WIDTH / 2) - x_offset;
        int tunnel_center_y_unrotated = (LOOKUP_HEIGHT / 2) - y_offset;
        
        int tunnel_center_x = tunnel_center_y_unrotated;
        int tunnel_center_y = WINDOW_WIDTH - 1 - tunnel_center_x_unrotated;
        
        int end_texture_width, end_texture_height;
        SDL_QueryTexture(tunnelEndTexture, nullptr, nullptr, &end_texture_width, &end_texture_height);
        
        SDL_Rect endTextureRect;
        endTextureRect.x = tunnel_center_x - (end_texture_width / 2);
        endTextureRect.y = tunnel_center_y - (end_texture_height / 2);
        endTextureRect.w = end_texture_width;
        endTextureRect.h = end_texture_height;
        
        SDL_RenderCopy(renderer, tunnelEndTexture, nullptr, &endTextureRect);

        tunnel_zoomed += 12.0f;
        
        // Rotation control system
        rotation_timer += FRAME_TIME;
        
        // Ease in rotations
        if (fabs(current_rotation_speed - target_rotation_speed) > 0.001f) {
            if (current_rotation_speed < target_rotation_speed) {
                current_rotation_speed += rotation_speed_change_rate;
                if (current_rotation_speed > target_rotation_speed) {
                    current_rotation_speed = target_rotation_speed;
                }
            } else if (current_rotation_speed > target_rotation_speed) {
                current_rotation_speed -= rotation_speed_change_rate;
                if (current_rotation_speed < target_rotation_speed) {
                    current_rotation_speed = target_rotation_speed;
                }
            }
        }
        
        if (rotation_timer >= rotation_duration) {
            target_rotation_speed = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
            rotation_duration = 1.0f + ((float)rand() / RAND_MAX) * 4.0f;
            rotation_timer = 0.0f;
        }
        
        tunnel_rotated += current_rotation_speed;
        
        // Looking around effect
        float time = iteration * 0.02f; 
        x_offset = WINDOW_WIDTH / 2 + (int)(sin(time * 0.3f) * 100.0f);
        y_offset = WINDOW_HEIGHT / 2 + (int)(cos(time * 0.5f) * 80.0f);
        
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_FreeSurface(textureSurface);
    SDL_DestroyTexture(tunnelEffectTexture);
    SDL_DestroyTexture(tunnelEndTexture);
    SDL_DestroyTexture(tunnelTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}