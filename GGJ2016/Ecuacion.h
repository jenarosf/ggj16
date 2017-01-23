#ifndef ECUACION_H
#define ECUACION_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

using namespace sf;
using namespace std;

class Ecuacion: public Sprite {
private:
	Texture ec1,ec2,ec3;
	int Variable;
	Clock anim;
protected:
public:
	Ecuacion();
	void Actualizar();
	void Posicion();
	void PosicionErr();
	~Ecuacion();
};

#endif

