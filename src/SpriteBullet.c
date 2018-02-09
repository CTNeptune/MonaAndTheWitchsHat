#pragma bank 2
#include "SpriteBullet.h"
UINT8 bank_SPRITE_BULLET = 2;

#include "SpriteManager.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "gbt_player.h"

UINT8 bullet_anim[] = {4, 0, 1, 2, 3};
void Start_SPRITE_BULLET() {
	THIS->coll_x = 0u;
	THIS->coll_w = 4u;
	THIS->coll_y = 5u;
	THIS->coll_h = 4u;
    SetSpriteAnim(THIS, bullet_anim, 15);
	PlayFx(CHANNEL_1, 10, 0x2C, 0xD8, 0xF3, 0x62, 0xC7);
}

extern UINT8 scroll_collisions[128];
extern UINT8 isPaused;
extern UINT8 level;
void Update_SPRITE_BULLET() {
	UINT8 i;
	struct Sprite* spr;
	
	if(!isPaused){
		if(SPRITE_GET_VMIRROR(THIS)) {
			THIS->x -= 3 << delta_time;
		} else {
			THIS->x += 3 << delta_time;
		}
	}
	if(scroll_collisions[GetScrollTile((THIS->x + 4)>> 3, (THIS->y + 4) >> 3)] && level != 8) {
		SpriteManagerRemove(THIS_IDX);
		return;
	}
	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_BARREL || spr->type == SPRITE_SKELTAL || spr->type == SPRITE_SKULL) {
			if(CheckCollision(THIS, spr)) {
				SpriteManagerRemove(i);
				SpriteManagerRemove(THIS_IDX);
				break;
			}
		}
	}
}

void Destroy_SPRITE_BULLET() {
}