
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

Centralize o mapa de acordo com a tela com o método __setPosCentro__ e desenhe com o método __desenhar__.

```c
// centraliza o mapa
mapa.setPosCentro(res_x/2, res_y/2);

// desenhar o tilemap
mapa.desenhar();
```

Com isso você já deve conseguir ver o tilemap sendo renderizado na tela.

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

