
# Texto

* [Texto.h](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/include/Midia/Texto.h)
* [Texto.cpp](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/src/Midia/Texto.cpp)

Texto é uma classe utilizada para apresentar textos na tela, podendo customizar a fonte, a cor, o alinhamento e o espaçamento.


## Caregando a fonte

Carrega os arquivos de fontes utilizando o objeto estático [__recursos__](./recursos).

> _O carregamento da fonte deve ser chamado apenas na inicialização da aplicação, caso seja chamada durante o jogo rodando pode comprometer o desempenho do jogo._

```c
// Jogo.cpp
// Carregar as fontes (passando o tamanho da fonte como parametro)
recursos.carregarFonte("fonte1", "dados/fontes/morohashi.ttf", 32);
```

## Selecionando a fonte

Crie uma instância da classe __Texto__.

```c
Texto texto;
```

Selecione a fonte que foi carregada passando o nome dela.

```c
// Setar a fonte e a string do texto
texto.setFonte("fonte1");
```

Informar o texto que será visualizado.

```c
texto.setString("Este eh\num texto de\nexemplo!");
```

Para desenhar o texto na tela é preciso passar a função __desenhar__ passando a posição x e y na tela. É também possivel passar como terceiro parametro a rotação.

```c
// Desenhar o texto (x, y, rotaçao)
texto.desenhar(res_x/2, res_y/2);  //  bem no meio da tela
```

Ao finalizar a aplicação não esqueça de descarregar da memória as fontes que foram carregadas.

```c
// Descarregar tudo
recursos.descarregarTudo();
```


## Customizando

### Cor

Para customizar a cor, chame o método __setCor__ passando os parametros "vermelho, verde, azul, alpha" com os valores entre 0 e 255.

```c
// Setar cor para os textos. O padrão é branco.
texto.setCor(0, 255, 0, 255);
```

### Alinhamento

Para selecionar o alinhamento do texto, chame o método __setAlinhamento__ passando como parametro os três possiveis valores _enum_: 

* TEXTO_ALINHADO_A_ESQUERDA
* TEXTO_ALINHADO_A_DIREITA
* TEXTO_CENTRALIZADO

```c
// Setar alinhamento. O padrão é alinhado à esquerda.
texto.setAlinhamento(TEXTO_CENTRALIZADO);
```

### Espaçamento

```c
// Setar espaçamento das linhas. O padrão é 1.0f.
texto.setEspacamentoLinhas(1.5f);
```

## Exemplo completo

```c
#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
    uniInicializar(800, 600, false);

    // Carregar as fontes (passando o tamanho da fonte como parametro)
    recursos.carregarFonte("fonte1", "dados/fontes/morohashi.ttf", 32);

    // Setar a fonte e a string do texto
    texto.setFonte("fonte1");
    texto.setString("Este eh\num texto de\nexemplo!");

    // (Opcional) Setar cor para os textos. O padrão é branco.
    texto.setCor(0, 255, 0);

    // (Opcional) Setar alinhamento. O padrão é alinhado à esquerda.
    texto.setAlinhamento(TEXTO_CENTRALIZADO);

    // (Opcional) Setar espaçamento das linhas. O padrão é 1.0f.
    texto.setEspacamentoLinhas(1.5f);
}

void Jogo::finalizar()
{
    // Descarregar tudo
    recursos.descarregarTudo();

    uniFinalizar();
}

void Jogo::executar()
{
    while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
    {
        uniIniciarFrame();

        // Desenhar o texto (x, y, rot)
        texto.desenhar(res_x/2, res_y/2);       //  bem no meio da tela

        uniTerminarFrame();
    }
}
```


