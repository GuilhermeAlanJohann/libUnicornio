#include "Eventos.h"

int EventosJoysticks::nextId = 0;

EventosJoysticks::EventosJoysticks()
{}

EventosJoysticks::~EventosJoysticks()
{}

void EventosJoysticks::atualizar()
{
	for(int i = 0; i < NUMERO_DE_BOTOES_JOYSTICK; ++i)
	{
		player1.pressionou[i] = false;
		player1.soltou[i] = false;

		player2.pressionou[i] = false;
		player2.soltou[i] = false;

		player3.pressionou[i] = false;
		player3.soltou[i] = false;

		player4.pressionou[i] = false;
		player4.soltou[i] = false;
	}
}

void EventosJoysticks::processarEvento(const SDL_Event& evento)
{
	Joystick* joy;

	switch(evento.type)
	{
	case SDL_JOYAXISMOTION:
		joy = identificarJoystick(evento.jaxis.which);
		if(joy)
		{
			switch(evento.jaxis.axis)
			{
			case SDL_CONTROLLER_AXIS_LEFTX:
				joy->x = evento.caxis.value/32767.0;
				filtrarInput(joy->x, joy);
				break;

			case SDL_CONTROLLER_AXIS_LEFTY:
				joy->y = evento.caxis.value/32767.0;
				filtrarInput(joy->y, joy);
				break;

			case SDL_CONTROLLER_AXIS_RIGHTX:
				joy->xDir = evento.caxis.value/32767.0;
				filtrarInput(joy->xDir, joy);
				break;

			case SDL_CONTROLLER_AXIS_RIGHTY:
				joy->yDir = evento.caxis.value/32767.0;
				filtrarInput(joy->yDir, joy);
				break;
			}
		}
		break;

	case SDL_JOYBUTTONDOWN:
		joy = identificarJoystick(evento.jbutton.which);
		if(joy)
		{
			joy->segurando[evento.jbutton.button] = true;

			if(evento.jbutton.state == SDL_PRESSED)
			{
				joy->pressionou[evento.jbutton.button] = true;
			}
		}

		break;

	case SDL_JOYBUTTONUP:	
		joy = identificarJoystick(evento.jbutton.which);
		if(joy)
		{
			joy->segurando[evento.jbutton.button] = false;

			if(evento.jbutton.state == SDL_RELEASED)
			{
				joy->soltou[evento.jbutton.button] = true;
			}
		}

		break;


	case SDL_JOYDEVICEADDED:
		joy = getPrimeiroJoystickLivre();
		if(joy)
		{
			joy->id = nextId;
			//joy->js = SDL_JoystickOpen(joy->id);
			joy->js = SDL_JoystickOpen(evento.jdevice.which);
			nextId++;
		}
		break;

	case SDL_JOYDEVICEREMOVED:
		joy = identificarJoystick(evento.jdevice.which);
		if(joy)
		{
			SDL_JoystickClose(joy->js);
			joy->js = NULL;
			joy->id = -1;
		}
		break;
	}
}

Joystick* EventosJoysticks::identificarJoystick(const int id)
{
	// compara o id como cada um dos players
	if(id == player1.id)
	{
		return &player1; 
	}
	else if(id == player2.id)
	{
		return &player2;
	}
	else if(id == player3.id)
	{
		return &player3;
	}
	else if(id == player4.id)
	{
		return &player4;
	}
	// se não tem nenhum player com este id pega o primeiro que estiver livre
	else return getPrimeiroJoystickLivre();
}

Joystick* EventosJoysticks::getPrimeiroJoystickLivre()
{
	if(player1.id == -1)
	{
		return &player1;
	}
	else if(player2.id == -1)
	{
		return &player2;
	}
	else if(player3.id == -1)
	{
		return &player3;
	}
	else if(player4.id == -1)
	{
		return &player4;
	}
	// se nenhum estiver livre, ignora (retorna nulo)
	return NULL;
}

void EventosJoysticks::filtrarInput(float& f, Joystick* joy)
{
	// verifica dead zone
	if((f < 0) && (f > -joy->deadZone))
	{
		f = 0.0;
	}
	else if((f > 0) && (f < joy->deadZone))
	{
		f = 0.0;
	}
	// verifica se é maior que 1
	else if(f > 1.0)
	{
		f = 1.0;
	}
	else if(f < -1.0)
	{
		f = -1.0;
	}
}