
# Recursos 

* [GerenciadorDeRecursos.h](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/include/GerenciadorDeRecursos.h)
* [GerenciadorDeRecursos.cpp](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/src/GerenciadorDeRecursos.cpp)

Para carregar recursos externos como imagens (sprites), áudios e fontes é utilizado uma instância global chamada __recursos__ da classe __GerenciadorDeRecursos__, podendo ser acessado de qualquer lugar na aplicação.

Após o carregamento dos recursos outros módulos ficam livres para utilizá-lo através do nome que foi dado ao recurso durante o carregamento.

## Carregando fontes

Informe o nome, o caminho do arquivo e o tamanho da fonte durante seu carregamento.

```c
recursos.carregarFonte("fonte1", "dados/fontes/morohashi.ttf", 32);
```

## Carregando sprites

A classe __GerenciadorDeRecursos__ utiliza a classe SpriteSheet, que também é utilizada pela classe __Sprite__, para carregar as imagens e dividi-lás em animações.

Após passar por parâmetro o nome e o caminho do arquivo do spritesheet, os dois próximos parâmetros definem a quantidade de animações e o número máximo de frames.

```c
// carregarSpriteSheet(nome, caminho_do_arquivo, numero_animacoes, 
//					   numero_frames_da_maior_animacao);

recursos.carregarSpriteSheet("player", "dados/imagens/sprite_sheet.png", 5, 4);
```

O número máximo de frames define como será dividido o spritesheet em frames, por exemplo, caso a imagem tenha 400px de largura e é passado 4 frames como número máximo, essa imagem será divida em 4 frames de 100px para cada animação.

Caso alguma animação tenha menos frames que o número máximo de frames, é possível setar o número correto de frames que a animação irá utilizar através do método __setNumFramesDaAnimacao__ passando por parâmetro o número da animação e o número de frames.

```c
// setar numero de frames na primeira animacao
// setNumFramesDaAnimacao(numero_animacao, frames)
recursos.getSpriteSheet("player")->setNumFramesDaAnimacao(0, 1);
```

### Adicionando animações

Outra forma de criar as animações é através do método __adicionarAnimacao__ da classe __SpriteSheet__. 

Utilizando o método __getSpriteSheet__ do objeto global __recursos__ para retornar um ponteiro da classe SpriteSheet, é possível utilizar o método __adicionarAnimacao__ passando por parâmetro o ponto no eixo x e y e o tamanho em largura e altura.

```c
// passa as coordenadas do primeiro frame como parâmetro
int anim = recursos.getSpriteSheet("player")->adicionarAnimacao(0, 124, 70, 124);
```

Esse método retornará o número do último frame adicionado, possibilitando a utilização do método __adicionarFrameNaAnimacao__ passando como parâmetro o número do último frame.

```c
// passa as coordenadas dos proximos frame como parâmetro
recursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*2, 70, 124);
recursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*4, 70, 124);
recursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*3, 70, 124);
```

## Carregando áudios

Informe o nome e o caminho do arquivo de áudio que será carregado. Está versão da libUnicornio aceita somente arquivos de áudio no formato __wav__.

```c
// carregar áudio
recursos.carregarAudio("tiro", "dados/sons/shot.wav");
```

## Descarregando tudo

Na finalização da aplicação é preciso chamar o método __descarregarTudo__, com ele todas imagens (spritesheets), audios e fontes serão descarregados.

```c
recursos.descarregarTudo();
```