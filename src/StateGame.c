#pragma bank 1
#include "StateGame.h"
UINT8 bank_STATE_GAME = 1;

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\map1.h"
#include "..\res\src\map2.h"
#include "..\res\src\map3.h"
#include "..\res\src\map4.h"
#include "..\res\src\font.h"
#include "..\res\src\title.h"
#include "..\res\src\cineTiles.h"
#include "..\res\src\cine.h"
#include "..\res\src\cine1.h"
#include "..\res\src\cine2.h"
#include "..\res\src\cine3.h"
#include "..\res\src\cine4.h"
#include "..\res\src\cine5.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "SpritePlayer.h"
#include "Keys.h"
#include "gbt_player.h"

UINT8 collision_tiles[] = {1, 4, 5, 12, 13, 33, 34, 35, 36, 39, 44, 45, 52, 53, 54, 67, 68, 69, 70, 71, 72, 73, 74, 75,  0};
UINT8 level = 0;
UINT8 hasHat;
UINT8 isPaused;
UINT8 scrollTimer;
UINT16 level4Timer;

extern UINT8* splash_mod_data[];
extern UINT8* textinterlude_mod_data[];
extern UINT8* levela_mod_data[];
extern UINT8* levelb_mod_data[];
extern UINT8* ending_mod_data[];

extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;
	isPaused = 0;
	//level = 6;
	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;
	switch(level){
		case 0:
			InitScrollTiles(0, 100, font, 3);
			InitScroll(TitleWidth, TitleHeight, Title, collision_tiles, 0, 3);
			PlayMusic(splash_mod_data, 4, 0);
		break;
		case 1:
			InitScrollTiles(0, 100, font, 3);
			InitScroll(Cine1Width, Cine1Height, Cine1, collision_tiles, 0, 3);
			PlayMusic(textinterlude_mod_data, 4, 0);
		break;
		case 2:
			hasHat = 0;
			InitScrollTiles(0, 100, tiles, 3);
			InitScroll(map1Width, map1Height, map1, collision_tiles, 0, 3);
			PlayMusic(levela_mod_data, 4, 1);
		break;
		case 3:
			InitScrollTiles(0, 100, font, 3);
			InitScroll(Cine2Width, Cine2Height, Cine2, collision_tiles, 0, 3);
			PlayMusic(textinterlude_mod_data, 4, 0);
		break;
		case 4:
			InitScrollTiles(0, 100, tiles, 3);
			scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 124 << 3, 11 << 3);
			SPRITE_SET_VMIRROR(scroll_target);
			hasHat = 1;
			InitScroll(map2Width, map2Height, map2, collision_tiles, 0, 3);
			//PlayMusic(levela_mod_data, 4, 1);
			PlayMusic(levelb_mod_data, 4, 1);
		break;
		case 5:
			InitScrollTiles(0, 100, font, 3);
			InitScroll(Cine3Width, Cine3Height, Cine3, collision_tiles, 0, 3);
			PlayMusic(textinterlude_mod_data, 4, 0);
		break;
		case 6:
			InitScrollTiles(0, 100, tiles, 3);
			scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 3 << 3, 17 << 3);
			hasHat = 1;
			InitScroll(map3Width, map3Height, map3, collision_tiles, 0, 3);
			PlayMusic(levela_mod_data, 4, 1);
		break;
		case 7:
			InitScrollTiles(0, 100, font, 3);
			InitScroll(Cine4Width, Cine4Height, Cine4, collision_tiles, 0, 3);
			PlayMusic(textinterlude_mod_data, 4, 0);
		break;
		case 8:
			InitScrollTiles(0, 104, tiles, 3);
			InitScroll(map4Width, map4Height, map4, collision_tiles, 0, 3);
			scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 1 << 3, 17 << 3);
			level4Timer = 1800u;
			//PlayMusic(levela_mod_data, 4, 1);
			PlayMusic(levelb_mod_data, 4, 1);
		break;
		case 9:
			InitScrollTiles(0, 100, font, 3);
			InitScroll(Cine5Width, Cine5Height, Cine5, collision_tiles, 0, 3);
			PlayMusic(textinterlude_mod_data, 4, 0);
		break;
		case 10:
			InitScrollTiles(0, 100, CineTiles, 3);
			InitScroll(cineWidth, cineHeight, cine, collision_tiles, 0, 3);
			PlayMusic(ending_mod_data, 4, 0);
		break;
	}
	SHOW_BKG;
}

void Update_STATE_GAME() {
	if(level == 8 && !isPaused){
		if(scroll_target == 0){
			scroll_x += 1u;
		}
		if(scroll_target->x >= 168){
			scroll_target = 0;
			}
		level4Timer -= 1u << delta_time;
		switch(level4Timer){
			case 1500u:
			case 840u:
				SpriteManagerAdd(SPRITE_SKULL, scroll_x + 160, 1 << 3);
			break;
			case 600u:
			case 240u:
				SpriteManagerAdd(SPRITE_SKULL, scroll_x + 160, 3 << 3);
			break;
			case 1080u:
			case 720u:
				SpriteManagerAdd(SPRITE_SKULL, scroll_x + 160, 8 << 3);
			break;
			case 1200u:
			case 960u:
			case 480u:
				SpriteManagerAdd(SPRITE_SKULL, scroll_x + 160, 12 << 3);
			break;
		}
		if(level4Timer <= 0){
			level++;
			SetState(STATE_GAME);
		}
	}
	if(KEY_TICKED(J_START)){
		switch(level){
			case 2:
			case 4:
			case 6:
			case 8:
				isPaused = ~isPaused;
				if(!isPaused){
					gbt_pause(1);
					NR52_REG = 0x80; //Enables sound, you should always setup this first
					NR51_REG = 0xFF; //Enables all channels (left and right)
					NR50_REG = 0x77; //Max volume
				}else{
					gbt_pause(0);
					NR51_REG = 0x00; //Disable all channels (left and right)
					NR50_REG = 0x00; //Lowest volume
				}
			break;
		}
	}
	if(KEY_TICKED(J_A) || KEY_TICKED(J_B) || KEY_TICKED(J_START)){
		switch(level){
			case 0:
			case 1:
			case 3:
			case 5:
			case 7:
			case 9:
				level ++;
				SetState(STATE_GAME);
			break;
			case 10:
				level = 0;
				SetState(STATE_GAME);
			break;
		}
	}
}