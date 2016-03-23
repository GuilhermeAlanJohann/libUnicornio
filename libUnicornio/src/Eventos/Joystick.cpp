#include "Joystick.h"

Joystick::Joystick(): id(-1), deadZone(0.2f), x(0), y(0), z(-1), xDir(0), yDir(0), zDir(-1), sdl_joystick(NULL), sdl_haptic(NULL)
{
	sdl_joystick = NULL;
	sdl_controller = NULL;
	sdl_haptic = NULL;
	for(int i = 0; i < NUMERO_DE_BOTOES_JOYSTICK; ++i)
	{
		pressionou[i] = false;
		segurando[i] = false;
		soltou[i] = false;
	}
};

Joystick::~Joystick()
{};

bool Joystick::eControle()
{
	return sdl_controller;
}

bool Joystick::estaPlugado()
{
	if (sdl_joystick)
	{
		return SDL_JoystickGetAttached(sdl_joystick);
	}
	return 0;
}

std::string Joystick::getNome()
{
	if (sdl_controller)
	{
		return SDL_GameControllerName(sdl_controller);
	}
	else if (sdl_joystick)
	{
		return SDL_JoystickName(sdl_joystick);
	}

	return "";
}

int Joystick::getNumBotoes()
{
	if (sdl_joystick)
	{
		return SDL_JoystickNumButtons(sdl_joystick);
	}
	return 0;
}

int Joystick::getNumEixos()
{
	if (sdl_joystick)
	{
		return SDL_JoystickNumAxes(sdl_joystick);
	}
	return 0;
}

void Joystick::vibrar(float forca, float tempo)
{
	if(sdl_haptic)
	{
		if(SDL_HapticRumbleSupported(sdl_haptic))
			SDL_HapticRumblePlay(sdl_haptic, forca, tempo*1000);
	}
}

void Joystick::pararDeVibrar()
{
	if(sdl_haptic)
	{
		if(SDL_HapticRumbleSupported(sdl_haptic))
			SDL_HapticRumbleStop(sdl_haptic);
	}
}