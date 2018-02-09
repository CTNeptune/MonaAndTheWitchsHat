#pragma bank 2
#include "SpriteSkeltal.h"
UINT8 bank_SPRITE_SKELTAL = 2;

#include "SpriteManager.h"
struct SkeltalInfo {
    INT8 vy;
    INT8 vx;
    INT8 xTime;
    INT8 xResetTime;
};

const UINT8 skeltalAnim[] = {2, 0, 1};
extern UINT8 isPaused;
void Start_SPRITE_SKELTAL() {
    struct SkeltalInfo* data = (struct SkeltalInfo*)THIS->custom_data;
    data->xResetTime = 20;
    data->vx = -1;
    data->xTime = data->xResetTime;
    SetSpriteAnim(THIS, skeltalAnim, 10);
}

void Update_SPRITE_SKELTAL() {
    struct SkeltalInfo* data = (struct SkeltalInfo*)THIS->custom_data;
    //TranslateSprite(THIS, data->vx, 0);
    data->xTime--;
    if(!isPaused){
        if(TranslateSprite(THIS, data->vx, 0)){
            data->vx = -data->vx;
            if(SPRITE_GET_VMIRROR(THIS)){
                SPRITE_UNSET_VMIRROR(THIS);
            }else{
                SPRITE_SET_VMIRROR(THIS);
            }
            //data->xTime = data->xResetTime;
        }
    }
}

void Destroy_SPRITE_SKELTAL() {
}