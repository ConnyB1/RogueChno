#pragma once

/*
	Gameplay speed = 25 ticks/sec
*/

#define WIDTH 1024
#define HEIGHT 500

#define playerTexture "resources/sprites/playerShip.png"
#define playerHP 10
#define playerBulletSpeed 30

#define enemyTexture "resources/sprites/enemyShip.png"
#define enemyHP 5
#define enemySpeed -3
#define enemyBulletSpeed -15

#define bulletHP 1

#define normalBulletTexture "resources/sprites/blueLaser.png"
#define shootGunBulletTexture "resources/sprites/shootGunBullet.png"
#define enemyBulletTexture "resources/sprites/redLaser.png"


#define powerUpSPD 6
#define bonusHPTexture "resources/sprites/bonusHP.png"
#define enchanceAttackTexture "resources/sprites/enchanceATK.png"
#define explosionTexture "resources/sprites/explosion.png"

#define titleScreenTexture "resources/sprites/menu.png"
#define endScreenTexture "resources/sprites/ending.png"
#define icon "resources/sprites/icono.png"
#define backgroundTexture "resources/sprites/background2.jpg"

#define soundChannel 5
#define fireSound "resources/sound/laser.ogg"
#define explosionSound "resources/sound/explosion.ogg"
#define bgSound "resources/sound/background.mp3"
#define btSound "resources/sound/button.ogg"	

enum {
	pPlane,
	ePlane,
	ePlane2,
	eBullet,
	shipDebris,
	bonusHP,
	enchanceATK,
	enchanceSPD
};

enum {
	normalBullet,
	shootGunBullet,
};

enum {
	CH_MUSIC,
	CH_MENU,
	CH_PLAYER,
	CH_ENEMY,
	CH_OTHER
};

enum {
	SOUND_FIRE,
	SOUND_EXPLOSION,
	SOUND_BUTTON
};