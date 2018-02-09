#pragma bank 2
#include "SpriteSkull.h"
UINT8 bank_SPRITE_SKULL = 2;

#include "SpriteManager.h"
struct SkullInfo {
    INT8 vy;
    INT8 vx;
    INT8 yResetTime;
    INT8 yTime;
    INT8 pauseResetTime;
    INT8 pauseTime;
};

extern UINT8 isPaused;
const UINT8 skullAnim[] = {2, 0, 1};
void Start_SPRITE_SKULL() {
    struct SkullInfo* data = (struct SkullInfo*)THIS->custom_data;
    data->yResetTime = 20;
    data->yTime = data->yResetTime;
    data->pauseResetTime = 2;
    data->pauseTime = data->pauseResetTime;
	data->vy = 1;
    data->vx = -1;
    THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 7;
	THIS->coll_h = 11;
    SetSpriteAnim(THIS, skullAnim, 5);
}

void Update_SPRITE_SKULL() {
    struct SkullInfo* data = (struct SkullInfo*)THIS->custom_data;
    if(!isPaused){
        if(data->yTime > 0){
            data->yTime -= (1 << delta_time);
            //TranslateSprite(THIS, data->vx, data->vy);
            THIS->x += data->vx << delta_time;
            THIS->y += data->vy << delta_time;
        }
        if(data->yTime <= 0){
            data->pauseTime -= (1 << delta_time);
            if(data->pauseTime <= 0){
                data->vy = -data->vy;
                data->yTime = data->yResetTime;
                data->pauseTime = data->pauseResetTime;
            }
        }
    }
}

void Destroy_SPRITE_SKULL() {
}