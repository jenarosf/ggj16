#include "Final.h"
#include <iostream>

Final::Final() {
	textura_final.loadFromFile("Sprites/final.png");
	setTexture(textura_final);
	setTextureRect(IntRect(0,0,50,50));
	setOrigin(20,20);
	anim.restart();
}

Final::~Final() {
	
}

void Final::Actualizar(float dt){
	move(mov * dt);
	if(anim.getElapsedTime().asSeconds() > 0 && anim.getElapsedTime().asSeconds() < 0.2 ){
		setTextureRect(IntRect(0,0,50,50));
	}
	if(anim.getElapsedTime().asSeconds() > 0.2 && anim.getElapsedTime().asSeconds() < 0.4 ){
		setTextureRect(IntRect(50,0,50,50));
	}
	if(anim.getElapsedTime().asSeconds() > 0.4 && anim.getElapsedTime().asSeconds() < 0.6 ){
		setTextureRect(IntRect(100,0,50,50));
	}
	if(anim.getElapsedTime().asSeconds() > 0.6 ) anim.restart();
	
}

void Final::setVelocidad(float horizontal, float vertical){
	mov.x = horizontal;
	mov.y = vertical;
}


