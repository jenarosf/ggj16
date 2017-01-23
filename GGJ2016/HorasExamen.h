#ifndef HORASEXAMEN_H
#define HORASEXAMEN_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class HorasExamen {
private:
	Font fuente;							//Fuente para las horas
	Text text_tiempo;						//Tiempo actual (en letras)
	Text texto;
	unsigned int tiempo_actual;				//Tiempo actual (número)
protected:
public:
	HorasExamen();
	void VerTiempo(RenderWindow& window);		//Método que muestra en pantalla el tiempo
	void QuitarTiempo();									//Método que resta tiempo cuando hay una colision
	void VerTiempo();
	int VerHoras(){return tiempo_actual;};
	~HorasExamen();
};

#endif

