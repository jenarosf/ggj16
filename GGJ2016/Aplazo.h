#ifndef APLAZO_H
#define APLAZO_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sf;

class Aplazo: public Sprite {
	Texture textura_aplazo;
	Vector2f mov;
public:
	Aplazo();
	~Aplazo();
	void Actualizar(float dt);
	void setVelocidad(float horizontal,float vertical);
};

#endif

