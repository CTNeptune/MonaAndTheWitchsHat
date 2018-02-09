#pragma bank 1
#include "ZGBMain.h"
UINT8 init_bank = 1;


#include "StateGame.h"
#include "StateLevel1.h"

#include "SpritePlayer.h"
#include "SpriteBarrel.h"
#include "SpriteEnemy.h"
#include "SpriteSkeltal.h"
#include "SpriteBroom.h"
#include "SpriteCauldron.h"
#include "SpriteSilverware.h"
#include "Spriteskull.h"
#include "SpriteBullet.h"

#include "../res/src/player.h"
#include "../res/src/barrel.h"
#include "../res/src/enemy.h"
#include "../res/src/skeltal.h"
#include "../res/src/broom.h"
#include "../res/src/cauldron.h"
#include "../res/src/silverware.h"
#include "../res/src/skull.h"
#include "../res/src/bullet.h"

UINT8 next_state = STATE_GAME;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_GAME);
	INIT_STATE(STATE_LEVEL1);
}

void InitSprites() {
	INIT_SPRITE(SPRITE_PLAYER, player, 3, FRAME_16x16, 4);
    INIT_SPRITE(SPRITE_BARREL, barrel, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_ENEMY,  enemy,  3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_SKELTAL, skeltal, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_BROOM, broom, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_CAULDRON, cauldron, 3, FRAME_16x16, 3);
	INIT_SPRITE(SPRITE_SILVERWARE, silverware, 3, FRAME_16x16, 4);
	INIT_SPRITE(SPRITE_SKULL, skull, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_BULLET, bullet, 3, FRAME_16x16, 4);
}