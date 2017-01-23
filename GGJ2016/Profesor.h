#ifndef PROFESOR_H
#define PROFESOR_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

using namespace sf;

class Profesor:public Sprite {
	Texture textura_profesor;
	Vector2f mov;
	Clock reloj_anim_profesor;
public:
	Profesor();
	~Profesor();
	void Actualizar(float dt);
	void setVelocidad(float horizontal,float vertical);
};

#endif

