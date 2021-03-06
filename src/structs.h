//
// Created by ali on 25/12/18.
//

#ifndef ALTER_TANK_STRUCTS_H
#define ALTER_TANK_STRUCTS_H

#include <stdbool.h>
#include <SDL_video.h>
#include <SDL_render.h>

#define BULLET_COUNT 5
#define MAX_ITEM_COUNT 4

typedef enum {
    Enable, Disable, FadeOut
} BulletState;

typedef struct {
    double x, y, vx, vy;
    double instantiate_time;
    BulletState state;
    bool isBomb;
    bool isParticle;
} Bullet;

typedef struct {
    int red, green, blue, alpha;
} Color;

typedef struct {
    int x1, y1, x2, y2;
} Wall;

typedef struct {
    char source[256];
    Wall walls[100];
    int wall_count;
} Map;

typedef struct {
    double x, y;
    Color color;
    int colorIndex;
    double angle;
    Bullet bullets[BULLET_COUNT];
    bool enable;
    int score;
    int last_smoke_time;
    int forward_key, backward_key, right_key, left_key, fire_key;
    bool hasMachineGun, hasLaser, hasMine, hasBomb;
    int BombState;
    bool hasShoot;
} Tank;

typedef struct{
    char Caption[120];
} UIButton;

typedef enum {
    Idle,
    Hover,
    Pressed
} ButtonState;

typedef enum {
    Play2v2,
    Play3v3,
    Setting,
    Reload,
    Exit,
    None,
    Load,
    Save,
    Resume,
    Pause,
    ShowMenu
} Action;

typedef struct {
    char text[100];
    ButtonState state;
    Color color, hover_color, pressed_color, text_color;
    Action action;
} Button;

typedef enum {
    Bomb=0, Mine=1, MachineGun=2, Laser=3
} ItemType;

typedef struct {
    int x, y;
    ItemType type;
    bool enable;
} Item;

typedef struct {
    Map map;
    int mapIndex;
    int tank_count;
    Tank tanks[5];
    Button button[5];
    int last_destroy_time;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int WinScore;
    Item item[MAX_ITEM_COUNT];
    bool isLoaded;
} Manager;

typedef struct {
    Color color;
    float life_time;
    float radius, radius_speed;
    float x, y, dx, dy;
} Particle;

typedef struct {
    Particle particles[30];
    int particle_count;
    int x, y;
    int instantiate_time;
    bool enable;
} Smoke;

#endif //ALTER_TANK_STRUCTS_H
