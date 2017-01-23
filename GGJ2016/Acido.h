#ifndef ACIDO_H
#define ACIDO_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

using namespace sf;

class Acido: public Sprite {
	Texture textura_acido;
	Vector2f mov;
	Clock anim;
	
public:
	Acido();
	~Acido();
	void Actualizar(float dt);
	void setVelocidad(float horizontal,float vertical);
};

#endif

