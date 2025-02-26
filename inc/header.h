#ifndef HEADER_H
#define HEADER_H

#include "../resource/raylib/src/raylib.h"
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

Font GetCustomFont(void);
void UnloadCustomFont(void);

#define NUM_LEVELS 3
#define INVENTORY_SIZE 7
#define MAX_QUEUE 3
#define MAX_LEVEL_GUESTS 6

// gamestate
typedef enum GameScreen {
    MAIN_MENU = 0,
    SELECT_PLAYER,
    SETTINGS,
    GUIDE_PAGE1,
    GUIDE_PAGE2,
    GUIDE_PAGE3,
    LEVEL_MENU,
    LEVEL_MENU2,
    GAMEPLAY,
    GAMEPLAY_SETTINGS,
    DEVELOPERS
} GameScreen;

typedef struct Level_stars {
    int levelStars[NUM_LEVELS];
} Level_stars;

typedef struct GameConfig {
    double screenWidth;
    double screenHeight;
    double buttonWidth;
    double buttonHeight;
    double fontSizeHeader1;
    double fontSizeHeader2;
    double fontSizeHeader3;
    double fontSizeParagraph;
} GameConfig;

typedef struct CustomColors {
    Color buttonBackgroundColor;
    Color menuBackgroundColor;
    Color musicColor;
    Color sliderColor;
    Color redColor;
    Color levelRectangleColor;
    Color circleColor;
    Color circleStrokeColor;
    Color nonactiveStarColor;
    Color activeStarColor;
    Color noneColor;
    Color nonactiveLevelColor;
    Color tonedPreviewColor;
} CustomColors;

typedef struct GameTextures {
    Texture2D gearTexture;
    Texture2D volume_on;
    Texture2D volume_on2;
    Texture2D music_on;
    Texture2D volume_off;
    Texture2D music_off;
    Texture2D arrow;
    Texture2D del_texture;
    Texture2D guide;
    Texture2D exit;
    Texture2D pause;
    Texture2D background;
    Texture2D play_button;
    Texture2D star;
    Texture2D one_player;
    Texture2D two_players;
    Texture2D chef;
    Texture2D right_arrow;
    Texture2D left_arrow;
    Texture2D map3;
    Texture2D image3;
    Texture2D level_preview;
    Texture2D served_icon;
    Texture2D guest;
    Texture2D reversedGuest;
    Texture2D dirtyApple;
    Texture2D washedApple;
    Texture2D slicedApple;
    Texture2D juice;
    Texture2D dirtyPotato;
    Texture2D washedPotato;
    Texture2D slicedPotato;
    Texture2D peeledPotato;
    Texture2D friedPotato;
    Texture2D dirtyCucumber;
    Texture2D washedCucumber;
    Texture2D slicedCucumber;
    Texture2D dirtyTomato;
    Texture2D washedTomato;
    Texture2D slicedTomato;
    Texture2D salad;
    Texture2D guideJuice;
    Texture2D guidePotato;
    Texture2D guideSalad;
    Texture2D image1;
    Texture2D image2;
    Texture2D map1;
    Texture2D map2;
    Texture2D cloud;
    Texture2D fButton;
} GameTextures;

void LoadTextures(GameTextures *textures);
void UnloadTextures(GameTextures *textures);

// gameplay
typedef struct Player {
    Vector2 position;
} Player;

typedef struct PlayerConfig {
    float speed;
    float playerWidth;
    float playerHeight;
} PlayerConfig;

typedef struct {
    int x;
    int y;
} Position;

typedef struct QueueConfig {
    int registerX;
    int registerY;
    Position spots[MAX_QUEUE];
} QueueConfig;

typedef struct HotbarConfig {
    int cellWidth;
    int cellHeight;
    int margin;
    Color cellColor;
    Color cellBorderColor;
    Color cellBorderColorActive;
} HotbarConfig;

typedef enum {
    NONE,
    POTATO_BED,
    TOMATO_BED,
    CUCUMBER_BED,
    APPLE_TREE,
    WASHBASIN,
    PEELING_TABLE,
    SLICING_TABLE,
    GARBAGE_CAN,
    STOVE,
    JUICEMAKER,
    PICK_UP,
    CASHBOX,
    PLATE
} InteractableType;

typedef struct {
    Rectangle rect;
    Color color;
    InteractableType type;
} Surface;

typedef enum {
    DIRTY,
    CLEAN,
    PEELED,
    JUICED,
    FRIED,
    SLICED,
    MIXED
} IngredientState;

typedef enum {
    APPLE,
    POTATO,
    CUCUMBER,
    TOMATO,
    SALAD
} Ingredient;

typedef struct {
    IngredientState state;
    Ingredient type;
} Item;

typedef struct {
    Item* items[INVENTORY_SIZE];
    int activeItem;
} Inventory;

typedef struct LevelData {
    int guestCount;
    Item levelMenu[MAX_LEVEL_GUESTS];
    Surface surfaces[34];
    int surfaceCount;
} LevelData;

typedef struct {
    int id;
    int arrivalTime;
    Item* order;
    int x;
    int y;
    int targetX;
    int targetY;
} Guest;

typedef struct {
    Guest* queue[MAX_QUEUE];
    int queueSize;
    Guest* atRegister;
    Guest* outOfQueue;
} Queue;

typedef struct {
    Guest* allGuests;
    int nextGuestIndex;
    int guestCount;
} Level;

void initializeQueue(Queue*);
bool hasQueueSpace(Queue*);
bool acceptOrder(Queue*);
void serveGuestAtIndex(Queue*, int);
void initializeLevel(LevelData*, Level*);
void loadLevel(LevelData*, Level*);
void clearLevel(Level*);
void tryAddGuestToRegister(Level*, Queue*, int);
void initializeSurfaces(LevelData*);
void initializeInventory(Inventory*);
int findFreeCell(Inventory*);
int addItem(Inventory*, Item*);
Item* removeActiveItem(Inventory*);
void clearInventory(Inventory*);
void setActiveItem(Inventory*, int);
void reloadInventory(Inventory*);
extern LevelData levelData[];

bool canFry(Item*);
bool canWash(Item*);
bool canPeel(Item*);
bool canJuice(Item*);
bool canSlice(Item*);
bool canServe(Item*);
bool canThrowAway(Item* item);

Item* getDirtyItem(Ingredient);
void updateItem(Item*, IngredientState);
void deleteItem(Item** item);
Item* getSalad(void);

// game render
void renderTimer(void);
void renderLevelMenu(GameTextures *textures, Level_stars *level_star, Player*);
void renderLevelMenu2(GameTextures*);
void renderDevelopers(GameTextures *textures);
void drawStars(int, int, GameTextures*, Vector2);
void drawText(int, Rectangle, Vector2, char*, char* time);
void drawLevel(int, int, GameTextures*, Texture2D, Vector2);
void tonedRect(int);
void renderMainMenu(GameTextures*, bool*);
void renderGameplaySettings(GameTextures*, float*, float*, bool*, int*);
void renderGuidePage1(GameTextures *textures);
void renderGuidePage2(GameTextures *textures);
void renderGuidePage3(GameTextures *textures);
void renderSelectPlayer(GameTextures*);
void renderSettings(GameTextures *textures, float *volumeMusic, float *volumeEffects, Level_stars *gameState);
void renderHotbar(GameTextures*);
void renderQueue(Rectangle, bool*, int*, GameTextures*);
void renderGameplay(Player*, GameTextures*, bool*, int *servedCounter, int maxServed);
void drawStars_gameplay(int, double, GameTextures*, Vector2);
void DisableGameplayInput(bool);
void DrawLevelSucsses(bool *isExitPopupOpen, GameTextures *textures, int*);
void updateLevelStars(Level_stars*, int, int);
int calculateStarsForLevel(void);
void interactWithGuest(Inventory* inventory, Queue* queue, int index, InteractableType type);
int getNearbyInteractable(Rectangle player, Surface* surfaces, int surfaceCount);
void interactWithObject(Inventory*, InteractableType);
void InitGameAudio(void);
void UpdateGameAudio(void);
void UnloadGameAudio(void);
void SetMusicVolumeLevel(float volume);
void UpdateMenuMusic(void);
void UpdateGameplayMusic(void);
void UpdateMusicVolume(float volume);
void InitSoundEffects(void);
void UnloadSoundEffects(void);
void PlaySoundEffect(Sound sound);
void SetEffectsVolume(float volume);
void StartGameTimer(void);
void PauseGameTimer(void);
void ResumeGameTimer(void);
void ResetGameTimer(void);
double GetElapsedTime(void);
void LoadBestTime(void);
void SaveBestTime(void);
double GetBestTime(void);

extern GameScreen currentState;
extern GameScreen previousState;
extern GameScreen previousGuideState;
extern Inventory hotbar;
extern Queue queue;
extern Level level;
extern Surface surfaces[];
extern int surfaceCount;
extern GameConfig gameConfig;
extern CustomColors customColors;
extern QueueConfig queueConfig;
extern HotbarConfig hotbarConfig;
extern PlayerConfig playerConfig;
extern int levelNumber;
extern Sound buttonClick;
extern Sound itemPickup;
extern Sound completeOrder;
extern Sound cutting;
extern Sound frying;
extern Sound leaves;
extern Sound peeling;
extern Sound washing;
extern Sound wrongOrder;
extern Sound pouring;
extern Sound levelComplete;

#endif
