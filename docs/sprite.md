
# Sprite

* [Sprite.h](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/include/Midia/Sprite.h)
* [Sprite.cpp](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/src/Midia/Sprite.cpp)

A classe __Sprite__ é utilizada para desenhar as imagens e animações carregadas pela classe __SpriteSheet__.

## Carregando o spritesheet

Primeiramente é preciso carregar o spritesheet com o objeto global [__recursos__](./recursos) passando para por parâmetro o nome do sprite, o local do arquivo, o número de animações e o número máximo de frames.

```c
recursos.carregarSpriteSheet("player", "dados/imagens/sprite_sheet.png", 5, 4);
```

> _Acesse o link [__recursos__](./recursos) para ter mais inforações sobre o carregamento dos spritesheets._

Caso precise, também é possível criar outras animações:

```c
// passa as coordenadas do primeiro frame como parâmetro
int anim = recursos.getSpriteSheet("player")->adicionarAnimacao(0, 124, 70, 124);

// passa as coordenadas dos proximos frame como parâmetro
recursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*2, 70, 124);
```

## Utilizando o Sprite

O spritesheet recebeu um nome, que neste caso é _"player"_, esse nome será passado para uma instância da classe __Sprite__.

```c
Sprite sprite;
sprite.setSpriteSheet("player");
```

Para alternar entre as animações chame o método __setAnimacao__ passando o número da animação. Uma forma interessante de organizar o número das animações é utilizando um __enum__, transformando números em labels deixa mais claro qual animação está sendo executada, facilitando o desenvolvimento do jogo.

```c
// Utilizando apenas números
sprite.setAnimacao(1);

// Utilizado enum
enum PersonagemAnim
{
	PARADO,
	GIRANDO
};

sprite.setAnimacao(GIRANDO);
```

Para apenas avançar a animação, chame o método __avancarAnimacao__.

```c
sprite.avancarAnimacao();
```

Para setar um frame específico utilize o método __setFrame__ passando o número do frame.

```c
// mostra o frame 0
sprite.setFrame(0);
```

Por último para desenhar o Sprite na tela, chame o método __desenhar__ passando as coordenadas _x_ e _y_.

```c
// x e y
sprite.desenhar(100, 200);
```