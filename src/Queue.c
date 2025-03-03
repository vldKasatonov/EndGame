#include "../inc/header.h"

static void draw_order_image(int x, int y, t_item* item, t_game_textures* textures) {
    DrawTexturePro(textures->cloud, (Rectangle) { 0, 0, textures->cloud.width, textures->cloud.height },
        (Rectangle) {x + 70, y - 30, 90, 90}, (Vector2) { 0, 0 }, 0.0f, WHITE);
    if (item->state == JUICED && item->type == APPLE) {
        DrawTexturePro(textures->juice, (Rectangle) { 0, 0, textures->juice.width, textures->juice.height },
        	(Rectangle) {x + 92, y - 8, 45, 45}, (Vector2) { 0, 0 }, 0.0f, WHITE);
    }
    if (item->state == FRIED && item->type == POTATO) {
        DrawTexturePro(textures->fried_potato, (Rectangle) { 0, 0, textures->fried_potato.width, textures->fried_potato.height },
        	(Rectangle) {x + 92, y - 8, 45, 55}, (Vector2) { 0, 0 }, 0.0f, WHITE);
    }
    if (item->state == MIXED && item->type == SALAD) {
        DrawTexturePro(textures->salad, (Rectangle) { 0, 0, textures->salad.width, textures->salad.height },
        	(Rectangle) {x + 92, y - 8, 45, 45}, (Vector2) { 0, 0 }, 0.0f, WHITE);
    }
}

static bool active_item_is_order(t_inventory* hotbar, t_item* order) {
    if (!order) return false;
    t_item* active_item = hotbar->items[hotbar->active_item];
    return active_item && active_item->state == order->state && active_item->type == order->type;
}

void update_guest_position(t_guest* guest, float delta_time) {
    float move_speed = 200.0f;

    float dx = guest->target_x - guest->x;
    float dy = guest->target_y - guest->y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 1.0f) {
        float move_x = (dx / distance) * move_speed * delta_time;
        float move_y = (dy / distance) * move_speed * delta_time;

        guest->x += move_x;
        guest->y += move_y;
    }
    else {
        guest->x = guest->target_x;
        guest->y = guest->target_y;
    }
}

void mx_render_queue(Rectangle player, bool* is_popup_open, int* served_counter, t_game_textures *textures) {
  	double current_time = mx_get_elapsed_time();
  	float delta_time = GetFrameTime();

  	mx_try_add_guest_to_register(&level, &queue, current_time);

  	// guest is waiting near cash register
  	if (queue.at_register != NULL) {
    	Rectangle client = { queue.at_register->x, queue.at_register->y, 100, 100 };
    	if (!(*is_popup_open)) {
      		update_guest_position(queue.at_register, delta_time);
    	}
    	DrawTexture(textures->guest, client.x, client.y, WHITE);

    	int index = mx_get_nearby_interactable(client, surfaces, surface_count);

    	if (index != -1 && !(*is_popup_open)
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
      		if (!(*is_popup_open)) {
        		update_guest_position(queue.queue[i], delta_time);
      		}
      		DrawTexture(textures->guest, client.x, client.y, WHITE);
      		draw_order_image(queue.queue[i]->x - 20, queue.queue[i]->y - 20, queue.queue[i]->order, textures);
      		int index = mx_get_nearby_interactable(client, surfaces, surface_count);
      		if (index != -1 && !(*is_popup_open) && CheckCollisionRecs(client, surfaces[index].rect) && CheckCollisionRecs(player, surfaces[index].rect)) {
        		if (IsKeyPressed(KEY_F) && active_item_is_order(&hotbar, queue.queue[i]->order)) {
          			mx_interact_with_guest(&hotbar, &queue, i, surfaces[index].type);
          			if (surfaces[index].type == PICK_UP) {
              			(*served_counter)++;
          			}
        		}
      		}
    	}
  	}
  	// served guest leaves
  	if (queue.out_of_queue != NULL) {
    	Rectangle client = { queue.out_of_queue->x, queue.out_of_queue->y, 100, 100 };
    	if (!(*is_popup_open)) {
      		update_guest_position(queue.out_of_queue, delta_time);
    	}
    	DrawTexture(textures->reversed_guest, client.x, client.y, WHITE);

    	if (queue.out_of_queue->x < -50) {
      		queue.out_of_queue = NULL;
    	}
  	}
}
