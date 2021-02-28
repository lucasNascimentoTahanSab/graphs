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
 * meio da lista de ponteiros 'arestas'. As 'Arestas'
 * sao ponderadas e contem ponteiro para uma de suas
 * extremidades.
 */
struct Grafo
{
  struct Vertice **vertices;
} * grafo;

struct Vertice
{
  char identificador;
  struct Aresta **arestas;
};

struct Aresta
{
  double peso;
  struct Vertice *vertice;
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
void inserirAresta(char, char, double);
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
void inicializarArestas(struct Vertice *);
int existeVerticeEmArestas(struct Vertice *, struct Aresta **);
void removerArestasDoVertice(struct Vertice *);
void vincularVertices(struct Vertice *, struct Vertice *, double);
void desvincularVertices(struct Vertice *, struct Vertice *);
void mostrarRelacoes(struct Aresta **);

/**
 * Metodos de funcionalidades 
 * auxiliares.
 */
int selecionarOpcao();
char obterIdentificadorVertice();
double obterPesoAresta();
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
      inserirAresta(obterIdentificadorVertice(), obterIdentificadorVertice(), obterPesoAresta());
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
      inicializarArestas(grafo->vertices[i]);
      break;
    }
  }
}

void inserirAresta(char primeiroIdentificador, char segundoIdentificador, double peso)
{
  if (primeiroIdentificador == segundoIdentificador)
    return;

  struct Vertice *primeiroVertice = obterVertice(primeiroIdentificador);
  struct Vertice *segundoVertice = obterVertice(segundoIdentificador);
  if ((primeiroVertice != NULL && segundoVertice != NULL) && !existeAresta(primeiroVertice, segundoVertice))
  {
    vincularVertices(primeiroVertice, segundoVertice, peso);
    vincularVertices(segundoVertice, primeiroVertice, peso);
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
      mostrarRelacoes(grafo->vertices[i]->arestas);
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
  if (obterVertice(identificador) != NULL)
    return 1;
  else
    return 0;
}

int existeAresta(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  if (primeiroVertice->arestas == NULL || segundoVertice->arestas == NULL)
    return 0;

  return existeVerticeEmArestas(segundoVertice, primeiroVertice->arestas);
}

void inicializarArestas(struct Vertice *vertice)
{
  vertice->arestas = (struct Aresta **)malloc(VERTICES_TOTAIS * sizeof(struct Aresta **));
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
    vertice->arestas[i] = NULL;
}

int existeVerticeEmArestas(struct Vertice *verticePesquisado, struct Aresta **arestas)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (arestas[i] != NULL && arestas[i]->vertice == verticePesquisado)
      return 1;
  }

  return 0;
}

void removerArestasDoVertice(struct Vertice *vertice)
{
  for (struct Aresta *i = vertice->arestas[0]; i != NULL; i = vertice->arestas[0])
    removerAresta(vertice->identificador, i->vertice->identificador);
}

void vincularVertices(struct Vertice *primeiroVertice, struct Vertice *segundoVertice, double peso)
{
  struct Aresta *aresta = (struct Aresta *)malloc(sizeof(struct Aresta *));
  aresta->vertice = segundoVertice;
  aresta->peso = peso;

  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (primeiroVertice->arestas[i] == NULL)
    {
      primeiroVertice->arestas[i] = aresta;
      break;
    }
  }
}

void desvincularVertices(struct Vertice *primeiroVertice, struct Vertice *segundoVertice)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (primeiroVertice->arestas[i] != NULL && primeiroVertice->arestas[i]->vertice == segundoVertice)
    {
      if (i == VERTICES_TOTAIS - 1)
        primeiroVertice->arestas[i] = NULL;
      else
      {
        for (int j = i; j < VERTICES_TOTAIS - 1; j++)
          primeiroVertice->arestas[j] = primeiroVertice->arestas[j + 1];
      }

      break;
    }
  }
}

void mostrarRelacoes(struct Aresta **arestas)
{
  for (int i = VERTICE_INICIAL; i < VERTICES_TOTAIS; i++)
  {
    if (arestas[i] != NULL)
      printf("%c(%.2lf) ", arestas[i]->vertice->identificador, arestas[i]->peso);
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

double obterPesoAresta()
{
  double peso;
  printf("Insira um peso para a aresta: ");
  scanf("%lf", &peso);
  limparEntrada();

  return peso;
}

void limparEntrada()
{
  char entrada;
  scanf("%c", &entrada);
}