#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_DADOS "dados.txt"


typedef struct {
    int codigo;        // identificador único, atribuído sequencialmente
    char nome[50];     // nome sem espaços
    int quantidade;    // unidades disponíveis no estoque
    float preco;       // preço unitário
} Produto;


typedef struct {
    Produto *produtos; // array dinâmico de produtos
    int capacidade;    // tamanho máximo atual do array
    int total;         // quantidade de produtos cadastrados
    float caixa;       // saldo atual do caixa
} Estoque;




void imprimirSeparador();


Produto *buscarProduto(Estoque *estoque, int codigo);


void inserirProduto(Estoque *estoque, char *nome, int quantidade, float preco);


void aumentarEstoque(Estoque *estoque, int codigo, int quantidade);


void modificarPreco(Estoque *estoque, int codigo, float novoPreco);


void realizarVenda(Estoque *estoque);


void consultarEstoque(Estoque *estoque);


void consultarSaldo(Estoque *estoque);


void inicializar(Estoque *estoque);


void finalizarDia(Estoque *estoque);

void inserirProduto(Estoque *estoque, char *nome, int quantidade, float preco){
    estoque->produtos[estoque->total].codigo=estoque->total;
    estoque->produtos[estoque->total].quantidade=quantidade;
    estoque->produtos[estoque->total].preco=preco;
    strcpy(estoque->produtos[estoque->total].nome, nome);
    estoque->total++;
}
void modificarPreco(Estoque *estoque, int codigo, float novoPreco){
    estoque->produtos[codigo].preco=novoPreco;
}
void realizarVenda(Estoque *estoque){
    int k; //guarda temporariamente cada codigo do produto
    float total=0.0;//valor total da compra
    while(k!=-1){
        scanf(" %d",&k);
        printf("%s ",estoque->produtos[k].nome);
        printf("%d\n",estoque->produtos[k].preco);
        total+=estoque->produtos[k].preco;
        estoque->produtos[k].quantidade-=1;//diminui a quantidade do produto em 1
    }
    printf("Total: %.2f\n");
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

int main() {
    Estoque estoque;

    // Carrega dados do dia anterior ou inicializa do zero
    inicializar(&estoque);

    char comando[3];

    // Lê e processa comandos até receber FE (finalizar o dia)
    while (scanf("%2s", comando) == 1) {

        if (strcmp(comando, "IP") == 0) {
            // Insere produto: lê nome, quantidade e preço

        } else if (strcmp(comando, "AE") == 0) {
            // Aumenta estoque: lê código e quantidade

        } else if (strcmp(comando, "MP") == 0) {
            // Modifica preço: lê código e novo preço

        } else if (strcmp(comando, "VE") == 0) {
            // Realiza venda
            realizarVenda(&estoque);

        } else if (strcmp(comando, "CE") == 0) {
            // Consulta estoque
            consultarEstoque(&estoque);

        } else if (strcmp(comando, "CS") == 0) {
            // Consulta saldo
            consultarSaldo(&estoque);

        } else if (strcmp(comando, "FE") == 0) {
            // Finaliza o dia e encerra
            finalizarDia(&estoque);
            break;
        }
    }

    // Libera memória alocada dinamicamente
    free(estoque.produtos);

    return 0;
}
