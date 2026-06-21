#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_DADOS "dados.txt"

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    Produto *produtos;
    int capacidade;
    int total;
    float caixa;
} Estoque;

void imprimirSeparador();
Produto *buscarProduto(Estoque *estoque, int codigo);
void inserirProduto(Estoque *estoque, char *nome, int quantidade, float preco);

void aumentarEstoque(Estoque *estoque, int codigo, int quantidade){
    estoque->produtos[codigo].quantidade += quantidade;
    estoque->caixa -= quantidade * estoque->produtos[codigo].preco;
}

void modificarPreco(Estoque *estoque, int codigo, float novoPreco){
    estoque->produtos[codigo].preco=novoPreco;
}
void realizarVenda(Estoque *estoque){
    int k = 0;
    float total=0.0;
    while(k!=-1){
        scanf(" %d",&k);
        printf("%s ",estoque->produtos[k].nome);
        printf("%d\n",estoque->produtos[k].preco);
        total+=estoque->produtos[k].preco;
        estoque->produtos[k].quantidade-=1;
    }
    printf("Total: %.2f\n",total);
    printf("--------------------------------------------------\n");
}
void consultarEstoque(Estoque *estoque){
    for(int i=0;i<(estoque->total);i++){
        printf("%d ",estoque->produtos[i].codigo);
        printf("%s ",estoque->produtos[i].nome);
        printf("%d\n",estoque->produtos[i].quantidade);
    }
    printf("--------------------------------------------------\n");
}
void consultarSaldo(Estoque *estoque){
    printf("Saldo: %d\n", estoque->caixa);
    printf("--------------------------------------------------\n");
}

void inicializar(Estoque *estoque){
    FILE *f = fopen(ARQUIVO_DADOS, "r");
    if (f != NULL){
         fscanf(f, "%f %d %d", &estoque->caixa, &estoque->total, &estoque->capacidade);
        estoque->produtos = malloc(estoque->capacidade * sizeof(Produto));
        for(int i = 0; i < estoque->total; i++){
            fscanf(f, "%d %s %d %f",
                &estoque->produtos[i].codigo,
                estoque->produtos[i].nome,
                &estoque->produtos[i].quantidade,
                &estoque->produtos[i].preco);
                                                }
    fclose(f);
    }
    else{
        estoque->caixa = 100.0;
        estoque->total = 0;
        printf("Capacidade inicial do estoque: ");
        scanf("%d", &estoque->capacidade);
        estoque->produtos = malloc(estoque->capacidade * sizeof(Produto));
    }
}

void finalizarDia(Estoque *estoque){
    FILE *f = fopen(ARQUIVO_DADOS, "w");
    fprintf(f, "%f %d %d\n", estoque->caixa, estoque->total, estoque->capacidade);
    for(int i = 0; i < estoque->total; i++){
        fprintf(f, "%d %s %d %f\n",
            estoque->produtos[i].codigo,
            estoque->produtos[i].nome,
            estoque->produtos[i].quantidade,
            estoque->produtos[i].preco);
                                            }
    fclose(f);
}

void inserirProduto(Estoque *estoque, char *nome, int quantidade, float preco){
    estoque->produtos[estoque->total].codigo=estoque->total;
    estoque->produtos[estoque->total].quantidade=quantidade;
    estoque->produtos[estoque->total].preco=preco;
    strcpy(estoque->produtos[estoque->total].nome, nome);
    estoque->total++;
}


int main() {
    Estoque estoque;
    inicializar(&estoque);

    char comando[3];
    while (scanf("%2s", comando) == 1) {
        if (strcmp(comando, "IP") == 0) {
            char nome[50];
            int quantidade;
            float preco;
            scanf("%s %d %f", nome, &quantidade, &preco);
            inserirProduto(&estoque, nome, quantidade, preco);

        } else if (strcmp(comando, "AE") == 0) {
            int codigo, quantidade;
            scanf("%d %d", &codigo, &quantidade);
            aumentarEstoque(&estoque, codigo, quantidade);

        } else if (strcmp(comando, "MP") == 0) {
            int codigo;
            float novoPreco;
            scanf("%d %f", &codigo, &novoPreco);
            modificarPreco(&estoque, codigo, novoPreco);

        } else if (strcmp(comando, "VE") == 0) {
            realizarVenda(&estoque);

        } else if (strcmp(comando, "CE") == 0) {
            consultarEstoque(&estoque);

        } else if (strcmp(comando, "CS") == 0) {
            consultarSaldo(&estoque);

        } else if (strcmp(comando, "FE") == 0) {
            finalizarDia(&estoque);
            break;
        }
    }

    free(estoque.produtos);
    return 0;
}
