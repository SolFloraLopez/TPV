#pragma once

using uint = unsigned int;

enum {
	Background1, Background2, Background3, Background4, Background5, Background6,
	ScoreArrowTexture, DigitsTexture, BowTexture, Balloons, ArrowTexture, ButterflyTexture, RewardTexture, BubbleTexture, Button
};

struct infoTexturas
{
	string route;
	int rows;
	int columns;
};

const uint WIN_WIDTH = 800;//
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 15;
const uint FRAME_RATE = 50;
const uint BASE_ARROWS_AMOUNT = 3;
const uint BASE_BUTTERFLY_AMOUNT = 3;
const uint BASE_POINT_MAX = 100;
const uint MAP_AMOUNT = 6;
const double BOW_VELOCITY = 5;
const double BALLOON_VELOCITY = 0.5;
const double ARROW_VELOCITY = 10;
const double BOW_HEIGHT = 61;
const double BOW_WIDTH = 142;//

const infoTexturas INFOTEXT[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},
											{"..\\images\\bg_spring_trees_1.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_01.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_02.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_03.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_04.png", 1, 1},
											{"..\\images\\Arrow2.png", 1, 1},
											{"..\\images\\digits1.png", 1, 10},
											{"..\\images\\Bow2.png", 1, 1},
											{"..\\images\\balloons.png", 7, 6},
											{"..\\images\\Arrow1.png", 1, 1},
											{"..\\images\\butterfly2.png", 4, 10},
											{"..\\images\\rewards.png", 10, 8},
											{"..\\images\\bubble.png", 1, 1},
											{"..\\images\\button.png", 1, 1}
};