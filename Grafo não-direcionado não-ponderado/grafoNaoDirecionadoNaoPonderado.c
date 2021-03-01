#include <stdlib.h>
#include <stdio.h>

int const VERTICES_TOTAIS = 10;
int const VERTICE_INICIAL = 0;

/**
 * Estruturas responsaveis pela modelagem do 
 * Grafo na implementacao, sendo a struct 'Grafo'
 * representante do componente, contendo uma lista
 * de ponteiros para estruturas do tipo 'Vertice'.
 * Os 'Vertices' se associam a outros 'Vertices' por 
 * meio da lista de ponteiros 'vertices'. 
 */
struct Grafo
{
  struct Vertice **vertices;
} * grafo;

struct Vertice
{
  char identificador;
  struct Vertice **vertices;
};

/**
 * Metodos de inicializacao 
 * da implementacao. 
 */
void iniciar();
void inicializarVariaveis();
void apresentarOpcoes();

/**
 * Metodos de manipulacao do
 * 'Grafo' (insercao, remocao e
 * leitura).
 */
void inserirVertice(char);
void inserirAresta(char, char);
void removerVertice(char);
void removerAresta(char, char);
void mostrarVerticesERelacoes();
struct Vertice *obterVertice(char);

/**
 * Metodos de funcionalidades auxiliares
 * para manipulacao do 'Grafo'. 
 */
int existeVertice(char);
int existeAresta(struct Vertice *, struct Vertice *);
void inicializarVertices(struct Vertice *);
int verticeEstaAssociado(struct Vertice *, struct Vertice **);
void removerArestasDoVertice(struct Vertice *);
void vincularVertices(struct Vertice *, struct Vertice *);
void desvincularVertices(struct Vertice *, struct Vertice *);
void mostrarRelacoes(struct Vertice *);

/**
 * Metodos de funcionalidades 
 * auxiliares.
 */
int selecionarOpcao();
char obterIdentificadorVertice();
void limparEntrada();

int main(int argc, char const *argv[])
{
  iniciar();
}

void iniciar()
{
  inicializarVariaveis();
  apresentarOpcoes();
}

void inicializarVariaveis()
{
  grafo = (struct Grafo *)malloc(sizeof(struct Grafo *));
  grafo->vertices = (struct Vertice **)malloc(VERTICES_TOTAIS * sizeof(struct Vertice **));
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
    grafo->vertices[i] = NULL;
}

void apresentarOpcoes()
{
  int opcaoEscolhida;
  do
  {
    opcaoEscolhida = selecionarOpcao();
    switch (opcaoEscolhida)
    {
    case 0:
      inserirVertice(obterIdentificadorVertice());
      break;
    case 1:
      removerVertice(obterIdentificadorVertice());
      break;
    case 2:
      inserirAresta(obterIdentificadorVertice(), obterIdentificadorVertice());
      break;
    case 3:
      removerAresta(obterIdentificadorVertice(), obterIdentificadorVertice());
      break;
    case 4:
      mostrarVerticesERelacoes();
      break;
    default:
      break;
    }
  } while (opcaoEscolhida != 5);
}

void inserirVertice(char identificador)
{
  if (existeVertice(identificador))
    return;

  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (grafo->vertices[i] == NULL)
    {
      grafo->vertices[i] = (struct Vertice *)malloc(sizeof(struct Vertice *));
      grafo->vertices[i]->identificador = identificador;
      inicializarVertices(grafo->vertices[i]);
      break;
    }
  }
}

void inserirAresta(char primeiroIdentificador, char segundoIdentificador)
{
  if (primeiroIdentificador == segundoIdentificador)
    return;

  struct Vertice *primeiroVertice = obterVertice(primeiroIdentificador);
  struct Vertice *segundoVertice = obterVertice(segundoIdentificador);
  if ((primeiroVertice != NULL && segundoVertice != NULL) && !existeAresta(primeiroVertice, segundoVertice))
  {
    vincularVertices(primeiroVertice, segundoVertice);
    vincularVertices(segundoVertice, primeiroVertice);
  }
}

void removerVertice(char identificador)
{
  if (!existeVertice(identificador))
    return;

  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (grafo->vertices[i]->identificador == identificador)
    {
      removerArestasDoVertice(grafo->vertices[i]);
      for (int j = i; j < VERTICES_TOTAIS - 1; j++)
        grafo->vertices[j] = grafo->vertices[j + 1];
      break;
    }
  }
}

void removerAresta(char primeiroIdentificador, char segundoIdentificador)
{
  struct Vertice *primeiroVertice = obterVertice(primeiroIdentificador);
  struct Vertice *segundoVertice = obterVertice(segundoIdentificador);
  if ((primeiroVertice != NULL && segundoVertice != NULL) && existeAresta(primeiroVertice, segundoVertice))
  {
    desvincularVertices(primeiroVertice, segundoVertice);
    desvincularVertices(segundoVertice, primeiroVertice);
  }
}

void mostrarVerticesERelacoes()
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (grafo->vertices[i] != NULL)
    {
      printf("%c possui relacao com: ", grafo->vertices[i]->identificador);
      mostrarRelacoes(grafo->vertices[i]);
    }
    else
      break;
    printf("\n");
  }
}

struct Vertice *obterVertice(char identificador)
{
  struct Vertice *vertice = NULL;
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (grafo->vertices[i] != NULL && grafo->vertices[i]->identificador == identificador)
      vertice = grafo->vertices[i];
    else if (grafo->vertices[i] == NULL)
      break;
  }

  return vertice;
}

int existeVertice(char identificador)
{
  return obterVertice(identificador) != NULL;
}

int existeAresta(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  if (primeiroVertice->vertices == NULL || segundoVertice->vertices == NULL)
    return 0;

  return verticeEstaAssociado(segundoVertice, primeiroVertice->vertices);
}

void inicializarVertices(struct Vertice *vertice)
{
  vertice->vertices = (struct Vertice **)malloc(VERTICES_TOTAIS * sizeof(struct Vertice **));
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
    vertice->vertices[i] = NULL;
}

int verticeEstaAssociado(struct Vertice *verticePesquisado, struct Vertice **verticesAssociados)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (verticesAssociados[i] == verticePesquisado)
      return 1;
  }

  return 0;
}

void removerArestasDoVertice(struct Vertice *vertice)
{
  for (struct Vertice *i = vertice->vertices[0]; i != NULL; i = vertice->vertices[0])
    removerAresta(vertice->identificador, i->identificador);
}

void vincularVertices(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (primeiroVertice->vertices[i] == NULL)
    {
      primeiroVertice->vertices[i] = segundoVertice;
      break;
    }
  }
}

void desvincularVertices(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (primeiroVertice->vertices[i]->identificador == segundoVertice->identificador)
    {
      if (i == VERTICES_TOTAIS - 1)
        primeiroVertice->vertices[i] = NULL;
      else
      {
        for (int j = i; j < VERTICES_TOTAIS - 1; j++)
          primeiroVertice->vertices[j] = primeiroVertice->vertices[j + 1];
      }

      break;
    }
  }
}

void mostrarRelacoes(struct Vertice *vertice)
{
  struct Vertice **relacoes = vertice->vertices;
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (relacoes[i] != NULL)
      printf("%c ", relacoes[i]->identificador);
    else
      break;
  }
}

int selecionarOpcao()
{
  int opcaoEscolhida;
  printf("\n");
  printf("Escolha a opcao desejada:\n");
  printf("0 - Inserir vertice\n");
  printf("1 - Remover vertice\n");
  printf("2 - Inserir aresta\n");
  printf("3 - Remover aresta\n");
  printf("4 - Apresentar vertices e relacoes\n");
  printf("5 - Sair\n");
  printf("\n");
  scanf("%d", &opcaoEscolhida);
  printf("\n");
  limparEntrada();

  return opcaoEscolhida;
}

char obterIdentificadorVertice()
{
  char identificador;
  printf("Insira um identificador de 1 caractere para o vertice: ");
  scanf("%c", &identificador);
  limparEntrada();

  return identificador;
}

/**
 * Metodo de controle para evitar
 * captura da tecla enter ao inserir
 * um novo valor. 
 */
void limparEntrada()
{
  char entrada;
  scanf("%c", &entrada);
}