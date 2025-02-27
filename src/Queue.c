#include "../inc/header.h"

/* static const char* getOrderName(t_item* item) {
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



static void drawOrderImage(int x, int y, t_item* item, t_game_textures* textures) {
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
    DrawTexturePro(textures->fried_potato, (Rectangle) { 0, 0, textures->fried_potato.width, textures->fried_potato.height },
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
static bool activeItemIsOrder(t_inventory* hotbar, t_item* order) {
  if (!order) return false;
  t_item* active_item = hotbar->items[hotbar->active_item];
  return active_item && active_item->state == order->state && active_item->type == order->type;
}

void updateGuestPosition(t_guest* guest, float deltaTime) {
  float moveSpeed = 200.0f;

  float dx = guest->target_x - guest->x;
  float dy = guest->target_y - guest->y;
  float distance = sqrt(dx * dx + dy * dy);

  if (distance > 1.0f) {
    float moveX = (dx / distance) * moveSpeed * deltaTime;
    float moveY = (dy / distance) * moveSpeed * deltaTime;

    guest->x += moveX;
    guest->y += moveY;
  }
  else {
    guest->x = guest->target_x;
    guest->y = guest->target_y;
  }
}

void mx_render_queue(Rectangle player, bool* isPopupOpen, int* servedCounter, t_game_textures *textures) {
  double currentTime = mx_get_elapsed_time();
  float deltaTime = GetFrameTime();

  mx_try_add_guest_to_register(&level, &queue, currentTime);

  // guest is waiting near cash register
  if (queue.at_register != NULL) {
    Rectangle client = { queue.at_register->x, queue.at_register->y, 100, 100 };
    if (!(*isPopupOpen)) {
      updateGuestPosition(queue.at_register, deltaTime);
    }
    //DrawRectangleRec(client, RED);
    DrawTexture(textures->guest, client.x, client.y, WHITE);

    int index = mx_get_nearby_interactable(client, surfaces, surface_count);

    if (index != -1 && !(*isPopupOpen)
      && CheckCollisionRecs(client, surfaces[index].rect)
      && CheckCollisionRecs(player, surfaces[index].rect)) {
      if (IsKeyPressed(KEY_F)) {
        mx_interact_with_guest(&hotbar, &queue, -1, surfaces[index].type);
      }
    }
  }

  // guests are waiting for their orders
  for (int i = 0; i < MX_MAX_QUEUE; i++) {
    if (queue.queue[i] != NULL) {
      Rectangle client = { queue.queue[i]->x, queue.queue[i]->y, 100, 100 };
      if (!(*isPopupOpen)) {
        updateGuestPosition(queue.queue[i], deltaTime);
      }
      //DrawRectangleRec(client, BLUE);
      DrawTexture(textures->guest, client.x, client.y, WHITE);
      drawOrderImage(queue.queue[i]->x - 20, queue.queue[i]->y - 20, queue.queue[i]->order, textures);
      int index = mx_get_nearby_interactable(client, surfaces, surface_count);
      if (index != -1 && !(*isPopupOpen) && CheckCollisionRecs(client, surfaces[index].rect) && CheckCollisionRecs(player, surfaces[index].rect)) {
        if (IsKeyPressed(KEY_F) && activeItemIsOrder(&hotbar, queue.queue[i]->order)) {
          mx_interact_with_guest(&hotbar, &queue, i, surfaces[index].type);
          if (surfaces[index].type == PICK_UP) {
              (*servedCounter)++;
          }
        }
      }
    }
  }
  // served guest leaves
  if (queue.out_of_queue != NULL) {
    Rectangle client = { queue.out_of_queue->x, queue.out_of_queue->y, 100, 100 };
    if (!(*isPopupOpen)) {
      updateGuestPosition(queue.out_of_queue, deltaTime);
    }
    //DrawRectangleRec(client, GREEN);
    DrawTexture(textures->reversed_guest, client.x, client.y, WHITE);

    if (queue.out_of_queue->x < -50) {
      queue.out_of_queue = NULL;
    }
  }
}

