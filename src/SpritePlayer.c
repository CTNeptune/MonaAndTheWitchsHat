#pragma bank 2
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "gbt_player.h"

typedef enum  {
	MONA_STATE_NORMAL,
	MONA_STATE_JUMPING,
	MONA_STATE_FIRE,
    MONA_STATE_END
}MONA_STATE;
MONA_STATE monaState;

extern UINT8 level;
extern UINT8 isPaused;

UINT8 tile_collision;
extern UINT8 hasHat;
UINT8 shootCooldown;

INT16 player_accel_x;
INT16 player_accel_y;

const UINT8 anim_idle[] = {2, 0, 2};
const UINT8 hat_anim_idle[] = {1, 2};
const UINT8 anim_walk[] = {2, 1, 0};
const UINT8 hat_anim_walk[] = {2, 3, 2};
const UINT8 anim_jump[] = {1, 1};
const UINT8 hat_anim_jump[] = {1, 3};
const UINT8 fly_anim[] = {1, 4};

void CheckCollisionTile() {
	switch(tile_collision) {
		case 36u:
			SetState(STATE_GAME);
        break;
        case 39u:
			SetState(STATE_GAME);
        break;
        case 52u:
            level++;
            SetState(STATE_GAME);
        break;
        case 53u:
        case 54u:
            if(level == 4 || level == 6){
                level++;
                SetState(STATE_GAME);
            }
        break;
	}
}
void PlayerMovement(){
    if(level!=8){
        if(KEY_PRESSED(J_LEFT)){
            SPRITE_SET_VMIRROR(THIS);
            tile_collision = TranslateSprite(THIS, -player_accel_x << delta_time, 0);
            CheckCollisionTile();
        }
        if(KEY_PRESSED(J_RIGHT)){
            SPRITE_UNSET_VMIRROR(THIS);
            tile_collision = TranslateSprite(THIS, player_accel_x << delta_time, 0);
            CheckCollisionTile();
        }
        if(monaState == MONA_STATE_NORMAL){
            if(hasHat == 1){
                SetSpriteAnim(THIS, hat_anim_walk, 15);
            }else{
                SetSpriteAnim(THIS, anim_walk, 15);
            }
        }
    }else{
        if(KEY_PRESSED(J_UP) && THIS-> y > 8u){
            THIS->y -= player_accel_x << delta_time;
        }
        if(KEY_PRESSED(J_DOWN) && THIS-> y < 120u){
            THIS->y += player_accel_x << delta_time;
        }
        CheckCollisionTile();
    }
}
void Jump(){
    if(monaState != MONA_STATE_JUMPING){
        player_accel_y = -40;
        monaState = MONA_STATE_JUMPING;
        PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);
    }
}
void Shoot(){
    struct Sprite* bullet_sprite = SpriteManagerAdd(SPRITE_BULLET, 0, 0);

	bullet_sprite->flags = THIS->flags;
	if(SPRITE_GET_VMIRROR(THIS)) 
		bullet_sprite->x = THIS->x - 5u;
	else
		bullet_sprite->x = THIS->x + 5u; 
	bullet_sprite->y = THIS->y + 1u;

    shootCooldown = 60u;
}
void Start_SPRITE_PLAYER() {
    if(level == 0){
        level++;
        SetState(STATE_GAME);
    }
    
    scroll_target = THIS;
    THIS->coll_x = 2;
	THIS->coll_y = 0;
	THIS->coll_w = 12;
	THIS->coll_h = 16;
    player_accel_x = 1;
    player_accel_y = 0;
    
    if(level != 8){
        monaState = MONA_STATE_NORMAL;
    }else{
        monaState = MONA_STATE_END;
    }
}
void Update_SPRITE_PLAYER() {
    UINT8 i;
    struct Sprite* spr;
    if(!isPaused && monaState != MONA_STATE_END){
        PlayerMovement();
    }
    switch(monaState){
        case MONA_STATE_NORMAL:
            if(KEY_TICKED(J_A) && !isPaused && level != 8){
                Jump();
            }
            if((!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) || isPaused) && level != 8){
                if(hasHat == 1){
                    SetSpriteAnim(THIS, hat_anim_idle, 0);
                }else{
                    SetSpriteAnim(THIS, anim_idle, 0);
                }
            }
            if((player_accel_y >> 4) > 1 && level != 8) {
				monaState = MONA_STATE_JUMPING;
			}
            if(THIS->x > scroll_x + 16u && level == 8){
                THIS->x -= 1u;
            }
            if(THIS->x < scroll_x + 16u && level == 8){
                THIS->x = scroll_x + 16u;
            }
        break;
        case MONA_STATE_JUMPING:
            if(hasHat == 1){
                SetSpriteAnim(THIS, hat_anim_jump, 0);
            }else{
                SetSpriteAnim(THIS, anim_jump, 0);
            }
            if((player_accel_y < 0) && !KEY_PRESSED(J_A)) {
				player_accel_y = 0;
			}
        case MONA_STATE_END:
            if(level == 8 && !isPaused){
                SetSpriteAnim(THIS, fly_anim, 0);
                TranslateSprite(THIS, player_accel_x << delta_time, 0);
                if(THIS->y > 40u){
                    THIS->y--;
                }
                if(THIS->x >= 168u){
                    monaState = MONA_STATE_NORMAL;
                    hasHat = 1;
                }
            }
        break;
    }
#ifndef DEBUG_CONTROLS
    if(isPaused){
        player_accel_y = 0;
    }
    if(player_accel_y < 60 && !isPaused && level != 8) {
        player_accel_y += 2 >> delta_time;
    }
    if(TranslateSprite(THIS,0,(player_accel_y >> (-4 << delta_time)))){
        player_accel_y = 0;
    }
    tile_collision = TranslateSprite(THIS, 0, (player_accel_y >> (4 << delta_time)));
    CheckCollisionTile();
    if(!tile_collision && delta_time != 0 && player_accel_y < 40 && !isPaused) {
        player_accel_y += 2 >> delta_time;
        tile_collision = TranslateSprite(THIS, 0, (player_accel_y >> 4));
    }
    if(tile_collision && !TranslateSprite(THIS,0,(player_accel_y >> -4))) {
        player_accel_y = 0;
        if(monaState == MONA_STATE_JUMPING) {
            SetSpriteAnim(THIS, anim_idle, 15);
            monaState = MONA_STATE_NORMAL;
        }
    }
#endif
    SPRITEMANAGER_ITERATE(i, spr){
        switch(spr->type){
            case SPRITE_BARREL:
            case SPRITE_SKELTAL:
                if(CheckCollision(THIS,spr)){
                    if(THIS->y + 12 < spr->y){
                        player_accel_y = -30;
                        SpriteManagerRemove(i);
                    }else{
                        SetState(STATE_GAME);
                    }
                }
            break;
            case SPRITE_SKULL:
            case SPRITE_CAULDRON:
            case SPRITE_SILVERWARE:
                if(CheckCollision(THIS,spr)){
                    SetState(STATE_GAME);
                }
            break;

            case SPRITE_BROOM:
                if(CheckCollision(THIS,spr) && player_accel_y > 10){
                    if(THIS->y + 6 < spr->y){
                        monaState = MONA_STATE_NORMAL;
                        THIS->y = spr->y-10;
                        player_accel_y = 30;
                    }
                }
            break;
        }
    }
    if(shootCooldown && !isPaused) {
        shootCooldown -= 1u;
    } else {
        if(KEY_TICKED(J_B) && hasHat == 1 && !isPaused) {
            Shoot();
        }
    }
}
void Destroy_SPRITE_PLAYER() {
}