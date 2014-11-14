libUnicornio
============

Uma biblioteca didática para o desenvolvimento de jogos digitais 2D. 

## Como instalar

Faça o download do repositório: [Link de Download](https://github.com/GuilhermeAlanJohann/libUnicornio/archive/master.zip)

Após o download descompacte  o arquvo *.zip*.

## Como usar

Para começar a utilizar a *libUnicornio* vamos utilizar o projeto *base_2012*.

Entre no diretório *projetos/base_2012*, nele se encontra o arquivo *main.cpp*:

**main.cpp**
```c++
#include "Jogo.h"

int main(int argc, char* argv[])
{
	Jogo jogo;
	jogo.inicializar();
	jogo.executar();
	jogo.finalizar();

	return 0;
}
```

A função *main* cria uma instância da classe Jogo, e chama seus métodos que criam toda lógica do jogo através da libUnicornio.
Para começar a programar seu jogo abra o arquivo Jogo.cpp.

### Inicializar

Neste arquivo você terá o método *Jogo::inicializar()* para fazer a configuração do seu jogo.

**Jogo.cpp**
```c++
void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	//	O resto da inicialização vem aqui!
	//	...
}
```

### Finalizar

O método *Jogo::finalizar()* é utilizado para finalizar o jogo. Podendo deixar aqui o cargo de salvar um arquivo de restituição, ou por exemplo, desalocar memória dos ponteiros.

**Jogo.cpp**
```c++
void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	uniFinalizar();
}
```

### Executando

O método *Jogo::executar()* será o responsável por manter o jogo em andamento utilizando um *while* que segue até o usuário teclar ESC no seu teclado ou o sistema setar a propriedade *aplicacao.sair* como true.

**Jogo.cpp**
```c++
void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	Seu código vem aqui!
		//	...

		uniTerminarFrame();
	}
}
```

Após o jogo sair dessa fase, a *libUnicornio* chamará o método *Jogo::finalizar()* e a janela de visualização será fechada.
