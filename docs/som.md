
# Som

* [Som.h](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/include/Midia/Som.h)
* [Som.cpp](https://github.com/GuilhermeAlanJohann/libUnicornio/blob/master/libUnicornio/src/Midia/Som.cpp)


A classe Som é responsável por manipular o áudio durante o jogo, para isso ela possui métodos como alterar o volume e executar o som. Por baixo ela utiliza duas classes para poder setar a distância e ângulo do som, __Audio__ e __MixadorDeAudios__.

## Carregando o áudio


Para carregar os arquivos de áudio, utilize o objeto global __recursos__, passando o nome do som e local do arquivo. Atualmente a libUnicornio aceita apenas arquivos de áudio no formato __wav__.

```c
// carregar áudio
recursos.carregarAudio("tiro", "dados/sons/shot.wav");
```

## Utilizando o som

Para utilizar o arquivo de áudio que foi carregado, crie uma instância de __Som__ e sete seu áudio com o nome que recebeu ao ser carregado, neste caso _"tiro"_.

```c
// setar audio no som
Som som;
som.setAudio("tiro");
```

Em seguida já é possível chamar o método __tocar__ para executar o som.

```c
som.tocar();
```

Caso precise regular o som, utilize o método setVolume, passando um valor inteiro entre 0 a 100.

```c
// setar volume (0 - 100)
som.setVolume(50);
```
