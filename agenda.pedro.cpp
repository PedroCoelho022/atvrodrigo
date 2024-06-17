#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_TAMA 100
#define MAX_TELEFONE_TAMA 15

typedef struct {
    char nome[MAX_NOME_TAMA];
    char telefone[MAX_TELEFONE_TAMA];
} Contato;

void adicionarContato();
void consultarContato();
void excluirContato();
void salvarContatos();
void carregarContatos();
void exibirMenu();

Contato contatos[100];
int contadorContatos = 0;
const char *nomeArquivo = "contatos.dat";

int main()
{
    carregarContatos();
    int opcao;

    while (1)
    {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
            case 1:
                adicionarContato();
                break;
            case 2:
                consultarContato();
                break;
            case 3:
                excluirContato();
                break;
            case 4:
                salvarContatos();
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

void exibirMenu()
{
    printf("\n--- Catalogo de Cotatos ---\n");
    printf("1. Adicionar contato\n");
    printf("2. Consultar contato\n");
    printf("3. Excluir contato\n");
    printf("4. Salvar e sair\n");
}

void adicionarContato()
{
    if (contadorContatos < 100)
    {
        Contato novoContato;
        printf("Digite o nome: ");
        fgets(novoContato.nome, MAX_NOME_TAMA, stdin);
        novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0'; 

        printf("Digite o telefone: ");
        fgets(novoContato.telefone, MAX_TELEFONE_TAMA, stdin);
        novoContato.telefone[strcspn(novoContato.telefone, "\n")] = '\0'; 

        contatos[contadorContatos++] = novoContato;
        printf("Contato adicionado com sucesso!\n");
    }
    else
    {
        printf("Catálogo cheio! Nao é possível adicionar mais contatos.\n");
    }
}

void consultarContato()
{
    char nomeBusca[MAX_NOME_TAMA];
    printf("Digite o nome para buscar: ");
    fgets(nomeBusca, MAX_NOME_TAMA, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < contadorContatos; i++)
    {
        if (strcmp(contatos[i].nome, nomeBusca) == 0)
        {
            printf("Contato encontrado: Nome: %s, Telefone: %s\n", contatos[i].nome, contatos[i].telefone);
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

void excluirContato()
{
    char nomeBusca[MAX_NOME_TAMA];
    printf("Digite o nome para excluir: ");
    fgets(nomeBusca, MAX_NOME_TAMA, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; 

    for (int i = 0; i < contadorContatos; i++)
    {
        if (strcmp(contatos[i].nome, nomeBusca) == 0)
        {
            for (int j = i; j < contadorContatos - 1; j++)
            {
                contatos[j] = contatos[j + 1];
            }
            contadorContatos--;
            printf("Contato excluido com sucesso.\n");
            return;
        }
    }
    printf("Contato nao encontrado.\n");
}

void salvarContatos()
{
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar os contatos.\n");
        return;
    }
    fwrite(&contadorContatos, sizeof(int), 1, arquivo);
    fwrite(contatos, sizeof(Contato), contadorContatos, arquivo);
    fclose(arquivo);
    printf("Contatos salvos com sucesso.\n");
}

void carregarContatos()
{
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de contatos encontrado. Criando um novo.\n");
        return;
    }
    fread(&contadorContatos, sizeof(int), 1, arquivo);
    fread(contatos, sizeof(Contato), contadorContatos, arquivo);
    fclose(arquivo);
    printf("Contatos carregados com sucesso.\n");
}
