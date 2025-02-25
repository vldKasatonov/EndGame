#include "../inc/header.h"

/* static const char* getOrderName(Item* item) {
  static char buffer[50];
  const char* stateStr;
  const char* typeStr;

  Texture2D drawOrder;

  switch (item->state) {
  case DIRTY:   stateStr = "Dirty"; break;
  case CLEAN:   stateStr = "Washed"; break;
  case PEELED:  stateStr = "Peeled"; break;
  case JUICED:  stateStr = "Juiced"; break;
  case FRIED:   stateStr = "Fryied"; break;
  case SLICED:  stateStr = "Sliced"; break;
  default:      stateStr = ""; break;
  }

  switch (item->type) {
  case APPLE:    typeStr = "apple"; break;
  case POTATO:   typeStr = "potato"; break;
  case CUCUMBER: typeStr = "cucumber"; break;
  case TOMATO:   typeStr = "tomato"; break;
  case SALAD:    typeStr = "salad"; break;
  default:       typeStr = "unknown"; break;
  }

  snprintf(buffer, sizeof(buffer), "%s %s", stateStr, typeStr);
  return buffer;
}

static void drawOrderText(int x, int y, const char* text) {
  DrawText(text, x, y, 20, BLACK);
} */



static void drawOrderImage(int x, int y, Item* item, GameTextures* textures) {
    DrawTexturePro(textures->cloud, (Rectangle) { 0, 0, textures->cloud.width, textures->cloud.height },
        (Rectangle) {
        x + 70, y - 30, 90, 90
    }, (Vector2) { 0, 0 }, 0.0f, WHITE);
  if (item->state == JUICED && item->type == APPLE) {
    DrawTexturePro(textures->juice, (Rectangle) { 0, 0, textures->juice.width, textures->juice.height },
      (Rectangle) {
      x + 92, y - 8, 45, 45
    }, (Vector2) { 0, 0 }, 0.0f, WHITE);
  }
  if (item->state == FRIED && item->type == POTATO) {
    DrawTexturePro(textures->friedPotato, (Rectangle) { 0, 0, textures->friedPotato.width, textures->friedPotato.height },
      (Rectangle) {
        x + 92, y - 8, 45, 55
    }, (Vector2) { 0, 0 }, 0.0f, WHITE);
  }
  if (item->state == MIXED && item->type == SALAD) {
    DrawTexturePro(textures->salad, (Rectangle) { 0, 0, textures->salad.width, textures->salad.height },
      (Rectangle) {
        x + 92, y - 8, 45, 45
    }, (Vector2) { 0, 0 }, 0.0f, WHITE);
  }


}
static bool activeItemIsOrder(Inventory* hotbar, Item* order) {
  if (!order) return false;
  Item* activeItem = hotbar->items[hotbar->activeItem];
  return activeItem && activeItem->state == order->state && activeItem->type == order->type;
}

void updateGuestPosition(Guest* guest, float deltaTime) {
  float moveSpeed = 200.0f;

  float dx = guest->targetX - guest->x;
  float dy = guest->targetY - guest->y;
  float distance = sqrt(dx * dx + dy * dy);

  if (distance > 1.0f) {
    float moveX = (dx / distance) * moveSpeed * deltaTime;
    float moveY = (dy / distance) * moveSpeed * deltaTime;

    guest->x += moveX;
    guest->y += moveY;
  }
  else {
    guest->x = guest->targetX;
    guest->y = guest->targetY;
  }
}

void renderQueue(Rectangle player, bool* isPopupOpen, int* servedCounter, GameTextures *textures) {
  double currentTime = GetElapsedTime();
  float deltaTime = GetFrameTime();

  tryAddGuestToRegister(&level, &queue, currentTime);

  // guest is waiting near cash register
  if (queue.atRegister != NULL) {
    Rectangle client = { queue.atRegister->x, queue.atRegister->y, 100, 100 };
    if (!(*isPopupOpen)) {
      updateGuestPosition(queue.atRegister, deltaTime);
    }
    //DrawRectangleRec(client, RED);
    DrawTexture(textures->guest, client.x, client.y, WHITE);

    int index = getNearbyInteractable(client, surfaces, surfaceCount);

    if (index != -1 && !(*isPopupOpen)
      && CheckCollisionRecs(client, surfaces[index].rect)
      && CheckCollisionRecs(player, surfaces[index].rect)) {
      if (IsKeyPressed(KEY_F)) {
        interactWithGuest(&hotbar, &queue, -1, surfaces[index].type);
      }
    }
  }

  // guests are waiting for their orders
  for (int i = 0; i < MAX_QUEUE; i++) {
    if (queue.queue[i] != NULL) {
      Rectangle client = { queue.queue[i]->x, queue.queue[i]->y, 100, 100 };
      if (!(*isPopupOpen)) {
        updateGuestPosition(queue.queue[i], deltaTime);
      }
      //DrawRectangleRec(client, BLUE);
      DrawTexture(textures->guest, client.x, client.y, WHITE);
      drawOrderImage(queue.queue[i]->x - 20, queue.queue[i]->y - 20, queue.queue[i]->order, textures);
      int index = getNearbyInteractable(client, surfaces, surfaceCount);
      if (index != -1 && !(*isPopupOpen) && CheckCollisionRecs(client, surfaces[index].rect) && CheckCollisionRecs(player, surfaces[index].rect)) {
        if (IsKeyPressed(KEY_F) && activeItemIsOrder(&hotbar, queue.queue[i]->order)) {
          interactWithGuest(&hotbar, &queue, i, surfaces[index].type);
          if (surfaces[index].type == PICK_UP) {
              (*servedCounter)++;
          }
        }
      }
    }
  }
  // served guest leaves
  if (queue.outOfQueue != NULL) {
    Rectangle client = { queue.outOfQueue->x, queue.outOfQueue->y, 100, 100 };
    if (!(*isPopupOpen)) {
      updateGuestPosition(queue.outOfQueue, deltaTime);
    }
    //DrawRectangleRec(client, GREEN);
    DrawTexture(textures->reversedGuest, client.x, client.y, WHITE);

    if (queue.outOfQueue->x < -50) {
      queue.outOfQueue = NULL;
    }
  }
}

