#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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
  bool jaPercorrido;
  char *identificador;
  struct Vertice **vertices;
};

/**
 * Metodos responsaveis pela obtencao
 * de todas as combinacoes possiveis
 * de vertices que resultam em 
 * ciclos.
 */
void mostrarCiclosPorVertice();
void mostrarCiclos(struct Vertice *, struct Vertice *, char *);

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
int existeAresta(struct Vertice *, struct Vertice *);
int verticeEstaAssociado(struct Vertice *, struct Vertice **);
void inserirVertice(char *);
void inserirAresta(char *, char *);
void mostrarVerticesERelacoes();
struct Vertice *obterVertice(char *);

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
  mostrarCiclosPorVertice();
}

int numeroDeCiclos = 0;
void mostrarCiclosPorVertice()
{
  for (int i = 0; i < VERTICES_TOTAIS; i++)
  {
    /**
     * Percorrera todos os vertices do grafo e,
     * para cada um, imprimira todos os ciclos
     * possiveis por meio de mostrarCiclos().
     */
    char *ciclo = (char *)malloc(sizeof(char) * VERTICES_TOTAIS);
    mostrarCiclos(grafo->vertices[i], grafo->vertices[i], strcpy(ciclo, grafo->vertices[i]->identificador));
  }
}

void mostrarCiclos(struct Vertice *verticeInicial, struct Vertice *verticeAtual, char *ciclo)
{
  /**
   * Indicara que o vertice atual ja
   * foi percorrido.
   */
  verticeAtual->jaPercorrido = true;

  /**
   * Percorrera todos os vertices associados
   * ao atual. 
   */
  for (int i = 0; i < VERTICES_TOTAIS; i++)
  {
    /**
     * Interrompe se vertice atual nao possuir
     * vertices associados.
     */
    if (verticeAtual->vertices[i] == NULL)
      break;

    /**
     * Pula proximo vertice associado caso este 
     * seja o inicial, porem o ciclo possua apenas 
     * 2 vertices, ou caso nao seja o inicial e ja tenha 
     * sido percorrido.
     */
    if ((verticeAtual->vertices[i] == verticeInicial && strlen(ciclo) <= 2) ||
        (verticeAtual->vertices[i] != verticeInicial && verticeAtual->vertices[i]->jaPercorrido))
      continue;

    /**
     * Caminha ate o proximo vertice associado caso 
     * nao seja o inicial ou imprime ciclo na tela caso
     * seja o inicial e ciclo possua mais de 2 vertices.
     */
    if (verticeAtual->vertices[i] != verticeInicial)
    {
      char *cicloAux = (char *)malloc(sizeof(char) * VERTICES_TOTAIS);
      strcat(strcpy(cicloAux, ciclo), verticeAtual->vertices[i]->identificador);
      mostrarCiclos(verticeInicial, verticeAtual->vertices[i], cicloAux);
    }
    else if (strlen(ciclo) > 2)
      printf("%d. %s%s\n", ++numeroDeCiclos, ciclo, verticeAtual->vertices[i]->identificador);
  }

  /**
   * Marca vertice como nao percorrido apos
   * finalizacao da busca em profundidade 
   * pelos ciclos. 
   */
  verticeAtual->jaPercorrido = false;
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
  inserirVertice("A");
  inserirVertice("B");
  inserirVertice("C");
  inserirVertice("D");
  inserirVertice("E");
  inserirVertice("F");
  inserirAresta("A", "B");
  inserirAresta("A", "D");
  inserirAresta("A", "E");
  inserirAresta("B", "C");
  inserirAresta("B", "D");
  inserirAresta("B", "E");
  inserirAresta("C", "D");
  inserirAresta("C", "E");
  inserirAresta("C", "F");
  inserirAresta("D", "F");
  inserirAresta("E", "F");
}

void inserirVertice(char *identificador)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (grafo->vertices[i] == NULL)
    {
      grafo->vertices[i] = (struct Vertice *)malloc(sizeof(struct Vertice *));
      grafo->vertices[i]->identificador = identificador;
      grafo->vertices[i]->jaPercorrido = false;
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

void inserirAresta(char *primeiroIdentificador, char *segundoIdentificador)
{
  struct Vertice *primeiroVertice = obterVertice(primeiroIdentificador);
  struct Vertice *segundoVertice = obterVertice(segundoIdentificador);
  vincularVertices(primeiroVertice, segundoVertice);
  vincularVertices(segundoVertice, primeiroVertice);
}

struct Vertice *obterVertice(char *identificador)
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

int existeAresta(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  if (primeiroVertice->vertices == NULL || segundoVertice->vertices == NULL)
    return 0;

  return verticeEstaAssociado(segundoVertice, primeiroVertice->vertices);
}

int verticeEstaAssociado(struct Vertice *verticePesquisado, struct Vertice **verticesAssociados)
{
  for (int i = ARESTA_INICIAL; i < ((int)ARESTAS_TOTAIS); i++)
  {
    if (verticesAssociados[i] == verticePesquisado)
      return 1;
  }

  return 0;
}

void mostrarVerticesERelacoes()
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (grafo->vertices[i] != NULL)
    {
      printf("%s possui relacao com: ", grafo->vertices[i]->identificador);
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
      printf("%s ", relacoes[i]->identificador);
    else
      break;
  }
}