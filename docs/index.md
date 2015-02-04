
# Bem-vindo à documentação da libUnicornio


## Requisitos

* __Sistema Operacional Windows 7+__
* __Visual Studio 2012__: O projeto base é um projeto feito com a IDE Microsoft Visual Studio 2012 e está totalmente configurado para usar a biblioteca.

## Como começar a usar ?

Para começar a utilizar a biblioteca Unicórnio é recomendado que você use o projeto base.

Vá ao diretório "projetos" e você encontrará a pasta "base_2012". Essa pasta contém o projeto base. 

> Para garantir que você sempre tenha o projeto base intacto, faça um backup do mesmo, ou utilize uma cópia dele. 

Neste caso, utilizaremos uma cópia. Copie a pasta "base_2012" e cole dentro do mesmo diretório.

> Agora você terá uma pasta chamada "base_2012" e outra chamada "base_2012 - Cópia".
> A primeira servirá como backup, e a segunda será a pasta do projeto que você irá trabalhar.

Primeiramente, renomeie a pasta "base_2012 - Cópia" para o nome do seu jogo. Ex: "Meu primeiro Jogo".  
Abra esta pasta e você encontrará os arquivos do projeto configurados para o Visual Studio 2012.

Abra o projeto com o visual Studio 2012 e você verá que ele já vem com um código base, que inclui uma classe chamada Jogo.  
No arquivo main.cpp, a função 'main' cria uma instância da classe Jogo, e chama seus métodos que determinam o fluxo da aplicação.

```c++
  // main.cpp
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

## Inicializar

Para começar a programar seu jogo abra o arquivo Jogo.cpp.

A classe Jogo é composta por 3 métodos. Cada um responssável por uma etapa do jogo: Inicialização, Execução e Finalização. 

A etapa de inicialização é feita pelo método 'Jogo::inicializar()'.

Ele serve para fazer a inicialização dos dados do jogo. Carregamento de arquivos, alocação de memória, configurações iniciais, etc. Para isso, antes de tudo, ele chama uma função 'uniInicializar' que inicializa a biblioteca Unicórnio, confugurando a resolução da janela, e deixa ele pronta para uso.

> Repare que ele já vem comentado, indicando o local onde o seu código deve ir.

```c++
  // Jogo.cpp
  
  
  void Jogo::inicializar()
  {
      uniInicializar(800, 600, false);
  
      //  O resto da inicialização vem aqui!
      //  ...
  }

```

## Finalizar


Em seguida, de uma olhada do método 'Jogo::finalizar()'. Quando o seu jogo terminar de executar, esse é o método que será chamado.

Ele é a contra-parte do método 'Jogo::inicializar()' e serve para fazer a finalização dos dados do jogo. Dealocação de memória, salvar informações em arquivos, etc.

Além disso, ele também serve para finalizar a biblioteca Unicórnio, através da função 'uniFinalizar'.
 
> Repare que ele também vem comentado, indicando onde o seu código deve ir.

```c++
  // Jogo.cpp
  
  void Jogo::finalizar()
  {
      //  O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
      //  ...
  
      uniFinalizar();
  }
```

## Executar

Por fim, veja o método 'Jogo::executar()'. Ele é o mais importante dois três e controla o loop do jogo.

Ele serve para executar a lógica do jogo. Movimentação, colisão, animações, renderização, etc.  
Este método fica executando operações basicas ao inicio e fim de cada frame, como: captura de inputs, controle de tempo e renderização.  

Tudo isso fica dentro de um comando de laço 'while', que executa enquanto o usuário não pressionar a tecla ESC, ou clicar no botão de fechar da janela.  
> Repare que ele também vem comentado, indicando onde o seu código deve ir.  

```c++
  // Jogo.cpp
  
  
  void Jogo::executar()
  {
      while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
      {
          uniIniciarFrame();
  
          //  Seu código vem aqui!
          //  ...
  
          uniTerminarFrame();
      }
  }
```

#### Pronto! Agora vc já sabe como começar a usar a bibliteca Unicórnio.

Consulte os exemplos para saber como usar uma funcionalizade específica. Ex: Sprites, Testes de colisão, TileMap.  
Caso ainda tenha alguma dúvida, mande e-mail para '<pcista@hotmail.com>'. E sugira modificações neste tutorial

Obrigado!!!

