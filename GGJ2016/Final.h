#ifndef FINAL_H
#define FINAL_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

using namespace sf;

class Final: public Sprite {
	Texture textura_final;
	Vector2f mov;
	Clock anim;
public:
	Final();
	~Final();
	void Actualizar(float dt);
	void setVelocidad(float horizontal,float vertical);
	
};

#endif

