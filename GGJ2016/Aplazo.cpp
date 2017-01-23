#include "Aplazo.h"

Aplazo::Aplazo() {
	textura_aplazo.loadFromFile("Sprites/aplazo.png");
	setTexture(textura_aplazo);
	
}

Aplazo::~Aplazo() {
	
}

void Aplazo::Actualizar(float dt){
	move(mov * dt);
}
void Aplazo::setVelocidad(float horizontal, float vertical){
	mov.x = horizontal;
	mov.y = vertical;
}
