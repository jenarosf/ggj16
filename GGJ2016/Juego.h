#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Menu.h"
#include "Timmy.h"
#include <vector>
#include "Final.h"
#include "Acido.h"
#include "Profesor.h"
#include "Aplazo.h"
#include "HorasExamen.h"
#include "Ecuacion.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

using namespace sf;

class Juego {
	RenderWindow* ventana;
	
	Menu menu;
	
	bool comenzar;
	
	Clock reloj_anim_fondo;
	Texture textura_background;
	Sprite background;
	
	Timmy timmy;
	
	Texture textura_hud;
	Sprite hud;
	
	bool aparece_profesor;
	Clock reloj_aparicion_profesor;
	Profesor profesor;
	Clock reloj_tiempo_profesor;
	int disparos_profesor;
	
	std::vector<Aplazo> vector_aplazos;
	Clock reloj_aplazos;
	
	int HorasRestantes;
	HorasExamen Horas;
	
	Clock reloj_aparicion_finales;
	std::vector<Final> vector_finales;
	
	Clock reloj_aparicion_acidos;
	std::vector<Acido> vector_acido;
	
	Texture texture_aplazado;
	Sprite aplazado;
	
	Clock reloj_ecuacion;
	Ecuacion ecuacion;
	int parteEcuacion;
	bool Fin;
	bool parte1,parte2,parte3;
	Texture part1,part2,part3;
	Sprite p1,p2,p3;
	
	int dificultad ;
	
	bool gameover;
	Texture textura_pantallaperder;
	Sprite pantalla_perder;
	Texture textura_pantallawin;
	Sprite pantalla_win;
	
	Clock reloj_historia_perder;
	std::string hp1,hp2,hp3,hp4;
	Font fuente_historia;
	Text historia_perder;
	int cont_historia;
	
	
	SoundBuffer MusicaDesarrollo;
	Sound MusicD;
	
	SoundBuffer MusicaFin;
	Sound MusicF;
	
	SoundBuffer SonidoProfesor;
	Sound SProf;
	
	SoundBuffer SonidoColision;
	Sound SCol;
	
	SoundBuffer SonidoAplazado;
	Sound SApla;
	
	Texture textura_pantallaganar;
	Sprite pantalla_ganar;
	Texture textura_aprobado;
	Sprite aprobado;
	Clock reloj_aprobado;
	
	void Actualizar(float dt);
	void Dibujar(float dt);
	void ProcesarEventos();
	void ProcesarColisiones();
	void Reiniciar();
public:
	Juego();
	~Juego();
	void Comenzar();
};

#endif

