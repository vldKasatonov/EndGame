#include "../inc/header.h"

void drawStars(int space, int star, GameTextures *textures, Vector2 circle) {
    Rectangle starRec = { 225, 390, 75, 75 };
    Rectangle srcStar = { 0, 0, textures->star.width,
    		   	 textures->star.height };
    Color star1 = customColors.nonactiveStarColor;
    Color star2 = customColors.nonactiveStarColor;
    Color star3 = customColors.nonactiveStarColor;
    switch(star) {
        case 1:
            star1 = customColors.activeStarColor;
            break;
        case 2:
            star1 = customColors.activeStarColor;
            star2 = customColors.activeStarColor;
            break;
        case 3:
            star1 = customColors.activeStarColor;
            star2 = customColors.activeStarColor;
            star3 = customColors.activeStarColor;
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

void drawText(int space, Rectangle levelRec, Vector2 circle, char *level, char *time) {
    int textTimeWidth = MeasureText("00:00", gameConfig.fontSizeParagraph + 30);
    int textLevelWidth = MeasureText(level, gameConfig.fontSizeParagraph + 20);
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
    DrawTextEx(GetCustomFont(), level, (Vector2)
    	       { textLevelPos.x + space, textLevelPos.y },
    	       gameConfig.fontSizeParagraph + 20, 3, WHITE); 
    	       
    DrawTextEx(GetCustomFont(), "The best score", (Vector2)
    	       { textPos.x + space, textPos.y },
    	       gameConfig.fontSizeParagraph + 20, 2, WHITE);
    	       
    DrawTextEx(GetCustomFont(), time, (Vector2)
    	       { textTimePos.x + space, textTimePos.y },
    	       gameConfig.fontSizeParagraph + 20, 3, WHITE);
}

void drawLevel(int space, int star,
		      GameTextures *textures, Texture2D map_image, Vector2 circle) {    
    
    float mainCorner = 0.3f;
    float smallCorner = 0.52f;
    int segments = 10;
    Rectangle mainRec = { 150, 250, 400, 450 };
    Rectangle smallRec = { 150, 249, 400, 225 };
    
    DrawRectangleRounded((Rectangle){ mainRec.x + space, mainRec.y,
    				      mainRec.width, mainRec.height },
    				      mainCorner, segments,
    				      customColors.levelRectangleColor);
    Rectangle srcImage = { 0, 0, map_image.width, map_image.height };
    
    DrawTexturePro(map_image, srcImage, (Rectangle){ smallRec.x
    		   + space, smallRec.y, smallRec.width, smallRec.height },
    		   (Vector2){0, 0}, 0.0f, WHITE);
    		   
    DrawRectangleRounded((Rectangle){ smallRec.x + space, smallRec.y,
    				      smallRec.width, smallRec.height },
    				      smallCorner, segments, customColors.tonedPreviewColor);
    
    DrawCircleV((Vector2) { circle.x + space, circle.y }, 50,
    			    customColors.circleColor);
    DrawCircleLinesV((Vector2) { circle.x + space, circle.y }, 50,
    				 customColors.circleStrokeColor);
    
    Rectangle playButton = { circle.x - 18, circle.y - 25, 45, 50 };
    Rectangle srcPlayButton = { 0, 0, textures->play_button.width,
    			    textures->play_button.height };
    			    
    Color active_play = WHITE;
    DrawTexturePro(textures->play_button, srcPlayButton,
    		   (Rectangle){ playButton.x + space, playButton.y,
    		   playButton.width, playButton.height },
    		   (Vector2){0, 0}, 0.0f, active_play);
    drawStars(space, star, textures, circle);
}

void tonedRect (int space) {
	Rectangle mainRec = { 150, 249, 400, 450 };
	float mainCorner = 0.3f;
	int segments = 10;
	DrawRectangleRounded((Rectangle){ mainRec.x + space, mainRec.y,
						  mainRec.width, mainRec.height },mainCorner,
						  segments, customColors.nonactiveLevelColor);
}
