#include "../inc/header.h"

void mx_draw_stars(int space, int star, t_game_textures *textures, Vector2 circle) {
    Rectangle starRec = { 225, 390, 75, 75 };
    Rectangle srcStar = { 0, 0, textures->star.width,
    		   	 textures->star.height };
    Color star1 = custom_colors.nonactive_star_color;
    Color star2 = custom_colors.nonactive_star_color;
    Color star3 = custom_colors.nonactive_star_color;
    switch(star) {
        case 1:
            star1 = custom_colors.active_star_color;
            break;
        case 2:
            star1 = custom_colors.active_star_color;
            star2 = custom_colors.active_star_color;
            break;
        case 3:
            star1 = custom_colors.active_star_color;
            star2 = custom_colors.active_star_color;
            star3 = custom_colors.active_star_color;
            break;
        default: 
            break;
    }
    DrawTexturePro(textures->star, srcStar, (Rectangle){ starRec.x + space,
    		   starRec.y, starRec.width, starRec.height }, (Vector2){0, 0},
    		   0.0f, star1);
    		   
    DrawTexturePro(textures->star, srcStar, (Rectangle){ circle.x - 36
    		   + space, starRec.y - 65, starRec.width, starRec.height },
    		   (Vector2){0, 0}, 0.0f, star2);
    		   
    DrawTexturePro(textures->star, srcStar, (Rectangle){ starRec.x + 175 +
    		   space, starRec.y, starRec.width, starRec.height }, (Vector2)
    		   {0, 0}, 0.0f, star3);
}

void mx_draw_text(int space, Rectangle levelRec, Vector2 circle, char *level, char *time) {
    int textTimeWidth = MeasureText("00:00", game_config.font_size_paragraph + 30);
    int textLevelWidth = MeasureText(level, game_config.font_size_paragraph + 20);
    Vector2 textLevelPos = {
        levelRec.x + 195 - textLevelWidth / 2,
        levelRec.y + levelRec.height * 0.62
    };
    Vector2 textPos = {
        levelRec.x + 49,
        levelRec.y + levelRec.height * 0.75
    };
    Vector2 textTimePos = {
        circle.x - textTimeWidth / 2 - 5,
        levelRec.y + levelRec.height * 0.83
    };	       
    DrawTextEx(mx_get_custom_font(), level, (Vector2)
    	       { textLevelPos.x + space, textLevelPos.y },
    	       game_config.font_size_paragraph + 20, 3, WHITE); 
    	       
    DrawTextEx(mx_get_custom_font(), "The best score", (Vector2)
    	       { textPos.x + space, textPos.y },
    	       game_config.font_size_paragraph + 20, 2, WHITE);
    	       
    DrawTextEx(mx_get_custom_font(), time, (Vector2)
    	       { textTimePos.x + space, textTimePos.y },
    	       game_config.font_size_paragraph + 20, 3, WHITE);
}

void mx_draw_level(int space, int star,
		      t_game_textures *textures, Texture2D map_image, Vector2 circle) {    
    
    float mainCorner = 0.3f;
    float smallCorner = 0.52f;
    int segments = 10;
    Rectangle mainRec = { 150, 250, 400, 450 };
    Rectangle smallRec = { 150, 249, 400, 225 };
    
    DrawRectangleRounded((Rectangle){ mainRec.x + space, mainRec.y,
    				      mainRec.width, mainRec.height },
    				      mainCorner, segments,
    				      custom_colors.level_rectangle_color);
    Rectangle srcImage = { 0, 0, map_image.width, map_image.height };
    
    DrawTexturePro(map_image, srcImage, (Rectangle){ smallRec.x
    		   + space, smallRec.y, smallRec.width, smallRec.height },
    		   (Vector2){0, 0}, 0.0f, WHITE);
    		   
    DrawRectangleRounded((Rectangle){ smallRec.x + space, smallRec.y,
    				      smallRec.width, smallRec.height },
    				      smallCorner, segments, custom_colors.tonedreview_color);
    
    DrawCircleV((Vector2) { circle.x + space, circle.y }, 50,
    			    custom_colors.circle_color);
    DrawCircleLinesV((Vector2) { circle.x + space, circle.y }, 50,
    				 custom_colors.circle_stroke_color);
    
    Rectangle playButton = { circle.x - 18, circle.y - 25, 45, 50 };
    Rectangle srcPlayButton = { 0, 0, textures->play_button.width,
    			    textures->play_button.height };
    			    
    Color active_play = WHITE;
    DrawTexturePro(textures->play_button, srcPlayButton,
    		   (Rectangle){ playButton.x + space, playButton.y,
    		   playButton.width, playButton.height },
    		   (Vector2){0, 0}, 0.0f, active_play);
    mx_draw_stars(space, star, textures, circle);
}

void mx_toned_rect (int space) {
	Rectangle mainRec = { 150, 249, 400, 450 };
	float mainCorner = 0.3f;
	int segments = 10;
	DrawRectangleRounded((Rectangle){ mainRec.x + space, mainRec.y,
						  mainRec.width, mainRec.height },mainCorner,
						  segments, custom_colors.nonactive_level_color);
}
