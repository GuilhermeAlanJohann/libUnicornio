#ifndef UNI_TOQUE_H
#define UNI_TOQUE_H

#include "uniAPI.h"
#include "SDL_events.h"
#include "EnumsInputs.h"

struct UNI_API Toque
{
public:
	EnumToque tipo;

	int x;
	int y;
	int dx;
	int dy;

	float nx;
	float ny;
	float ndx;
	float ndy;

	float pressao;

	int64_t idDedo;
};

#endif