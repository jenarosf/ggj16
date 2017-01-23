#include "Acido.h"
#include <cstdlib>
#include <ctime>

Acido::Acido() {
	textura_acido.loadFromFile("Sprites/acido.png");
	setTexture(textura_acido);
	srand(time(0));
	setRotation(rand()%360);
	setOrigin(20,20);
}

Acido::~Acido() {
	
}

void Acido::Actualizar(float dt){
	move(mov * dt);
	if(anim.getElapsedTime().asSeconds() > 0.01 ){
		rotate(10);
		anim.restart();
	}
}

void Acido::setVelocidad(float horizontal, float vertical){
	mov.x = horizontal;
	mov.y = vertical;
}
