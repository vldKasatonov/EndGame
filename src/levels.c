#include "../inc/header.h"

t_level_data level_data[] = {
	{
		5,
		{{JUICED, APPLE}, {JUICED, APPLE}, {JUICED, APPLE}, {JUICED, APPLE}, {JUICED, APPLE}},
		{
			{ {0, 0, 1225, 75}, BROWN, NONE}, // top wall
			{ {175, 75, 300, 75}, BROWN, NONE}, // top wall
			{ {75, 75, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 250, 75, 20}, LIGHTGRAY, NONE},
			{ {75, 270, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 445, 75, 20}, LIGHTGRAY, NONE},
			{ {75, 465, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 640, 75, 40}, LIGHTGRAY, NONE},
			{ {75, 680, 150, 175}, RED, CASHBOX}, // cash register
			{ {150, 855, 75, 45}, LIGHTGRAY, NONE},
			{ {475, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {475, 225, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {625, 75, 150, 150}, RED, JUICEMAKER}, // squeezer
			{ {775, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {925, 75, 150, 150}, YELLOW, NONE}, // deep fryer
			{ {1075, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {1075, 225, 150, 150}, ORANGE, NONE}, // plase for cutting
			{ {1075, 375, 150, 150}, BLUE, WASHBASIN}, // sink
			{ {1125, 525, 100, 100}, PINK, GARBAGE_CAN}, // garbage
			{ {475, 525, 150, 150}, BLACK, NONE}, // plate
			{ {625, 525, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {775, 525, 150, 150}, ORANGE, SLICING_TABLE}, // plase for cutting
			{ {1235, 0, 365, 150}, MAROON, NONE}, // barn
			{ {1330, 0, 110, 150}, LIGHTGRAY, NONE}, // barn door
			{ {1450, 240, 150, 155}, LIGHTGRAY, APPLE_TREE}, // place for plants
			{ {0, 0, 0, 0}, BLANK, NONE}, // place for plants
			{ {0, 0, 0, 0}, BLANK, NONE}, // place for plants
			{ {0, 0, 0, 0}, BLANK, NONE}, // place for plants
			{ {1225, 0, 10, 675}, BROWN, NONE}, // upper right wall
			{ {1225, 875, 10, 25}, BROWN, NONE}, // lower right wall
			{ {-11, -11, 11, 922}, BLACK, NONE}, // left border
			{ {-11, -11, 1622, 11}, BLACK, NONE}, // bottom border
			{ {1600, -11, 11, 922}, BLACK, NONE}, // right border
			{ {-11, 900, 1622, 11}, BLACK, NONE}, // bottom border
		},
		34
	},
	{
		5,
		{{FRIED, POTATO}, {JUICED, APPLE}, {FRIED, POTATO}, {JUICED, APPLE}, {FRIED, POTATO}},
		{
			{ {0, 0, 1225, 75}, BROWN, NONE}, // top wall
			{ {175, 75, 300, 75}, BROWN, NONE}, // top wall
			{ {75, 75, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 250, 75, 20}, LIGHTGRAY, NONE},
			{ {75, 270, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 445, 75, 20}, LIGHTGRAY, NONE},
			{ {75, 465, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 640, 75, 40}, LIGHTGRAY, NONE},
			{ {75, 680, 150, 175}, RED, CASHBOX}, // cash register
			{ {150, 855, 75, 45}, LIGHTGRAY, NONE},
			{ {475, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {475, 225, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {625, 75, 150, 150}, RED, JUICEMAKER}, // squeezer
			{ {775, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {925, 75, 150, 150}, YELLOW, STOVE}, // deep fryer
			{ {1075, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {1075, 225, 150, 150}, ORANGE, PEELING_TABLE}, // plase for cutting
			{ {1075, 375, 150, 150}, BLUE, WASHBASIN}, // sink
			{ {1125, 525, 100, 100}, PINK, GARBAGE_CAN}, // garbage
			{ {475, 525, 150, 150}, BLACK, NONE}, // plate
			{ {625, 525, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {775, 525, 150, 150}, ORANGE, SLICING_TABLE}, // plase for cutting
			{ {1235, 0, 365, 150}, MAROON, NONE}, // barn
			{ {1330, 0, 110, 150}, LIGHTGRAY, NONE}, // barn door
			{ {1450, 240, 150, 155}, LIGHTGRAY, APPLE_TREE}, // place for plants
			{ {1450, 405, 150, 150}, LIGHTGRAY, POTATO_BED}, // place for plants
			{ {0, 0, 0, 0}, BLANK, NONE}, // place for plants
			{ {0, 0, 0, 0}, BLANK, NONE}, // place for plants
			{ {1225, 0, 10, 675}, BROWN, NONE}, // upper right wall
			{ {1225, 875, 10, 25}, BROWN, NONE}, // lower right wall
			{ {-11, -11, 11, 922}, BLACK, NONE}, // left border
			{ {-11, -11, 1622, 11}, BLACK, NONE}, // bottom border
			{ {1600, -11, 11, 922}, BLACK, NONE}, // right border
			{ {-11, 900, 1622, 11}, BLACK, NONE}, // bottom border
		},
		34
	},
	{
		5,
		{{MIXED, SALAD}, {FRIED, POTATO}, {JUICED, APPLE}, {FRIED, POTATO}, {MIXED, SALAD}},
		{
			{ {0, 0, 1225, 75}, BROWN, NONE}, // top wall
			{ {175, 75, 300, 75}, BROWN, NONE}, // top wall
			{ {75, 75, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 250, 75, 20}, LIGHTGRAY, NONE},
			{ {75, 270, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 445, 75, 20}, LIGHTGRAY, NONE},
			{ {75, 465, 150, 175}, PINK, PICK_UP}, // table for customers
			{ {150, 640, 75, 40}, LIGHTGRAY, NONE},
			{ {75, 680, 150, 175}, RED, CASHBOX}, // cash register
			{ {150, 855, 75, 45}, LIGHTGRAY, NONE},
			{ {475, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {475, 225, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {625, 75, 150, 150}, RED, JUICEMAKER}, // squeezer
			{ {775, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {925, 75, 150, 150}, YELLOW, STOVE}, // deep fryer
			{ {1075, 75, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {1075, 225, 150, 150}, ORANGE, PEELING_TABLE}, // plase for cutting
			{ {1075, 375, 150, 150}, BLUE, WASHBASIN}, // sink
			{ {1125, 525, 100, 100}, PINK, GARBAGE_CAN}, // garbage
			{ {475, 525, 150, 150}, BLACK, PLATE}, // plate
			{ {625, 525, 150, 150}, GREEN, NONE}, // kitchen surface
			{ {775, 525, 150, 150}, ORANGE, SLICING_TABLE}, // plase for cutting
			{ {1235, 0, 365, 150}, MAROON, NONE}, // barn
			{ {1330, 0, 110, 150}, LIGHTGRAY, NONE}, // barn door
			{ {1450, 240, 150, 155}, LIGHTGRAY, APPLE_TREE}, // place for plants
			{ {1450, 405, 150, 150}, LIGHTGRAY, POTATO_BED}, // place for plants
			{ {1450, 570, 150, 150}, LIGHTGRAY, CUCUMBER_BED}, // place for plants
			{ {1450, 735, 150, 150}, LIGHTGRAY, TOMATO_BED}, // place for plants
			{ {1225, 0, 10, 675}, BROWN, NONE}, // upper right wall
			{ {1225, 875, 10, 25}, BROWN, NONE}, // lower right wall
			{ {-11, -11, 11, 922}, BLACK, NONE}, // left border
			{ {-11, -11, 1622, 11}, BLACK, NONE}, // bottom border
			{ {1600, -11, 11, 922}, BLACK, NONE}, // right border
			{ {-11, 900, 1622, 11}, BLACK, NONE}, // bottom border
		},
		34
	},
};
