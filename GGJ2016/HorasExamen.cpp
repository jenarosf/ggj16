#include "HorasExamen.h"
#include <sstream>

using namespace sf;
using namespace std;

HorasExamen::HorasExamen() {
	tiempo_actual = 6;
	fuente.loadFromFile("Fonts/pixelmix.ttf"); //CAMBIAR FUENTE 
	text_tiempo.setFont(fuente);
	text_tiempo.setCharacterSize(50);
	text_tiempo.setColor(Color::Red);
	text_tiempo.setPosition(1190, 630); 
	texto.setFont(fuente);
	texto.setCharacterSize(25);
	texto.setColor(Color::White);
	texto.setPosition(900,630);
}

HorasExamen::~HorasExamen() {
	
}
void HorasExamen:: QuitarTiempo() {
	tiempo_actual = tiempo_actual - 1;
}

void HorasExamen::VerTiempo(RenderWindow& window){
	stringstream var1;
	var1<<tiempo_actual;
	text_tiempo.setString(var1.str());
	texto.setString("HORAS RESTANTES\n PARA EL EXAMEN: ");
	window.draw(text_tiempo);
	window.draw(texto);
}
