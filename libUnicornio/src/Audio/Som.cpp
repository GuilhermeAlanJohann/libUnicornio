#include "Som.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"

Som::Som()
{
	audio = NULL;

	volume = 100.0f;
	angulo = 0;
	distancia = 0;
	repetindo = false;
	terminouTocar = false;

	indiceDoGrupo = -1;
	indiceDoCanalAtual = -1;
}

Som::Som(const Som& r)
{
	audio = r.audio;
	volume = r.volume;
	angulo = r.angulo;
	distancia = r.distancia;
	repetindo = r.repetindo;
	terminouTocar = r.terminouTocar;

	indiceDoGrupo = r.indiceDoCanalAtual;
	indiceDoCanalAtual = r.indiceDoCanalAtual;
}

Som::~Som()
{
	/*	
		Se o objeto for destruido mas inda esta tocando,
	marca o som como destruido, mas deixa o canal ocupado
	ate que o audio termine de tocar.
		Isso eh para manter consistencia com os metodos
	getNumCanaisOcupados() e getNumCanaisLivres() do
	MixadorDeAudios.
	*/
	gAudios.marcarSomComoDestruido(indiceDoCanalAtual);
}

Som& Som::operator=(const Som &r)
{
	if(this != &r)
	{
		audio = r.audio;
		volume = r.volume;
		angulo = r.angulo;
		distancia = r.distancia;
		repetindo = r.repetindo;
		terminouTocar = r.terminouTocar;

		indiceDoGrupo = r.indiceDoCanalAtual;
		indiceDoCanalAtual = r.indiceDoCanalAtual;
	}
	return *this;
}

bool Som::operator==(const Som &r)
{
	return (audio == r.audio && volume == r.volume && angulo == r.angulo && distancia == r.distancia && indiceDoCanalAtual == r.indiceDoCanalAtual && indiceDoGrupo == r.indiceDoGrupo && repetindo == r.repetindo && terminouTocar == r.terminouTocar);
}

bool Som::operator!=(const Som &r)
{
	return !(*this == r);
}

void Som::tocar(bool repetir)
{
	if(!uniEstaInicializada()) 
		return;

	if(!audio)
	{
		gDebug.erro("Nao pode tocar Som antes de setar Audio.");
		return;
	}

	if(!repetindo)
	{
		indiceDoCanalAtual = gAudios.tocar(audio->getMix_Chunk(), repetir, volume, angulo, distancia);
		if (indiceDoCanalAtual == -1)
			return;

		gAudios.reservarCanalDeAudio(indiceDoCanalAtual, indiceDoGrupo, this);
		repetindo = repetir;
		terminouTocar = false;
	}
}

void Som::parar(float tempo_fadeout)
{
	if(indiceDoCanalAtual != -1)
		Mix_FadeOutChannel(indiceDoCanalAtual, tempo_fadeout*1000);

	repetindo = false;
}

void Som::pausar()
{
	if(indiceDoCanalAtual != -1)
		Mix_Pause(indiceDoCanalAtual);
}

void Som::continuar()
{
	if(indiceDoCanalAtual != -1)
		Mix_Resume(indiceDoCanalAtual);
}

bool Som::estaExecutandoFadeOut()
{
	if (indiceDoCanalAtual == -1)
		return false;

	return (Mix_FadingChannel(indiceDoCanalAtual) == MIX_FADING_OUT);
}

bool Som::estaTocando()
{
	if(indiceDoCanalAtual != -1)
		return Mix_Playing(indiceDoCanalAtual);

	return false;
}

bool Som::estaRepetindo()
{
	return repetindo;
}

bool Som::terminouDeTocar()
{
	return terminouTocar;
}

Audio* Som::getAudio()
{
	return audio;
}

int	Som::getVolume()
{
	return volume;
}

int Som::getDistancia()
{
	return distancia;
}

int Som::getAngulo()
{
	return angulo;
}

void Som::setAudio(Audio* audio)
{
	this->audio = audio;
}

void Som::setAudio(string nome)
{
	setAudio(gRecursos.getAudio(nome));
}

void Som::setVolume(float vol)
{
	if(vol > 100.0f)
		vol = 100.0f;
	if(vol < 0.0f)
		vol = 0.0f;

	volume = vol;

	if(indiceDoCanalAtual != -1)
	{
		gAudios.setVolumeDoCanal(indiceDoCanalAtual, this);
	}
}

void Som::setDistancia(Uint8 dist)
{
	distancia = dist;

	if(indiceDoCanalAtual != -1)
		Mix_SetDistance(indiceDoCanalAtual, distancia);
}

void Som::setAngulo(Sint16 ang)
{
	angulo = ang;

	if(indiceDoCanalAtual != -1)
		Mix_SetPosition(indiceDoCanalAtual, angulo, distancia);
}

void Som::setGrupo(const string& grupo)
{
	indiceDoGrupo = gAudios.getIndiceDoGrupo(grupo);
}

string Som::getNomeDoGrupo()
{
	return gAudios.getNomeDoGrupo(indiceDoGrupo);
}

void Som::quandoTerminarDeTocar()
{
	indiceDoCanalAtual = -1;
	terminouTocar = true;
	repetindo = false;
}