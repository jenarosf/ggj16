#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


using namespace sf;

class Menu {
	Font fuente_menu, fuente_jugar;
	Text texto_menu, texto_jugar, texto_salir;
	
	Texture textura_fondo;
	Sprite fondo;
	
	Texture textura_anim_fondo;
	Sprite background_anim;
	
	Clock reloj_fuego;
	Texture textura_fuego;
	Sprite fuego;
	
	Clock reloj_historia;
	std::vector<std::string> vector_string;
	Font fuente_historia;
	Text texto_historia;
	std::string s1,s2,s3,s4;
	int cant;
	
	Clock reloj_nube;
	Texture textura_nube;
	Sprite nube;
	
	Clock reloj_timmy;
	Texture textura_timmy;
	Sprite timmy;
	
	Clock reloj_hojas;
	Texture textura_hojas;
	Sprite hojas;
	
	Clock reloj_animacion;
	
	SoundBuffer MusicaComienzo; //hola
	Sound MusicC; //Hola
	
	SoundBuffer MusicaMenu;
	Sound Mmenu;
	
	bool menu, enter,animacion;
	
	void Actualizar(float dt,RenderWindow* v);
	void ActualizarAnimacion(float dt,RenderWindow* v);
	void ProcesarEventos(RenderWindow* v);
	void Dibujar(float dt,RenderWindow* v);
	void DibujarAnimacion(float dt,RenderWindow* v);
public:
	Menu();
	~Menu();
	void Comenzar(RenderWindow* v);
};

#endif

