#include "Audio.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"

Audio::Audio()
{
	mix_chunk = NULL;
	carregado = false;
}

Audio::Audio(const Audio &r)
{
	caminho_arquivo = r.caminho_arquivo;
	carregado = r.carregado;
	mix_chunk = r.mix_chunk;
}

Audio::~Audio()
{
	if(estaCarregado())
	{
		descarregar();
	}
}

Audio& Audio::operator=(const Audio &r)
{
	if(this != &r)
	{
		caminho_arquivo = r.caminho_arquivo;
		carregado = r.carregado;
		mix_chunk = r.mix_chunk;
	}
	return *this;
}

bool Audio::operator==(const Audio &r)
{
	return (caminho_arquivo == r.caminho_arquivo && carregado == r.carregado && mix_chunk == r.mix_chunk);
}

bool Audio::operator!=(const Audio &r)
{
	return !(*this == r);
}

bool Audio::carregar(string arquivo)
{
	if(!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}
	
	if(estaCarregado())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Som ja carregou o arquivo " + caminho_arquivo + ".");
		return false;
	}
	mix_chunk = Mix_LoadWAV(arquivo.c_str());
	
	if(!mix_chunk) 
	{
		gDebug.erro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	caminho_arquivo = arquivo;
	carregado = true;

	return carregado;
}

void Audio::descarregar()
{
	Mix_FreeChunk(mix_chunk);
	mix_chunk = NULL;
	caminho_arquivo = "";
	carregado = false;
}

bool Audio::estaCarregado()
{
	return carregado;
}

Mix_Chunk* Audio::getMix_Chunk()
{
	return mix_chunk;
}

string Audio::getCaminhoDoArquivo()
{
	return caminho_arquivo;
}

Audio Audio::clonar()
{
	Audio r(*this);
	r.carregar(caminho_arquivo);
	return r;
}