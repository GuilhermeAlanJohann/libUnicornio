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
		Esse método funciona apenas com texturas de streaming! 
	Ele copia os pixels da textura da memoria de vídeo para a memória RAM.
	Essa é uma operação lenta e deve ser usada apenas quando realmente necessário.
	Ao chamar esse método ele trava a textura, ou seja, ela não pode ser desenhada
	até que o método destravar seja chamado.
	Params: 
		pixels: ponteiro que será preenchido com o array de pixels da textura.
		pitch: inteiro que será preenchido com o valor do pitch (bytes por linha) da textura.
	Retorno:
		Uma booleana indicando se a operação foi bem sucessedida ou não.
	*/
	bool travar(void* pixels, int& pitch);

	/*
	Desc:
		Esse método funciona apenas com texturas de streaming!
	Ele destrava a textura (que foi travada chamando o método 'travar') para 
	que ela possa ser desenhada novamente.
	Retorno:
		Uma booleana indicando se a operação foi bem sucessedida ou não.
	*/
	bool destravar();

	/*
	Desc:
		Esse método funciona tanto com texturas de streaming como com texturas estaticas.
	Porém se a textura for de streaming, deve-se usar preferencialmente os métodos 'travar' e 
	'destravar' para obter melhor performance.
	Este método copia o conteúde de	'pixels' para os pixels da textura.
	Esta é uma operação MUITO lenta e deve ser usada apenas quando for realmente necessária. 
	Params:
		pixels: ponteiro contendo o novo array de pixels da textura.
		pitch: inteiro contendo o valor do pitch (bytes por linha) da textura.
	Retorno:
		Uma booleana indicando se a operação foi bem sucessedida ou não.
	*/
	bool atualizarPixels(void* pixels, int pitch);

	//	Funciona parcialmente:
	//	Não copia os pixels de uma textura estatica que não foi criada de um arquivo.
	//	Neste caso, cria uma textura com o mesmo tamanho mas transparente.
	//	Quando a textura é estatica, mas foi criada a partir de um arquivo, cria outra
	//	textura a partir do mesmo arquivo.
	//	Quando a textura é de streaming, copia os pixels de uma para a outra.
	Textura clonar();

private:
	bool travada;
	string caminhoArquivo;
};

#endif