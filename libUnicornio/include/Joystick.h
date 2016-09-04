#ifndef UNI_JOYSTICK_H
#define UNI_JOYSTICK_H

#include "uniAPI.h"
#include "SDL_events.h"
#include "SDL_joystick.h"
#include "SDL_haptic.h"
#include "EnumsInputs.h"
#include <string>

struct UNI_API Joystick
{
public:
	Joystick();
	~Joystick();

	int id;

	float deadZone;

	float x;
	float y;
	union { float z; float gatilhoEsq; };

	float xDir;
	float yDir;
	union { float zDir; float gatilhoDir; };

	bool pressionou[NUMERO_DE_BOTOES_JOYSTICK];
	bool segurando[NUMERO_DE_BOTOES_JOYSTICK];
	bool soltou[NUMERO_DE_BOTOES_JOYSTICK];

	SDL_Joystick *sdl_joystick;
	SDL_Haptic *sdl_haptic;
	SDL_GameController *sdl_controller;

	bool eControle();
	bool estaPlugado();

	int getNumBotoes();
	int getNumEixos();
	std::string getNome();
	void vibrar(float forca, float tempo);
	void pararDeVibrar();
};

#endif