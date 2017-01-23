#include "Menu.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

Menu::Menu() {
	fuente_menu.loadFromFile("Fonts/BMblock.TTF");
	texto_menu.setFont(fuente_menu);
	texto_menu.setCharacterSize(90);
	texto_menu.setPosition(430,50);
	texto_menu.setColor(Color::White);
	texto_menu.setString("TIMMY DON'T\nSLEEP");
	
	fuente_jugar.loadFromFile("Fonts/SadMachine.ttf");
	texto_jugar.setFont(fuente_jugar);
	texto_jugar.setCharacterSize(80);
	texto_jugar.setPosition(450,350);
	texto_jugar.setColor(Color::Yellow);
	texto_jugar.setString("JUGAR");
	
	texto_salir.setFont(fuente_jugar);
	texto_salir.setCharacterSize(80);
	texto_salir.setPosition(450,400);
	texto_salir.setString("SALIR");
	menu = false;
	enter = false;
	animacion = false;
	
	textura_anim_fondo.loadFromFile("Sprites/background_anim.png");
	background_anim.setTexture(textura_anim_fondo);
	
	textura_fondo.loadFromFile("Sprites/menu.png");
	fondo.setTexture(textura_fondo);

	textura_fuego.loadFromFile("Sprites/Fuego.png");
	fuego.setTexture(textura_fuego);
	fuego.setPosition(640,500);
	fuego.setTextureRect(IntRect(0,0,150,150));
	fuego.setOrigin(75,75);
	reloj_fuego.restart();
	
	s1 = "\tEL PEQUENO TIMMY NO HA ESTUDIADO PARA EL EXAMEN DE CALCULO Y DECIDIO\nINVOCAR A LAS FUERZAS DEL MAS ALLA PARA QUE SU PROFESOR SE ROMPA UNA PIERNA. ";
	s2 = "\n\n\tPERO TIMMY ESCRIBIO MAL LA ECUACION DEL RITUAL, SUMERGIENDOSE EN UNA \nNUEVA DIMENSION QUE SE CONVERTIRA EN UNA TERRIBLE PESADILLA ESTUDIANTIL.";
	s3 = "\n\nAYUDA A TIMMY A RECONSTRUIR LA ECUACION Y PODER TERMINAR EL RITUAL... ";
	s4 = "\n\n\t\t\t\t\t\t\t\t!SIN ESTRESARSE!";
	cant = 0;
	
	fuente_historia.loadFromFile("Fonts/SadMachine.ttf");
	texto_historia.setFont(fuente_historia);
	texto_historia.setCharacterSize(40);
	texto_historia.setString("");
	texto_historia.setPosition(100,80);
	
	textura_nube.loadFromFile("Sprites/Nube.png");
	nube.setTexture(textura_nube);
	nube.setTextureRect(IntRect(400,0,100,100));
	nube.setOrigin(50,50);
	nube.setScale(2,2);
	nube.setPosition(300,450);
	
	textura_timmy.loadFromFile("Sprites/timmy_anim.png");
	timmy.setTexture(textura_timmy);
	timmy.setTextureRect(IntRect(0,0,384,384));
	timmy.setScale(0.3,0.3);
	timmy.setPosition(300,460);
	
	textura_hojas.loadFromFile("Sprites/hojas.png");
	hojas.setTexture(textura_hojas);
	hojas.setPosition(490,520);
	hojas.setTextureRect(IntRect(0,0,300,140));
	
	if(!MusicaComienzo.loadFromFile("Sounds/animacion.flac"))
		std::cerr<<"NO SE PUDO CARGAR EL SONIDO"<<std::endl;
	MusicC.setBuffer(MusicaComienzo); 
	MusicC.setVolume(100);
	MusicC.setLoop(false);
	
	if(!MusicaMenu.loadFromFile("Sounds/menu.flac"))
		std::cerr<<"NO SE PUDO CARGAR EL SONIDO"<<std::endl;
	Mmenu.setBuffer(MusicaMenu); 
	Mmenu.setVolume(100);
	Mmenu.setLoop(false);
}

Menu::~Menu() {
	
}

void Menu::Comenzar(RenderWindow* v){
	Clock reloj_menu;
	
	Mmenu.play();
	while(v->isOpen() && !menu){
		float deltaT = reloj_menu.restart().asSeconds();
		
		Actualizar(deltaT,v);
		
		ProcesarEventos(v);
		
		Dibujar(deltaT,v);
	}
	Mmenu.stop();
	
	MusicC.play();
	reloj_historia.restart();
	reloj_nube.restart();
	reloj_timmy.restart();
	reloj_hojas.restart();
	reloj_animacion.restart();
	
	while(v->isOpen() && menu && !animacion){
		float deltaT = reloj_menu.restart().asSeconds();
		
		ActualizarAnimacion(deltaT,v);
		
		Event ev;
		while(v->pollEvent(ev)){
			if(ev.type == Event::Closed) v->close();
			if(ev.key.code == Keyboard::Escape) v->close();
			if(ev.key.code == Keyboard::A) {
				animacion = true;
			}
		}
		
		DibujarAnimacion(deltaT,v);
	}
	MusicC.stop();
}

void Menu::Dibujar(float dt,RenderWindow* v){
	v->clear();
	v->draw(fondo);
	v->draw(texto_menu);
	v->draw(texto_jugar);
	v->draw(texto_salir);
	v->display();
}

void Menu::Actualizar(float dt,RenderWindow* v){
	if(enter){
		if(texto_jugar.getColor() == Color::Yellow){
			menu = true;
		}else{
			v->close();
		}
	}
}

void Menu::ProcesarEventos(RenderWindow* v){
	Event e;
	while(v->pollEvent(e)){
		if(e.type == Event::Closed) v->close();
		if(e.key.code == Keyboard::Return) enter=true;
		if(e.key.code == Keyboard::Escape) v->close();
		if(e.key.code == Keyboard::Down){
			texto_jugar.setColor(Color::White);
			texto_salir.setColor(Color::Yellow);
		}
		if(e.key.code == Keyboard::Up){
			texto_jugar.setColor(Color::Yellow);
			texto_salir.setColor(Color::White);
		}
		
	}
}

void Menu::ActualizarAnimacion(float deltaT,RenderWindow* v){
	
	if(reloj_hojas.getElapsedTime().asSeconds() > 0.0 && reloj_hojas.getElapsedTime().asSeconds() < 12.0 ){
		hojas.setTextureRect(IntRect(0,0,300,140));
	}
	if(reloj_hojas.getElapsedTime().asSeconds() > 12.0 && reloj_hojas.getElapsedTime().asSeconds() < 12.2 ){
		hojas.setTextureRect(IntRect(0,140,300,140));
	}
	if(reloj_hojas.getElapsedTime().asSeconds() > 12.2 && reloj_hojas.getElapsedTime().asSeconds() < 12.4 ){
		hojas.setTextureRect(IntRect(0,280,300,140));
	}
	if(reloj_hojas.getElapsedTime().asSeconds() > 12.4 && reloj_hojas.getElapsedTime().asSeconds() < 12.6 ){
		hojas.setTextureRect(IntRect(0,420,300,140));
	}
	if(reloj_hojas.getElapsedTime().asSeconds() > 12.6 && reloj_hojas.getElapsedTime().asSeconds() < 12.8 ){
		hojas.setTextureRect(IntRect(0,560,300,140));
	}
	if(reloj_hojas.getElapsedTime().asSeconds() > 12.8 ){
		hojas.setTextureRect(IntRect(0,700,300,140));
	}
	
	if(reloj_timmy.getElapsedTime().asSeconds() > 0.0 && reloj_timmy.getElapsedTime().asSeconds() < 0.2 ){
		timmy.setTextureRect(IntRect(0,0,384,384));
	}
	if(reloj_timmy.getElapsedTime().asSeconds() > 0.2 && reloj_timmy.getElapsedTime().asSeconds() < 0.4 ){
		timmy.setTextureRect(IntRect(384,0,384,384));
	}
	if(reloj_timmy.getElapsedTime().asSeconds() > 0.4){
		reloj_timmy.restart();
	}
	
	if(reloj_nube.getElapsedTime().asSeconds() > 0.0 && reloj_nube.getElapsedTime().asSeconds() > 8 ){
		nube.setTextureRect(IntRect(400,0,100,100));
	}
	if(reloj_nube.getElapsedTime().asSeconds() > 8.0 && reloj_nube.getElapsedTime().asSeconds() > 8.5 ){
		nube.setTextureRect(IntRect(300,0,100,100));
	}
	if(reloj_nube.getElapsedTime().asSeconds() > 8.5 && reloj_nube.getElapsedTime().asSeconds() > 9.0 ){
		nube.setTextureRect(IntRect(200,0,100,100));
	}
	if(reloj_nube.getElapsedTime().asSeconds() > 9.0 && reloj_nube.getElapsedTime().asSeconds() > 9.5 ){
		nube.setTextureRect(IntRect(100,0,100,100));
	}
	if(reloj_nube.getElapsedTime().asSeconds() > 10.0 && reloj_nube.getElapsedTime().asSeconds() > 10.5 ){
		nube.setTextureRect(IntRect(0,0,100,100));
	}
	
	if(cant == 4 ){
		reloj_historia.restart();
	}
	
	if(reloj_historia.getElapsedTime().asSeconds() > 2 ) {
		reloj_historia.restart();
		switch(cant) {
		case 0 :
			texto_historia.setString(texto_historia.getString()+s1);
			cant++;
			break;
		case 1 :
			texto_historia.setString(texto_historia.getString()+s2);
			cant++;
			break;
		case 2 :
			texto_historia.setString(texto_historia.getString()+s3);
			cant++;
			break;
		case 3 :
			texto_historia.setString(texto_historia.getString()+s4);
			cant++;
			break;
		default:
			texto_historia.setString("");
			break;
		}
	}
	
	
	
	if(reloj_fuego.getElapsedTime().asSeconds() > 0.0 && reloj_fuego.getElapsedTime().asSeconds() < 0.1){
		fuego.setTextureRect(IntRect(0,0,150,150));
	}
	if(reloj_fuego.getElapsedTime().asSeconds() > 0.1 && reloj_fuego.getElapsedTime().asSeconds() < 0.2){
		fuego.setTextureRect(IntRect(150,0,150,150));
	}
	if(reloj_fuego.getElapsedTime().asSeconds() > 0.2 && reloj_fuego.getElapsedTime().asSeconds() < 0.3){
		fuego.setTextureRect(IntRect(300,0,150,150));
	}
	if(reloj_fuego.getElapsedTime().asSeconds() > 0.3 ){
		reloj_fuego.restart();
	}
	
	if(reloj_animacion.getElapsedTime().asSeconds() > 15 ){
		animacion = true;
	}
}
void Menu::DibujarAnimacion(float dt,RenderWindow* v){
	v->clear(Color::White);
	v->draw(background_anim);
	v->draw(fuego);
	v->draw(nube);
	v->draw(timmy);
	v->draw(hojas);
	v->draw(texto_historia);
	v->display();
}
