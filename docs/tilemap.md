
# TileMap

* [TileMap.h](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/include/TileMap/TileMap.h)
* [TileMap.cpp](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/src/TileMap/TileMap.cpp)

Para criar um tilemap você deve utilizar o software Tiled Map Editor: 

<http://www.mapeditor.org>

Faça o download do software e então crie o seu tilemap com ele. Após criar o tilemap, exporte ele para o formato __json__ ([link](#exemplos)).

Se for necessário (provavelmente será), arrume o caminho para os arquivos de tileset.

* Para fazer isso, abra o arquivo do mapa em um editor de textos e procure o local onde estão contidas as informações dos tileset que você usou.

* No campo __image__ digite o caminho correto para a imagem do tileset.

* Salve o arquivo novamente e ele estará pronto para usar com a libUnicornio.

```json
{
  ...
  "tilesets":[
        {
         ...
         "image":"dados/tilemaps/tilesets/tileset_campo.png", // <--
         "name":"tileset campo",
         ...
        }
  ],
  ...
}
```

## Configuração do TileSet

Antes de poder partir para o código do jogo é preciso criar a configuração do TileSet. Esta configuração ficara dentro de um arquivo txt setado pelo caminho que está dentro do arquivo json do tilemap:

```json
{
  ...
  "tilesets":[
        {
         ...
         "name":"tileset campo",
         "properties":
            {
             "config":"dados\/tilemaps\/tileset_configs\/campo config.txt"  // <--
            },
         ...
        }
  ],
  ...
}
```

A configuração possui as seguintes informações:

* O caminho da imagem tileset.
* O tamanho de cada tile, largura e altura.
* Matriz com os pontos que são caminhaveis pelos objetos do jogo através de mapeamentos.
    * 0 - não caminhavel
    * 1 - caminhavel
* Matriz do nível de cada tile em relação aos objetos.
    * 0 - abaixo dos objetos
    * 1 - no nivel dos objetos
    * 2 - acima dos objetos
* Matriz de inteiros que informa o custo adicional de tile na hora de calcular o caminho com o algoritmo A\* esta 
informação é usada apenas pelo algorimo de pathfinding A\*.

Exemplo da configuração de um tilemap de um campo.

```json
dados/tilemaps/tilesets/tileset_campo.png
32 32

# caminhavel
*
1 1 1 1 0 1 0 0
1 1 1 1 0 1 0 0
1 1 1 1 1 1 0 0
1 1 1 1 1 0 0 0
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 0 0 1 1 0 0 1

# nivel
*
0 0 0 0 1 0 1 1
0 0 0 0 1 0 1 1
0 0 0 0 0 0 1 1
0 0 0 0 0 1 1 1
0 0 0 0 0 0 0 0
0 2 2 0 0 2 2 0
2 2 2 2 2 2 2 2
2 2 2 2 2 2 2 2
2 1 1 2 2 1 1 2
0 1 1 0 0 1 1 0

# custo adicional
*
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
```

## Carregando o Tilemap

Com todas as configurações prontas, crie uma instância da classe __TileMap__ e carregue o arquivo json.

```c
// instância de um tilemap
TileMap mapa;

// carregar o tilemap
mapa.carregar("dados/tilemaps/mapa_campo.json");
```

Centralize o mapa a partir das coordenadas passadas ao método __setPosCentro__, ficando pronto para ser desenhado na tela com o método __desenhar__.

```c
// centraliza o mapa
mapa.setPosCentro(35.0, 7.5);

// desenhar o tilemap
mapa.desenhar();
```

Com isso você já deve conseguir ver o tilemap sendo renderizado na tela.

## Usando Objetos

<!-- O TileMap Editor possui uma camada chamada __Camada de Objetos__ onde permite adicionar __objetos__ com informações como posição e tamanho, essas informações são vistas através de seus atributos. É possivel adicionar mais atributos dos que vem por padrão, mas o atributo principal é o __nome__ que será necessário para podermos carregar no jogo. -->

O TileMap Editor permite você adicionar camadas de objetos ao seu mapa. Esses objetos são usados para representar os objetos do seu jogo (personagens, itens, áreas de colisão, coisas que se movem, etc).  

> Na libUnicornio, esses objetos são chamados de __ObjetoTile__.  
> Um ObjetoTile possui nome, tipo, posição, tamanho e propriedades.  

Para acessar um objeto, você deve primeiro obter a camada em que este objeto está passando o nome como parâmetro.
Depois, buscar pelo objeto também passando o nome como parâmetro.

```c
// Informe o nome da camada para obtê-la
CamadaDeObjetos * camadaObjetos =  mapa.getCamadaDeObjetos("Objetos");

// Informe o nome do objeto para obtê-lo
ObjetoTile * objetoTile = camadaObjetos->getObjeto("Player");
```

Agora, com um ponteiro para o objeto você pode acessar seus atributos e propriedades assim: 

```c
float x = objetoTile->getXCentro();
float y = objetoTile->getYCentro();

// setando um texto como propriedade
string texto = "Um texto qualquer!";
objetoTile->setPropriedade("texto", texto);
```

#### Desenhando Objetos

<!-- Agora podemos adicionar na inicialização um __Sprite__ ao __ObjetoTile__ e controlar sua animação.  -->

Para desenhar um objeto junto ao seu TileMap, você vai precisar de um __Sprite__. Inicialize o __Sprite__ previamente e então agregue ele ao __ObjetoTile__ usando o método __setSprite__.

<!-- Ao fazer isso, o sprite passa a ser desenhado automaticamente junto com o mapa, na posição central do objeto, então não é preciso chamar sprite.desenhar(x, y). -->

```c
// carregar spritesheet para o player
recursos.carregarSpriteSheet("player", "dados/spritesheets/player.png", 4, 4);

Sprite sprite;

//  setar spritesheet
sprite.setSpriteSheet(sheet);

//  setar ancora para os pes do personagem
sprite.setAncora(0.5, 0.75);

//  set vel anim (4 frames por segundo)
sprite.setVelocidadeAnimacao(4.0);

//  setar sprite para o objeto
objetoTile->setSprite(&sprite);
```

Dessa forma, o __Sprite__ será desenhado junto ao mapa, na posição central do __ObjetoTile__, sempre que você chamar o método __desenhar__ da classe __TileMap__. 

Essa forma de desenho garante que os objetos sejam desenhados na ordem correta, respeitando o nível de cada tile. Isso permite que os objetos possam em alguns momentos, dependendo da sua posição, serem desenhado na frente, em outros atrás, de alguns tiles. Um típico exemplo disso, é um personagem passando pela frente e por trás de um árvore.

#### Movimentando o ObjetoTile

Para mover o ObjetoTile junto com a tela é preciso infomar a posição central do __objetoTile__ e do __mapa__. Assim caso o __objetoTile__ sejá o personagem sendo controlado, ele irá ficar centralizado na tela.

```c
// setar posicao atual para o objeto no mapa
objetoTile->setPosCentro(x, y);

// centraliza o mapa na posicao do objeto
mapa.setPosCentro(objetoTile->getXCentro(), objetoTile->getYCentro());
```

Para verificar se um tile é caminhavel pelo ObjetoTile utilize o método __tileECaminhavel__ passando suas coordenadas.

```c
if(mapa.tileECaminhavel(x, y))
{
  // ...
}
```

Para verificar se a posição em que o ObjetoTile está existe outro objeto, você poderá utilizar o método __existeObjetoDoTipoNaPos__ informando o tipo do objeto e a posição do seu __ObjetoTile__.

```c
// Váriaveis temporárias para melhor visualização do exemplo
float x = objetoTile->getXCentro();
float y = objetoTile->getYCentro();

// Caso haja um objeto do tipo "Arvore Seca" no mesmo tile que o objetoTile
if(mapa.existeObjetoDoTipoNaPos("Arvore Seca", x, y))
{
  // ...
}
```
## Descarregar TileMap

Ao finalizar a execução do jogo, é preciso descarregar os tilemaps que foram carregados.

```c
// descarregar o tilemap
mapa.descarregar();
```

## Exemplos

Amostra do formato do arquivo json utilizado para montar o tilemap na libUnicornio.

```json
{ 
 "height":40,
 "layers":[
        {
         "data":[1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,],
         "height":40,
         "name":"Chao",
         "opacity":1,
         "type":"tilelayer",
         "visible":true,
         "width":50,
         "x":0,
         "y":0
        }, 
        {
         "data":[0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          26, 26, 27, 0, 0, 0, 0, 49, 50, 49, 50,
          26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
          26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 45, 46, 47,
          48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 26, 26, 26, 26, 29, 18, 18, ],
         "height":40,
         "name":"Meio",
         "opacity":1,
         "type":"tilelayer",
         "visible":true,
         "width":50,
         "x":0,
         "y":0
        }, 
        {
         "height":40,
         "name":"Objetos",
         "objects":[
                {
                 "height":32,
                 "name":"Player",
                 "properties":
                    {

                    },
                 "type":"Player",
                 "visible":true,
                 "width":32,
                 "x":1120,
                 "y":224
                }],
         "opacity":1,
         "type":"objectgroup",
         "visible":true,
         "width":50,
         "x":0,
         "y":0
        }],
 "orientation":"orthogonal",
 "properties":
    {

    },
 "tileheight":32,
 "tilesets":[
        {
         "firstgid":1,
         "image":"dados/tilemaps/tilesets/tileset_campo.png",
         "imageheight":320,
         "imagewidth":256,
         "margin":0,
         "name":"tileset campo",
         "properties":
            {
             "config":"dados\/tilemaps\/tileset_configs\/campo config.txt"
            },
         "spacing":0,
         "tileheight":32,
         "tilewidth":32
        }],
 "tilewidth":32,
 "version":1,
 "width":50
}
```

