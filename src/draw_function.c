#include "../inc/header.h"

void mx_draw_stars(int space, int star, t_game_textures *textures, Vector2 circle) {
    Rectangle star_rec = { 225, 390, 75, 75 };
    Rectangle src_star = { 0, 0, textures->star.width,
    		   	 textures->star.height };
    Color star_1 = custom_colors.nonactive_star_color;
    Color star_2 = custom_colors.nonactive_star_color;
    Color star_3 = custom_colors.nonactive_star_color;
    switch(star) {
        case 1:
            star_1 = custom_colors.active_star_color;
            break;
        case 2:
            star_1 = custom_colors.active_star_color;
            star_2 = custom_colors.active_star_color;
            break;
        case 3:
            star_1 = custom_colors.active_star_color;
            star_2 = custom_colors.active_star_color;
            star_3 = custom_colors.active_star_color;
            break;
        default: 
            break;
    }
    DrawTexturePro(textures->star, src_star, (Rectangle){ star_rec.x + space,
    		   star_rec.y, star_rec.width, star_rec.height },
               (Vector2){0, 0}, 0.0f, star_1);
    		   
    DrawTexturePro(textures->star, src_star, (Rectangle){ circle.x - 36
    		   + space, star_rec.y - 65, star_rec.width, star_rec.height },
    		   (Vector2){0, 0}, 0.0f, star_2);
    		   
    DrawTexturePro(textures->star, src_star, (Rectangle){ star_rec.x + 175 +
    		   space, star_rec.y, star_rec.width, star_rec.height },
               (Vector2){0, 0}, 0.0f, star_3);
}

void mx_draw_text_score(int space, Rectangle level_rec, Vector2 circle,
                        char *level, char *time) {
	Vector2 text_level = MeasureTextEx(mx_get_custom_font(), level, 40, 3);
	Vector2 text_size = MeasureTextEx(mx_get_custom_font(), "The best score", 40, 2);
	Vector2 text_time = MeasureTextEx(mx_get_custom_font(), time, 40, 3);
    Vector2 text_level_pos = {
        circle.x - text_level.x / 2,
        level_rec.y + level_rec.height * 0.62
    };
    Vector2 text_pos = {
    	circle.x - text_size.x / 2,
        level_rec.y + level_rec.height * 0.75
    };
    Vector2 text_time_pos = {
        circle.x - text_time.x / 2,
        level_rec.y + level_rec.height * 0.83
    };	       
    DrawTextEx(mx_get_custom_font(), level, (Vector2)
    	       { text_level_pos.x + space, text_level_pos.y },
    	       game_config.font_size_paragraph + 20, 3, WHITE); 
    	       
    DrawTextEx(mx_get_custom_font(), "The best score", (Vector2)
    	       { text_pos.x + space, text_pos.y },
    	       game_config.font_size_paragraph + 20, 2, WHITE);
    	       
    DrawTextEx(mx_get_custom_font(), time, (Vector2)
    	       { text_time_pos.x + space, text_time_pos.y },
    	       game_config.font_size_paragraph + 20, 3, WHITE);
}

void mx_draw_level(int space, int star, t_game_textures *textures,
                   Texture2D map_image, Vector2 circle) {
    
    float main_corner = 0.3f;
    float small_corner = 0.52f;
    int segments = 10;
    Rectangle main_rec = { 150, 250, 400, 450 };
    Rectangle small_rec = { 150, 249, 400, 225 };
    
    DrawRectangleRounded((Rectangle){ main_rec.x + space, main_rec.y,
    				      main_rec.width, main_rec.height },
    				      main_corner, segments,
    				      custom_colors.level_rectangle_color);
    Rectangle src_image = { 0, 0, map_image.width, map_image.height };
    
    DrawTexturePro(map_image, src_image, (Rectangle){ small_rec.x
    		   + space, small_rec.y, small_rec.width, small_rec.height },
    		   (Vector2){0, 0}, 0.0f, WHITE);
    		   
    DrawRectangleRounded((Rectangle){ small_rec.x + space, small_rec.y,
    				      small_rec.width, small_rec.height },
    				      small_corner, segments, custom_colors.tonedreview_color);
    
    DrawCircleV((Vector2) { circle.x + space, circle.y }, 50,
    			    custom_colors.circle_color);
    DrawCircleLinesV((Vector2) { circle.x + space, circle.y }, 50,
    				 custom_colors.circle_stroke_color);
    
    Rectangle play_button_rec = { circle.x - 18, circle.y - 25, 45, 50 };
    Rectangle src_play_button = { 0, 0, textures->play_button.width,
    			    textures->play_button.height };
    			    
    Color active_play = WHITE;
    DrawTexturePro(textures->play_button, src_play_button,
    		   (Rectangle){ play_button_rec.x + space,
               play_button_rec.y, play_button_rec.width,
               play_button_rec.height }, (Vector2){0, 0},
               0.0f, active_play);
    mx_draw_stars(space, star, textures, circle);
}

void mx_toned_rect(int space) {
	Rectangle main_rec = { 150, 249, 400, 450 };
	float main_corner = 0.3f;
	int segments = 10;
	DrawRectangleRounded((Rectangle){ main_rec.x + space, main_rec.y,
						 main_rec.width, main_rec.height },main_corner,
						 segments, custom_colors.nonactive_level_color);
}

Rectangle mx_draw_back_button(t_game_textures *textures) {
	int text_width = MeasureText("BACK", game_config.font_size_paragraph + 50);
	int button_height = 80;
	int icon_width = textures->exit.width ;
	int icon_height = textures->exit.height ;
	int button_width = icon_width + text_width + 80;
	Rectangle back_button = { 30, 40, button_width, button_height };
	Rectangle back_text_rect = { back_button.x + textures->arrow.width + 5,
					  back_button.y, text_width, button_height };

	Rectangle back_rect = { back_button.x , back_button.y + (button_height -
				  icon_height) / 2, icon_width, icon_height };

	DrawTexturePro(textures->arrow, (Rectangle){0, 0, textures->arrow.width,
			   textures->arrow.height}, back_rect, (Vector2){0, 0},
			   0.0f, WHITE);

	Vector2 text_pos = { back_text_rect.x, back_text_rect.y - 10};
	DrawTextEx(mx_get_custom_font(), "BACK", text_pos, game_config.font_size_paragraph + 70, 3, WHITE);
    return back_button;
}

Rectangle mx_draw_settings_icon(t_game_textures *textures) {
	int gear_size = 115;
	Rectangle gear_rect = { game_config.screen_width - gear_size - 30,
                           20, gear_size, gear_size };
	DrawTexturePro(textures->settings, (Rectangle){ 0, 0,
			   textures->settings.width, textures->settings.height },
			   gear_rect, (Vector2){0, 0}, 0.0f, WHITE);
    return gear_rect;
}

void mx_draw_arrow(Texture2D arrow, Rectangle arrow_rec) {
	DrawTexturePro(arrow, (Rectangle) { 0, 0, arrow.width, arrow.height },
                   arrow_rec, (Vector2) { 0, 0 }, 0.0f, WHITE);
}
