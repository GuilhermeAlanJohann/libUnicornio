#ifndef UNI_EVENTOSJOYSTICK_H
#define UNI_EVENTOSJOYSTICK_H

#include "uniAPI.h"
#include "Joystick.h"

class UNI_API EventosJoysticks
{
public:
	EventosJoysticks();
	~EventosJoysticks();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	Joystick& operator[](const int i);

	Joystick player1;
	Joystick player2;
	Joystick player3;
	Joystick player4;

private:
	Joystick *identificarJoystick(const int id);
	Joystick *getPrimeiroJoystickLivre();
	void filtrarInput(float& f, Joystick* joy);

	static int nextId;
};

#endif