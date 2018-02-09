#pragma bank 2
#include "StateLevel1.h"
UINT8 bank_STATE_LEVEL1 = 2;

#include "..\res\src\tiles.h"
#include "..\res\src\map1.h"
#include "..\res\src\font.h"


#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

UINT8 collision_tiles[] = {1, 0};

extern UINT8 n_sprite_types;
void Start_STATE_LEVEL1() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	//scroll_target = //SpriteManagerAdd(SPRITE_PLAYER, 50, 90);
    //SpriteManagerAdd(SPRITE_ENEMY, 70, 50);
	//SpriteManagerAdd(SPRITE_BARREL, 20, 20);
	//SpriteManagerAdd(SPRITE_SKELTAL, 20, 120);
	//SpriteManagerAdd(SPRITE_SILVERWARE, 20,100);
	InitScrollTiles(0, 9, tiles, 3);
	InitScroll(map1Width, map1Height, map1, collision_tiles, 0, 3);
	SHOW_BKG;
}

void Update_STATE_LEVEL1() {
}