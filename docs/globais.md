
# Globais

* [libUnicornio.h](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/include/libUnicornio.h)
* [libUnicornio.cpp](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/src/libUnicornio.cpp)

Lista de váriaveis e funções que podem ser usadas através da libUnicornio.

## Váriaveis

### res_x

Retorna a largura da tela definida na função __uniInicializar__.

### res_y

Retorna a altura da tela definida na função __uniInicializar__.

## Funções

### __uniInicializar__

Esta função inicializa a renderização da janela da aplicação, o mixador de áudio, o carregamento da fonte padrão, os handlers de eventos e o cálculo do framerate. Caso todos passos sejam executados corretamente a função irá retornar um __boolean__ com valor _true_. Caso contrário retornará _false_ ou uma excessão.

```c
// resolucao_x, resolucao_y, tela_cheia, titulo_janela
uniInicializar(800, 600, false, "My Game");
```

### __uniFinalizar__

Está função finaliza toda a aplicação descarregando os seguintes componentes:

* Finalizar as mensagens de debug.
* Descarregar todos os recursos.
* Descarregar a fonte padrão e as bibliotecas de fontes.
* Finalizar o áudio e vídeo.
* Finalizar a biblioteca SDL.
* Setar a váriavel global __uni_init__ para _false_.


### __uniDesenharTexto__

Esta função utiliza a classe __Texto__ para criar uma instância e desenhar na tela o texto definido.

> Cuidado: Esta função irá utilizar mais processamento que a utilização de uma única instância da classe __Texto__,
pois a cada iteração do jogo será criado e destruido uma nova instância de __Texto__.

```c
uniDesenharTexto("Pressione [ENTER]", 10, 10, 255, 255, 255, 0.0f);
```

### __uniIniciarFrame__

Esta função irá dar ínicio ao próximo frame do jogo controlando seu framerate e processando os eventos da tela. Por isso é necessário que durante o loop de execução essa função seja chamada primeiro para evitar que frames sejam perdidos e eventos não sejam executados.

### __uniTerminarFrame__

Esta função é responsável por desenhar a tela do jogo. Sendo por isso que é preciso chamá-la por último dentro do loop de execução.

### __uniColisao__


Esta função irá testar a colisão entre um __ponto__ e um __Sprite__, ou a colisão de dois __Sprites__.

A colisão de um ponto com o __Sprite__ utiliza um algoritmo de um ponto dentro de um retângulo. É um teste simples, 
pois possui menos chance de erro.

```c
// colisao de mouse com tiro
if(uniColisao(mouse.x, mouse.y, tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), 
              tiro.getRot()))
{
    ...
}
```

A colisão entre dois __Sprites__ utiliza um algoritmo que testa a colisão entre dois retângulos, precisando várias verificações
para dizer que houve colisão.

```c
// colisao de tiro com nave
if(uniColisao(tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot(),
              nave.getSprite(), nave.getPosX(), nave.getPosY(), nave.getRot()))
{
    ...
}
```


### __uniSetCorDeFundo__

Esta função é uma forma simples de mudar a cor de fundo da tela.

```c
//	muda cor de fundo para azul
uniSetCorDeFundo(0, 0, 255);
```

### __uniDepurar__ 

Para depurar os valores das váriaveis e objetos que estão no jogo, você pode utilizar a função global __uniDepurar__, passando uma label e um valor que serão adicionados na tela e desenhados por cima do jogo.

```c
uniDepurar("x: ", player.getX());
uniDepurar("y: ", player.getY());
```