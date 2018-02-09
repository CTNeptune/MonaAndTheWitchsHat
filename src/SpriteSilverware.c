#pragma bank 2
#include "SpriteSilverware.h"
#include "rand.h"
UINT8 bank_SPRITE_SILVERWARE = 2;

#include "SpriteManager.h"
struct SilverwareInfo {
    INT8 vy;
    INT8 rnd;
    INT8 rotateTimer;
};

extern UINT8 isPaused;
const UINT8 silverwareAnim[] = {4, 0, 1, 2, 3};
void Start_SPRITE_SILVERWARE() {
    struct SilverwareInfo* data = (struct SilverwareInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, silverwareAnim, 0);
    data->vy = -60;
    data->rnd = rand();
    if(data->rnd < 48){
        THIS->current_frame = 1;
    }else{
        THIS->current_frame = 2;
    }
    THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
}

void Update_SPRITE_SILVERWARE() {
    struct SilverwareInfo* data = (struct SilverwareInfo*)THIS->custom_data;
    if(!isPaused){
        data->vy += 2u;
        if(data->rotateTimer >= 15){
            SPRITE_SET_VMIRROR(THIS);
        }
        if(data->rotateTimer >= 30){
            SPRITE_UNSET_VMIRROR(THIS);
            data->rotateTimer = 0;
        }
        data->rotateTimer += 1u;
        if(TranslateSprite(THIS, 0, (data->vy >> (4u)))){
            SpriteManagerRemoveSprite(THIS);
        }
    }
}

void Destroy_SPRITE_SILVERWARE() {
}