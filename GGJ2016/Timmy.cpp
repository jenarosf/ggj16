#include "Timmy.h"
#include <iomanip>
#include <iostream>
#include <cmath>

Timmy::Timmy() {
	textura_timmy.loadFromFile("Sprites/timmy.png");
	setTexture(textura_timmy);
	setOrigin(32,32);
	setTextureRect(IntRect(0,0,64,64));
	reloj_anim_timmy.restart();
}

Timmy::~Timmy() {
	
}

void Timmy::setVelocidad(float h, float vertical){
	mov.x = h;
	if(getPosition().y < 530 ) {
		mov.y = vertical+150;
	}else{
		mov.y = vertical;
	}
}

void Timmy::Actualizar(float dt){
	move(mov * dt);
//	mov.x = 0;
//	mov.y = 0;
	if(reloj_anim_timmy.getElapsedTime().asSeconds() > 0.0 && reloj_anim_timmy.getElapsedTime().asSeconds() < 0.2){
		setTextureRect(IntRect(0,0,64,64));
	}
	if(reloj_anim_timmy.getElapsedTime().asSeconds() > 0.2 && reloj_anim_timmy.getElapsedTime().asSeconds() < 0.4){
		setTextureRect(IntRect(64,0,64,64));
	}
	if(reloj_anim_timmy.getElapsedTime().asSeconds() > 0.4 && reloj_anim_timmy.getElapsedTime().asSeconds() < 0.6){
		setTextureRect(IntRect(128,0,64,64));
	}
	if(reloj_anim_timmy.getElapsedTime().asSeconds() > 0.6 && reloj_anim_timmy.getElapsedTime().asSeconds() < 0.8){
		setTextureRect(IntRect(192,0,64,64));
	}
	if(reloj_anim_timmy.getElapsedTime().asSeconds() > 0.8 ) reloj_anim_timmy.restart();
}

