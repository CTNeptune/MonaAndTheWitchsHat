#pragma bank 2
#include "SpriteCauldron.h"
#include "ZGBMain.h"
#include "SpriteSilverware.h"

UINT8 bank_SPRITE_CAULDRON = 2;

#include "SpriteManager.h"
struct CauldronInfo {
    INT8 vy;
    INT8 vx;
    INT8 spitTimer;
    INT8 spitResetTimer;
    INT8 toIdleTimer;
    INT8 idleResetTimer;
    INT8 silverwareVX;
    INT8 hasSpit;
};
extern UINT8 isPaused;
const UINT8 cauldronAnim[] = {3, 0, 1, 2};
void Start_SPRITE_CAULDRON() {
    struct CauldronInfo* cauldronData = (struct CauldronInfo*)THIS->custom_data;
    cauldronData->spitResetTimer = 60;
    cauldronData->spitTimer = cauldronData->spitResetTimer;
    cauldronData->idleResetTimer = 25;
    cauldronData->toIdleTimer = cauldronData->idleResetTimer;
    cauldronData->hasSpit = 0;
    SetSpriteAnim(THIS, cauldronAnim, 0);
}

void Update_SPRITE_CAULDRON() {
    struct CauldronInfo* cauldronData = (struct CauldronInfo*)THIS->custom_data;
    if(!isPaused){
        if(cauldronData->spitTimer){
            cauldronData->spitTimer -= 1u;
        }
        if(!cauldronData->spitTimer){
            THIS->anim_speed = 15;
        }
        if(THIS->current_frame == 2 && cauldronData->idleResetTimer){
            THIS->anim_speed = 0;
            if(!cauldronData->hasSpit){
                SpriteManagerAdd(SPRITE_SILVERWARE, THIS->x, THIS->y);
                cauldronData->hasSpit++;
            }
            cauldronData->idleResetTimer -= 1u;
            if(!cauldronData->idleResetTimer){
                cauldronData->spitTimer = cauldronData->spitResetTimer;
                cauldronData->idleResetTimer = cauldronData->toIdleTimer;
                cauldronData->hasSpit = 0;
                THIS->current_frame = 0;
            }
        }
    }
}

void Destroy_SPRITE_CAULDRON() {
}