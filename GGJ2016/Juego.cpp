#include "Juego.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "Collision.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace Collision;
using namespace sf;

Juego::Juego() {
	ventana = new RenderWindow(VideoMode(1280,720),"GGJ 2016");
	ventana->setVerticalSyncEnabled(false);
	ventana->setKeyRepeatEnabled(false);
	ventana->setMouseCursorVisible(false);
	srand(time(0));
	
	textura_hud.loadFromFile("Sprites/hud.png");
	hud.setTexture(textura_hud);
	hud.setPosition(0,570);
	
	timmy.setPosition(ventana->getSize().x/2,ventana->getSize().y/2);

	textura_background.loadFromFile("Sprites/background.png");
	background.setTexture(textura_background);
	background.setOrigin(20,20);
	
	aparece_profesor = false;
	disparos_profesor = 0;
	reloj_aplazos.restart();
	
	HorasRestantes = 0;
	
	comenzar = false;
	
	texture_aplazado.loadFromFile("Sprites/aplazo.png");
	aplazado.setTexture(texture_aplazado);
	aplazado.setScale(10,10);
	aplazado.setOrigin(77,0);
	aplazado.setPosition(330,200);
	
	parteEcuacion = 0;
	Fin = false;
	parte1= parte2=parte3= false;
	part1.loadFromFile("Sprites/vidachica.png");
	p1.setTexture(part1);
	p1.setPosition(50,630);
	part2.loadFromFile("Sprites/integral.png");
	p2.setTexture(part2);
	p2.setPosition(110,600);
	part3.loadFromFile("Sprites/terceraparte.png");
	p3.setTexture(part3);
	p3.setPosition(500,600);
	
	dificultad = 0;
	textura_pantallaperder.loadFromFile("Sprites/pantalla_perder.png");
	pantalla_perder.setTexture(textura_pantallaperder);
	
	gameover = false;
	
	fuente_historia.loadFromFile("Fonts/SadMachine.ttf");
	historia_perder.setFont(fuente_historia);
	historia_perder.setCharacterSize(35);
	historia_perder.setString("");
	historia_perder.setPosition(770,200);
	
	hp1 = "TIMMY ESTUDIA SIEMPRE A ULTIMO MOMENTO. ";
	hp2 = "\n\nTIMMY SE HA QUEDADO DORMIDO POR ESTUDIAR TODA\nLA MADRUGADA ANTES DEL EXAMEN.";
	hp3 = "\n\nSU AMIGO JOSE NUNCA DEJA\nA ULTIMO MOMENTO EL ESTUDIO.";
	hp4 = "\n\nJOSE ES INTELIGENTE, SE COMO JOSE.";
	cont_historia = 0;
	
	
	if(!MusicaDesarrollo.loadFromFile("Sounds/musicajuego.flac"))
		cerr<<"NO SE PUDO CARGAR EL SONIDO "<<endl;
	MusicD.setBuffer(MusicaDesarrollo); 
	MusicD.setVolume(100);
	MusicD.setLoop(true);
	
	if(!MusicaFin.loadFromFile("Sounds/MusicaFin.flac"))
		cerr<<"NO SE PUDO CARGAR EL SONIDO"<<endl;
	MusicF.setBuffer(MusicaFin); 
	MusicF.setVolume(90);
	MusicF.setLoop(true);
	
	if(!SonidoProfesor.loadFromFile("Sounds/Profesor.flac"))
		cerr<<"NO SE PUDO CARGAR EL SONIDO"<<endl;
	SProf.setBuffer(SonidoProfesor); 
	SProf.setVolume(100);
	SProf.setLoop(false);
	
	if(!SonidoColision.loadFromFile("Sounds/Colision.flac"))
		cerr<<"NO SE PUDO CARGAR EL SONIDO"<<endl;
	SCol.setBuffer(SonidoColision); 
	SCol.setVolume(100);
	SCol.setLoop(false);
	
	if(!SonidoAplazado.loadFromFile("Sounds/Aplazado.flac"))
		cerr<<"NO SE PUDO CARGAR EL SONIDO"<<endl;
	SApla.setBuffer(SonidoColision); 
	SApla.setVolume(100);
	SApla.setLoop(false);
	
	textura_pantallaganar.loadFromFile("Sprites/pantalla_ganar.png");
	pantalla_ganar.setTexture(textura_pantallaganar);
	
	textura_aprobado.loadFromFile("Sprites/aprobado.png");
	aprobado.setTexture(textura_aprobado);
	aprobado.setScale(12,12);
	aprobado.setOrigin(100,0);
	aprobado.setPosition(360,170);
	aprobado.setRotation(-45);
	
}

Juego::~Juego() {
	
}

void Juego::Comenzar(){
	Clock reloj;
	
	menu.Comenzar(ventana);
	
	reloj_aparicion_finales.restart();
	
	comenzar = true;
	reloj.restart();
	reloj_anim_fondo.restart();
	reloj_aparicion_acidos.restart();
	reloj_aparicion_finales.restart();
	reloj_aparicion_profesor.restart();
	reloj_aplazos.restart();
	reloj_tiempo_profesor.restart();
	reloj_ecuacion.restart();
	
	MusicD.play();
	
	while(ventana->isOpen() && comenzar && !Fin){
		
		float DeltaTiempo = reloj.restart().asSeconds();
		
		Actualizar(DeltaTiempo);
		
		ProcesarEventos();
		
		ProcesarColisiones();
		
		Dibujar(DeltaTiempo);
		
	}
	
	MusicD.stop();
	MusicF.play();
	reloj_historia_perder.restart();
	
	//VENTANA DE GAMEOVER
	while(ventana->isOpen() && gameover){
		float DeltaTiempo = reloj.restart().asSeconds();
		Event ev;
		while(ventana->pollEvent(ev)){
			if(ev.type == Event::Closed) ventana->close();
			if(ev.key.code == Keyboard::Escape) ventana->close();
			if(ev.key.code == Keyboard::F5) Reiniciar();
		}
		
		if(aplazado.getScale().x > 2) {
			aplazado.setScale(aplazado.getScale().x - 0.1, aplazado.getScale().y - 0.1);
		}
		if(cont_historia == 4) reloj_historia_perder.restart();
		if(reloj_historia_perder.getElapsedTime().asSeconds() > 2.0){
			reloj_historia_perder.restart();
			switch(cont_historia) {
			case 0 :
				historia_perder.setString(historia_perder.getString()+hp1);
				cont_historia++;
				break;
			case 1 :
				historia_perder.setString(historia_perder.getString()+hp2);
				cont_historia++;
				break;
			case 2 :
				historia_perder.setString(historia_perder.getString()+hp3);
				cont_historia++;
				break;
			case 3 : 
				historia_perder.setString(historia_perder.getString()+hp4);
				cont_historia++;
				break;
			default:
				historia_perder.setString("");
			}
		}
		
		
		ventana->clear(Color::Magenta);
		ventana->draw(pantalla_perder);
		ventana->draw(aplazado);
		ventana->draw(historia_perder);
		ventana->display();
	}
	
	reloj_aprobado.restart();
	//VENTANA GANADOR
	while(ventana->isOpen() && !gameover){
		float DeltaTiempo = reloj.restart().asSeconds();
		Event ev;
		while(ventana->pollEvent(ev)){
			if(ev.type == Event::Closed) ventana->close();
			if(ev.key.code == Keyboard::Escape) ventana->close();
			if(ev.key.code == Keyboard::F5) Reiniciar();
		}
		
		if(reloj_aprobado.getElapsedTime().asSeconds() > .2){
			if(aprobado.getScale().x > 1.5 )aprobado.setScale(aprobado.getScale().x-0.3,aprobado.getScale().y -0.3);
		}
		
		ventana->clear();
		ventana->draw(pantalla_ganar);
		ventana->draw(aprobado);
		ventana->display();
	}
}

void Juego::Actualizar(float dt){
	//actualizar todo el juego
	
	if(Horas.VerHoras() == 0){
		Fin = true;
		gameover = true;
	}
	
	if(parte1){
		dificultad = 2;
		if(parte2){
			dificultad =4;
		}
	}
	
	
	if(reloj_ecuacion.getElapsedTime().asSeconds() > 10 + dificultad ){
		ecuacion.setPosition(rand()%1200,rand()%600);
		reloj_ecuacion.restart();
	}
	
	int plus = 0;
	if(aparece_profesor) plus = 18;
	if(reloj_anim_fondo.getElapsedTime().asSeconds() > 0 && reloj_anim_fondo.getElapsedTime().asSeconds() < 0.1 ){
		background.setPosition(0,2+plus);
	}
	if(reloj_anim_fondo.getElapsedTime().asSeconds() > 0.1 && reloj_anim_fondo.getElapsedTime().asSeconds() < 0.2 ){
		background.setPosition(0,-2-plus);
	}
	if(reloj_anim_fondo.getElapsedTime().asSeconds() > 0.2 && reloj_anim_fondo.getElapsedTime().asSeconds() < 0.3 ){
		background.setPosition(2+plus,0);
	}
	if(reloj_anim_fondo.getElapsedTime().asSeconds() > 0.3 && reloj_anim_fondo.getElapsedTime().asSeconds() < 0.4 ){
		background.setPosition(-2-plus,0);
	}
	if(reloj_anim_fondo.getElapsedTime().asSeconds() > 0.4 ) reloj_anim_fondo.restart();
	
	
	//SWITCH PARA APARICION DEL PROFESOR
	if(profesor.getPosition().x > 0 && profesor.getPosition().y > 0 ){
		aparece_profesor = true;
	}
	else {
		reloj_tiempo_profesor.restart();
		disparos_profesor = 0;
		aparece_profesor = false;
	}
	if(disparos_profesor == 3){
		profesor.setPosition(-300,-300);
		disparos_profesor = 0;
	}
	
	//DISPAROS DEL PROFESOR
	if(!aparece_profesor){
		reloj_aplazos.restart();
	}
	
	if(reloj_aplazos.getElapsedTime().asSeconds() > 1 - (dificultad/6)){
		Aplazo *puntero = new Aplazo;
		puntero->setPosition(profesor.getPosition());
		puntero->setVelocidad(timmy.getPosition().x - puntero->getPosition().x,timmy.getPosition().y - puntero->getPosition().y);
		vector_aplazos.push_back(*puntero);
		reloj_aplazos.restart();
		disparos_profesor +=1 ;
	}
	
	//APARECE EL PROFESOR
	if(reloj_aparicion_profesor.getElapsedTime().asSeconds() > 10 - dificultad ){
		int rp = rand()%2;
		SProf.play();
		switch(rp){
		case 0:
			profesor.setPosition(200,400);
			break;
		case 1:
			profesor.setPosition(1100,400);
			break;
		}
		reloj_aparicion_profesor.restart();
	}
	
	//APARECEN LOS FINALES
	if(reloj_aparicion_finales.getElapsedTime().asSeconds() > 1.5 - (dificultad / 5)){
		Final *puntero_final = new Final;
		puntero_final->setVelocidad(0,150);
		puntero_final->setPosition(rand()%1280,10);
		vector_finales.push_back(*puntero_final);
		reloj_aparicion_finales.restart();
	}
	
	
	//APARECEN LOS ACIDOS
	if(reloj_aparicion_acidos.getElapsedTime().asSeconds() > 2 - (dificultad / 5)){
		Acido *puntero_acido = new Acido;
		int r = rand()%4;
		switch(r){
		case 0:
			puntero_acido->setPosition(rand()%1280,-10);
			break;
		case 1:
			puntero_acido->setPosition(rand()%1280,730);
			break;
		case 2:
			puntero_acido->setPosition(-10,rand()%720);
			break;
		case 3:
			puntero_acido->setPosition(1290,rand()%720);
			break;
		}
		puntero_acido->setVelocidad(timmy.getPosition().x-puntero_acido->getPosition().x,timmy.getPosition().y-puntero_acido->getPosition().y);
		vector_acido.push_back(*puntero_acido);
		
		reloj_aparicion_acidos.restart();
	}
	
	//SI PASA LAS MEDIDAS DE LA PANTALLA LO BORRA
	std::vector<Acido>::iterator itA = vector_acido.begin();
	while( itA != vector_acido.end() )
	{
		if( itA->getPosition().y > 700 || itA->getPosition().x > 1310 || itA->getPosition().x < -30 || itA->getPosition().y < -30 ){
			itA = vector_acido.erase(itA);
		}else{
			++itA;
		}
	}
	std::vector<Final>::iterator itF = vector_finales.begin();
	while(itF != vector_finales.end()){
		if( itF->getPosition().y > 700 || itF->getPosition().x > 1310 || itF->getPosition().x < -30 || itF->getPosition().y < -30 ){
			itF = vector_finales.erase(itF);
		}else{
			++itF;
		}
	}
	std::vector<Aplazo>::iterator itAp = vector_aplazos.begin();
	while(itAp != vector_aplazos.end()){
		if( itAp->getPosition().y > 700 || itF->getPosition().x > 1310 || itF->getPosition().x < -30 || itF->getPosition().y < -30 ){
			itAp = vector_aplazos.erase(itAp);
		}else{
			++itAp;
		}
	}
	
	//ACTUALIZAMOS LOS ACIDOS
	for(std::vector<Acido>::iterator it = vector_acido.begin(); it!=vector_acido.end();it++) { 
		it->Actualizar(dt);
	}
	
	for(std::vector<Aplazo>::iterator it = vector_aplazos.begin(); it!=vector_aplazos.end();it++) { 
		it->Actualizar(dt);
	}
	
	//ACTUALIZAMOS LOS FINALES
	for(std::vector<Final>::iterator it = vector_finales.begin(); it!=vector_finales.end();it++) { 
		it->Actualizar(dt);
	}
	profesor.Actualizar(dt);
	timmy.Actualizar(dt);
	ecuacion.Actualizar();
}

void Juego::Dibujar(float dt){
	ventana->clear();
	
	ventana->draw(background);
	
	ventana->draw(timmy);
	ventana->draw(ecuacion);
	ventana->draw(profesor);
	
	for(std::vector<Aplazo>::iterator itAp = vector_aplazos.begin(); itAp!=vector_aplazos.end();itAp++) { 
		ventana->draw(*itAp);
	}
	for(std::vector<Acido>::iterator itA = vector_acido.begin(); itA!=vector_acido.end();itA++) { 
		ventana->draw(*itA);
	}
	for(std::vector<Final>::iterator it = vector_finales.begin(); it!=vector_finales.end();it++) { 
		ventana->draw(*it);
	}
	ventana->draw(hud);
	Horas.VerTiempo(*ventana);
	if (parte1 == true) ventana->draw(p1);
	if (parte2 == true) ventana->draw(p2);
	if (parte3 == true) ventana->draw(p3);
	ventana->display();
}

void Juego::ProcesarEventos(){
	Event e;
	float horizontal = 0, vertical = 0;
	while(ventana->pollEvent(e)){
		if(e.type == Event::Closed) ventana->close();
		if(e.key.code == Keyboard::Escape ) ventana->close();
		if(e.key.code == Keyboard::F5) Reiniciar();
		if(e.KeyReleased) {
			timmy.setRotation(0);
		}
	}
	if(Keyboard::isKeyPressed(Keyboard::Left)){
		if(timmy.getPosition().x > 32 ){
			timmy.setRotation(330);
			horizontal -= 700;
		}
	}
	if(Keyboard::isKeyPressed(Keyboard::Right)){
		if(timmy.getPosition().x < 1258 ) {
			timmy.setRotation(30);
			horizontal += 700;
		}
	}
	if(Keyboard::isKeyPressed(Keyboard::Up)){
		if(timmy.getPosition().y > 32 ) vertical -= 700;
	}
	if(Keyboard::isKeyPressed(Keyboard::Down)){
		if(timmy.getPosition().y < 550) vertical += 700;
	}
	
	timmy.setVelocidad(horizontal,vertical);
	
}

void Juego::ProcesarColisiones(){
	bool choco = false;
	std::vector<Aplazo>::iterator itAplazos = vector_aplazos.begin();
	std::vector<Acido>::iterator itAcidos = vector_acido.begin();
	std::vector<Final>::iterator itFinales = vector_finales.begin();
	
	while ( (itAcidos != vector_acido.end()) && (!choco) ) {
		if (BoundingBoxTest(*itAcidos, timmy) ) {
			vector_acido.erase(itAcidos);
			Horas.QuitarTiempo();
			choco = true;
			SCol.play();
			break;
		}
		itAcidos++;
	}
	
	while ( (itFinales != vector_finales.end()) && (!choco) ) {
		if (BoundingBoxTest(*itFinales, timmy) ) {
			vector_finales.erase(itFinales);
			Horas.QuitarTiempo();
			choco = true;
			SCol.play();
			break;
		}
		itFinales++;
	}
	
	while ( itAplazos != vector_aplazos.end() && (!choco) ) {
		if ( BoundingBoxTest(*itAplazos, timmy) ) {
			vector_aplazos.erase(itAplazos);
			Horas.QuitarTiempo();
			choco = true;
			SApla.play();
			break;
		}
		itAplazos++;
	}
	
	Rect<float> t(timmy.getGlobalBounds());
	Rect<float> e(ecuacion.getGlobalBounds());
	
	if (t.intersects(e)) {
		parteEcuacion++;
		parte1 = true;
		if (parteEcuacion != 3) 
		{ ecuacion.PosicionErr();
		if (parteEcuacion==2) parte2=true;
		}
		else if (parteEcuacion == 3)
		{	parte3 = true;
			Fin = true;
			gameover = false;
		}
	}
	
	// esta función se usa de la clase colisión -> Collision::BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2)
}

void Juego::Reiniciar(){
	if(MusicD.getStatus() == MusicD.Playing) MusicD.stop();
	if(MusicF.getStatus() == MusicF.Playing) MusicF.stop();
	
	ventana->close();
	Juego juegoNuevo;
	juegoNuevo.Comenzar();
}
