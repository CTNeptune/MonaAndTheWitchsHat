#pragma bank 2
#include "SpriteBarrel.h"
UINT8 bank_SPRITE_BARREL = 2;

#include "SpriteManager.h"
struct BarrelInfo {
    INT8 vy;
    INT8 vx;
    INT8 xTime;
    INT8 xResetTime;
};
extern UINT8 isPaused;
const UINT8 barrelAnim[] = {2, 0, 1};
void Start_SPRITE_BARREL() {
    struct BarrelInfo* data = (struct BarrelInfo*)THIS->custom_data;
    data->xResetTime = 20;
    data->vx = 1;
    data->xTime = data->xResetTime;
    SetSpriteAnim(THIS, barrelAnim, 10);
}

void Update_SPRITE_BARREL() {
    struct BarrelInfo* data = (struct BarrelInfo*)THIS->custom_data;
    if(!isPaused){
        TranslateSprite(THIS, data->vx, 0);
        data->xTime--;
        if(data->xTime == 0){
            data->vx = -data->vx;
            data->xTime = data->xResetTime;
        }
    }
}

void Destroy_SPRITE_BARREL() {
}