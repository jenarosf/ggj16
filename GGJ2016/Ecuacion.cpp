#include "Ecuacion.h"

Ecuacion::Ecuacion() {
	ec1.loadFromFile("Sprites/ecuaciones.png");
	setTexture(ec1);
	
	setTextureRect(IntRect(0,0,50,50));
	setOrigin(20,20);
	anim.restart();
	setPosition(-300,-300);
}

Ecuacion::~Ecuacion() {
	
}

void Ecuacion::Actualizar() {
	
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

void Ecuacion::Posicion() {
	setPosition(rand()% 800, 100 + rand() % 375);
}
void Ecuacion::PosicionErr(){
	setPosition(-300,-300);
}
