#include "../inc/header.h"

GameConfig gameConfig = {
	1600, // screenWidth
	900, // screenHeight
	300, // buttonWidth
	60,  // buttonHeight
	80,  // fontSizeHeader1
	35,  // fontSizeHeader2
	25,	 // fontSizeHeader3
	20,  // fontSizeParagraph
};

CustomColors customColors = {
    { 241, 129, 59, 255 }, // buttonBackgroundColor
    { 242, 155, 101, 100 }, // menuBackgroundColor
    { 232, 110, 35, 255 }, // musicColor
    { 186, 77, 9, 255 }, // sliderColor
    { 255, 0, 0, 255 }, // redColor
    { 207, 99, 32, 255 }, // level rectangle
    { 217, 105, 35, 255 }, // circle
    { 135, 65, 21, 255 }, // circle stroke
    { 65, 65, 65, 255 }, // nonactive star 
    { 255, 217, 0, 255 }, // active star
    { 0, 0, 0, 0 }, // none
    { 0, 0, 0, 100}, // nonactive level
    { 0, 0, 0, 40}, // toned level preview
};

int levelNumber = 0;
