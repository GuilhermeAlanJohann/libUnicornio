#ifndef UNI_TEXTURA_H
#define UNI_TEXTURA_H

#include "uniAPI.h"
#include "TexturaBase.h"

class UNI_API Textura: public TexturaBase
{
public:
	Textura();
	Textura(const Textura& t);
	~Textura();

	Textura& operator=(const Textura& t);

	bool criar(int largura, int altura, int qualidade_escala = QUALIDADE_ESCALA_BAIXA, bool streaming = false);
	bool criarDoArquivo(const string& arquivo, int qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	bool criarDaSDL_Surface(SDL_Surface* surface, int qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	bool destruir();

	bool eEstatica();
	bool eDeStreaming();
	bool estaTravada();

	string getCaminhoDoArquivo();

	/* 
	Desc:
		Esse m�todo funciona apenas com texturas de streaming! 
	Ele copia os pixels da textura da memoria de v�deo para a mem�ria RAM.
	Essa � uma opera��o lenta e deve ser usada apenas quando realmente necess�rio.
	Ao chamar esse m�todo ele trava a textura, ou seja, ela n�o pode ser desenhada
	at� que o m�todo destravar seja chamado.
	Params: 
		pixels: ponteiro que ser� preenchido com o array de pixels da textura.
		pitch: inteiro que ser� preenchido com o valor do pitch (bytes por linha) da textura.
	Retorno:
		Uma booleana indicando se a opera��o foi bem sucessedida ou n�o.
	*/
	bool travar(void* pixels, int& pitch);

	/*
	Desc:
		Esse m�todo funciona apenas com texturas de streaming!
	Ele destrava a textura (que foi travada chamando o m�todo 'travar') para 
	que ela possa ser desenhada novamente.
	Retorno:
		Uma booleana indicando se a opera��o foi bem sucessedida ou n�o.
	*/
	bool destravar();

	/*
	Desc:
		Esse m�todo funciona tanto com texturas de streaming como com texturas estaticas.
	Por�m se a textura for de streaming, deve-se usar preferencialmente os m�todos 'travar' e 
	'destravar' para obter melhor performance.
	Este m�todo copia o conte�de de	'pixels' para os pixels da textura.
	Esta � uma opera��o MUITO lenta e deve ser usada apenas quando for realmente necess�ria. 
	Params:
		pixels: ponteiro contendo o novo array de pixels da textura.
		pitch: inteiro contendo o valor do pitch (bytes por linha) da textura.
	Retorno:
		Uma booleana indicando se a opera��o foi bem sucessedida ou n�o.
	*/
	bool atualizarPixels(void* pixels, int pitch);

	//	Funciona parcialmente:
	//	N�o copia os pixels de uma textura estatica que n�o foi criada de um arquivo.
	//	Neste caso, cria uma textura com o mesmo tamanho mas transparente.
	//	Quando a textura � estatica, mas foi criada a partir de um arquivo, cria outra
	//	textura a partir do mesmo arquivo.
	//	Quando a textura � de streaming, copia os pixels de uma para a outra.
	Textura clonar();

private:
	bool travada;
	string caminhoArquivo;
};

#endif