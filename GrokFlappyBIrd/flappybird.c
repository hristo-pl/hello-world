#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>  // Added for text rendering
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BIRD_WIDTH 40
#define BIRD_HEIGHT 30
#define PIPE_WIDTH 70
#define PIPE_GAP 150
#define GRAVITY 0.25f
#define JUMP_VELOCITY -6.0f

typedef enum { MENU, PLAYING, GAME_OVER } GameState;

typedef struct {
    float x, y;
    float velocity;
} Bird;

typedef struct {
    float x;
    int gap_y;
} Pipe;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_Error: %s\n", Mix_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {  // Initialize SDL_ttf
        printf("SDL_ttf could not initialize! SDL_Error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load font (you'll need a .ttf file or adjust the path)
    TTF_Font* font = TTF_OpenFont("SourceCodePro-Bold.ttf", 24);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        // Continue without font, text won't render
    }

    Mix_Chunk* jumpSound = Mix_LoadWAV("jump.wav");
    if (!jumpSound) {
        printf("Failed to load jump sound! SDL_mixer Error: %s\n", Mix_GetError());
    }

    GameState state = MENU;
    Bird bird = {200, SCREEN_HEIGHT/2, 0};
    Pipe pipe = {SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - PIPE_GAP - 100) + 50};
    bool running = true;
    float pipe_velocity = -2.0f;
    int score = 0;
    int selected = 0;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            switch (state) {
                case MENU:
                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN) {
                            selected = !selected;
                        }
                        if (e.key.keysym.sym == SDLK_RETURN) {
                            if (selected == 0) {
                                state = PLAYING;
                                bird.y = SCREEN_HEIGHT/2;
                                bird.velocity = 0;
                                pipe.x = SCREEN_WIDTH;
                                score = 0;
                            } else {
                                running = false;
                            }
                        }
                    }
                    break;

                case PLAYING:
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                        bird.velocity = JUMP_VELOCITY;
                        if (jumpSound) Mix_PlayChannel(-1, jumpSound, 0);
                    }
                    break;

                case GAME_OVER:
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                        state = MENU;
                    }
                    break;
            }
        }

        if (state == PLAYING) {
            bird.velocity += GRAVITY;
            bird.y += bird.velocity;
            pipe.x += pipe_velocity;

            if (pipe.x < -PIPE_WIDTH) {
                pipe.x = SCREEN_WIDTH;
                pipe.gap_y = rand() % (SCREEN_HEIGHT - PIPE_GAP - 100) + 50;
                score++;
            }

            if (bird.y < 0 || bird.y + BIRD_HEIGHT > SCREEN_HEIGHT) {
                state = GAME_OVER;
            }
            if (bird.x + BIRD_WIDTH > pipe.x && bird.x < pipe.x + PIPE_WIDTH) {
                if (bird.y < pipe.gap_y || bird.y + BIRD_HEIGHT > pipe.gap_y + PIPE_GAP) {
                    state = GAME_OVER;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color black = {0, 0, 0, 255};

        switch (state) {
            case MENU:
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect startRect = {SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 40, 100, 40};
                SDL_Rect exitRect = {SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 20, 100, 40};
                SDL_RenderFillRect(renderer, &startRect);
                SDL_RenderFillRect(renderer, &exitRect);
                
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, selected == 0 ? &startRect : &exitRect);

                if (font) {
                    SDL_Surface* startSurface = TTF_RenderText_Solid(font, "Start Game", black);
                    SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", black);
                    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
                    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
                    
                    SDL_Rect startTextRect = {SCREEN_WIDTH/2 - 40, SCREEN_HEIGHT/2 - 35, 80, 30};
                    SDL_Rect exitTextRect = {SCREEN_WIDTH/2 - 20, SCREEN_HEIGHT/2 + 25, 40, 30};
                    
                    SDL_RenderCopy(renderer, startTexture, NULL, &startTextRect);
                    SDL_RenderCopy(renderer, exitTexture, NULL, &exitTextRect);
                    
                    SDL_FreeSurface(startSurface);
                    SDL_FreeSurface(exitSurface);
                    SDL_DestroyTexture(startTexture);
                    SDL_DestroyTexture(exitTexture);
                }
                break;

            case PLAYING:
                SDL_Rect birdRect = {(int)bird.x, (int)bird.y, BIRD_WIDTH, BIRD_HEIGHT};
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                SDL_RenderFillRect(renderer, &birdRect);

                SDL_Rect upperPipe = {(int)pipe.x, 0, PIPE_WIDTH, pipe.gap_y};
                SDL_Rect lowerPipe = {(int)pipe.x, pipe.gap_y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - (pipe.gap_y + PIPE_GAP)};
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &upperPipe);
                SDL_RenderFillRect(renderer, &lowerPipe);
                break;

            case GAME_OVER:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_Rect gameOverRect = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 20, 200, 40};
                SDL_RenderFillRect(renderer, &gameOverRect);
                
                if (font) {
                    SDL_Surface* goSurface = TTF_RenderText_Solid(font, "Game Over", white);
                    SDL_Texture* goTexture = SDL_CreateTextureFromSurface(renderer, goSurface);
                    SDL_Rect goTextRect = {SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 15, 100, 30};
                    SDL_RenderCopy(renderer, goTexture, NULL, &goTextRect);
                    
                    SDL_FreeSurface(goSurface);
                    SDL_DestroyTexture(goTexture);
                }
                break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (jumpSound) Mix_FreeChunk(jumpSound);
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Final Score: %d\n", score);
    return 0;
}
