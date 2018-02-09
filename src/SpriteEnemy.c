#pragma bank 2
#include "SpriteEnemy.h"
UINT8 bank_SPRITE_ENEMY = 2;

#include "SpriteManager.h"
struct EnemyInfo {
    INT8 vy;
    INT8 vx;
};

const UINT8 anim[] = {2, 0, 1};
void Start_SPRITE_ENEMY() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	data->vy = 1;
    data->vx = 1;
    SetSpriteAnim(THIS, anim, 15);
}

void Update_SPRITE_ENEMY() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	if(TranslateSprite(THIS, 0, data->vy)) {
		data->vy = -data->vy;
	}
}

void Destroy_SPRITE_ENEMY() {
}