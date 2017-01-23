#ifndef TIMMY_H
#define TIMMY_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

using namespace sf;

class Timmy: public Sprite {
	Texture textura_timmy;
	Clock reloj_anim_timmy;
	Vector2f mov;
public:
	Timmy();
	~Timmy();
	void setVelocidad(float h, float vertical);
	void Actualizar(float dt);
	void Avanzar();
};

#endif

