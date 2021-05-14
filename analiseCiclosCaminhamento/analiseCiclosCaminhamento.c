#include <stdlib.h>
#include <stdio.h>

int const VERTICES_TOTAIS = 6;
int const ARESTAS_TOTAIS = 9;
int const VERTICE_INICIAL = 0;
int const ARESTA_INICIAL = 0;
int const BUFFER_MAX = 10;

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
void inicializarComponente();
void inicializarVertices(struct Vertice *);
void inserirVerticesEArestas();

/**
 * Metodos de manipulacao do
 * 'Grafo' (insercao, remocao e
 * leitura).
 */
void inserirVertice(char);
void inserirAresta(char, char);
void mostrarVerticesERelacoes();
struct Vertice *obterVertice(char);

/**
 * Metodos de funcionalidades auxiliares
 * para manipulacao do 'Grafo'. 
 */
void vincularVertices(struct Vertice *, struct Vertice *);
void mostrarRelacoes(struct Vertice *);

int main(int argc, char const *argv[])
{
  inicializarComponente();
  inserirVerticesEArestas();
  mostrarVerticesERelacoes();
}

void inicializarComponente()
{
  grafo = (struct Grafo *)malloc(sizeof(struct Grafo *));
  grafo->vertices = (struct Vertice **)malloc(VERTICES_TOTAIS * sizeof(struct Vertice **));
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
    grafo->vertices[i] = NULL;
}

void inserirVerticesEArestas()
{
  inserirVertice('A');
  inserirVertice('B');
  inserirVertice('C');
  inserirVertice('D');
  inserirVertice('E');
  inserirVertice('F');
  inserirAresta('A', 'B');
  inserirAresta('A', 'D');
  inserirAresta('A', 'E');
  inserirAresta('B', 'C');
  inserirAresta('B', 'D');
  inserirAresta('B', 'E');
  inserirAresta('C', 'D');
  inserirAresta('C', 'E');
  inserirAresta('C', 'F');
  inserirAresta('D', 'F');
  inserirAresta('E', 'F');
}

void inserirVertice(char identificador)
{
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

void inicializarVertices(struct Vertice *vertice)
{
  vertice->vertices = (struct Vertice **)malloc(((int)ARESTAS_TOTAIS) * sizeof(struct Vertice **));
  for (int i = ARESTA_INICIAL; i < ((int)ARESTAS_TOTAIS); i++)
    vertice->vertices[i] = NULL;
}

void inserirAresta(char primeiroIdentificador, char segundoIdentificador)
{
  struct Vertice *primeiroVertice = obterVertice(primeiroIdentificador);
  struct Vertice *segundoVertice = obterVertice(segundoIdentificador);
  vincularVertices(primeiroVertice, segundoVertice);
  vincularVertices(segundoVertice, primeiroVertice);
}

struct Vertice *obterVertice(char identificador)
{
  struct Vertice *vertice = NULL;
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
    if (grafo->vertices[i]->identificador == identificador)
      vertice = grafo->vertices[i];

  return vertice;
}

void vincularVertices(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  for (int i = ARESTA_INICIAL; i < ((int)ARESTAS_TOTAIS); i++)
  {
    if (primeiroVertice->vertices[i] == NULL)
    {
      primeiroVertice->vertices[i] = segundoVertice;
      break;
    }
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

void mostrarRelacoes(struct Vertice *vertice)
{
  struct Vertice **relacoes = vertice->vertices;
  for (int i = ARESTA_INICIAL; i < ((int)ARESTAS_TOTAIS); i++)
  {
    if (relacoes[i] != NULL)
      printf("%c ", relacoes[i]->identificador);
    else
      break;
  }
}