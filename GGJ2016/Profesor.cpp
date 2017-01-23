#include "Profesor.h"

Profesor::Profesor() {
	textura_profesor.loadFromFile("Sprites/profesor.png");
	setTexture(textura_profesor);
	setOrigin(15,15);
	setPosition(-300,-300);
	setTextureRect(IntRect(0,0,30,30));
	setScale(10,10);
}

Profesor::~Profesor() {
	
}

void Profesor::Actualizar(float dt){
	move(mov*dt);
	if(reloj_anim_profesor.getElapsedTime().asSeconds() > 0.0 && reloj_anim_profesor.getElapsedTime().asSeconds() < 0.1 ){
		setTextureRect(IntRect(0,0,30,30));
	}
	if(reloj_anim_profesor.getElapsedTime().asSeconds() > 0.1 && reloj_anim_profesor.getElapsedTime().asSeconds() < 0.2 ){
		setTextureRect(IntRect(30,0,30,30));
	}
	if(reloj_anim_profesor.getElapsedTime().asSeconds() > 0.2 && reloj_anim_profesor.getElapsedTime().asSeconds() < 0.3 ){
		setTextureRect(IntRect(60,0,30,30));
	}
	if(reloj_anim_profesor.getElapsedTime().asSeconds() > 0.3 && reloj_anim_profesor.getElapsedTime().asSeconds() < 0.4 ){
		setTextureRect(IntRect(90,0,30,30));
	}
	if(reloj_anim_profesor.getElapsedTime().asSeconds() > 0.4) reloj_anim_profesor.restart();
}

void Profesor::setVelocidad(float horizontal, float vertical){
	mov.x = horizontal;
	mov.y = vertical;
}
