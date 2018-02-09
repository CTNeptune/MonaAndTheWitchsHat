#pragma bank 2
#include "SpriteBroom.h"
#include "ZGBMain.h"
UINT8 bank_SPRITE_BROOM = 2;

#include "SpriteManager.h"
struct BroomInfo {
    INT8 vy;
    INT8 yResetTime;
    INT8 yTime;
    INT8 pauseResetTime;
    INT8 pauseTime;
};
extern UINT8 isPaused;
const UINT8 broomAnim[] = {1, 0};
void Start_SPRITE_BROOM() {
    struct BroomInfo* data = (struct BroomInfo*)THIS->custom_data;
    data->yResetTime = 60u;
    data->yTime = data->yResetTime;
    data->pauseResetTime = 30u;
    data->pauseTime = data->pauseResetTime;
	data->vy = 1u;
    SetSpriteAnim(THIS, broomAnim, 0);
}

void Update_SPRITE_BROOM() {
    struct BroomInfo* data = (struct BroomInfo*)THIS->custom_data;
    if(!isPaused){
        if(data->yTime){
        data->yTime -= 1u;
        TranslateSprite(THIS, 0, data->vy);
        }
        if(!data->yTime){
            data->pauseTime -= 1u;
            if(!data->pauseTime){
                data->vy = -data->vy;
                data->yTime = data->yResetTime;
                data->pauseTime = data->pauseResetTime;
            }
        }
    }
}

void Destroy_SPRITE_BROOM() {
}