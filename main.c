#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int numerovoo;
    char cidadeorigem[20];
    char cidadedestino[20];
    int ** mapaassentos;
}reserva;

int cabecalho()
{
    int x;
    printf("\t\tDesenvolvido por:\n-Rafael Alves Dorta      RA: 20032256\n-J\243lia de Miranda Gomes  RA: 20052387\n-Jo\306o Pedro C. Zanholo   RA: 20039822\n\n=======================================================\n");
    printf("\t\tBem vindo a JJR voos\n");
    printf("=======================================================\n");
    printf("\n\nDigite\n1- Nova Reserva;\n0- Sair;\nEscolha:");
    scanf("%d", &x);

    return x;
};

int valida_numero_voo(reserva CA[], int tam, int nv)
{
    int i;
    for(i=0;i<tam;i++)
        if(CA[i].numerovoo==nv)
            return i;
    return -1;
};

int escolhe_voo(reserva CA[], int tam)
{
    int i;
    int x=0;
    int nmv;
    printf("\n=======================================================\n");
    printf("\t\tEscolha o Numero do Voo\n\n");
    printf("NUMERO VOO\t\t ORIGEM\t\t DESTINO");
    for(i=0;i<tam;i++)
        printf("\n\n   %d\t\t\t%s\t%s",CA[i].numerovoo,CA[i].cidadeorigem,CA[i].cidadedestino);

    printf("\n=======================================================\n");
    do
    {
        printf("\nEscolha o Numero do Voo:");
        scanf("%d", &nmv);
        fflush(stdin);
        x = valida_numero_voo(CA,tam,nmv);
        if(x == -1)
            printf("Numero Invalido !");
    }while(x == -1);
    return x;
};

int **alocacao_espacao_matriz(int N, int M)
{
    int **mat,i;
    mat = (int**) calloc (N,sizeof(int));
    if(mat==NULL)
        exit (1);
    for (i=0;i<N;i++)
    {
        mat[i] = (int*)calloc (M,sizeof(int));
        if(mat[i]==NULL)
            exit (1);
    }
    return mat;
};

void imprime_mapa(int **mapa)
{
    int i,j;
    printf("       1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27\n");
    for(i=0;i<4;i++)
    {
        printf("\n [%c]", 65+ i);
        for(j=0;j<27;j++)
            printf("  %2d", mapa[i][j]);
    }
};

void escolhe_assento (reserva CA[], int tam, int posicao_tabela, char *letra, int *fileira)
{
    int a=0;
    printf("\n\nProcessando...");
    sleep(3);

    if (CA[posicao_tabela].mapaassentos == NULL)
       CA[posicao_tabela].mapaassentos= alocacao_espacao_matriz(4,27);

    do
    {
        system("cls");
        printf("\n\n\t\tMAPA DE LUGARES VOO: %d   ORIGEM: %s    DESTINO: %s \n\n",CA[posicao_tabela].numerovoo,CA[posicao_tabela].cidadeorigem,CA[posicao_tabela].cidadedestino );
        imprime_mapa(CA[posicao_tabela].mapaassentos);
        printf("\n\n0-VAGO     1-RESERVADO");
        printf("\n\nESCOLHA O SEU ASSENTO\n");
        do
        {
            printf("\nLetra: ");
            scanf("%c", letra);
            fflush(stdin);
            *letra = toupper(*letra);
        }while(*letra < 65 || *letra >68);

        do
        {
            printf("\n\nFileira: ");
            scanf("%d", fileira);
            fflush(stdin);
        }while(*fileira < 1 || *fileira >27);

        if (CA[posicao_tabela].mapaassentos[*letra -65][*fileira-1]==0)
        {
            CA[posicao_tabela].mapaassentos[*letra -65][*fileira-1] = 1;
            printf("\n\nProcessando...");
            sleep(3) ;
            system("cls");
            printf("\n\n\t\t\t\tVIZUALIZACAO DO ASSENTO RESERVADO\n\n");
            imprime_mapa(CA[posicao_tabela].mapaassentos);
            printf("\n\n");
            system("pause");
            break;
        }
        else
        {
            printf("\nASSENTO JA OCUPADO !!!\n\nAGUARDE...\n");
            sleep(3);
        }
    }while(a==0);
};

void imprime_bilhete(reserva CA[], int tam, int posicao_tabela, char letra, int fileira)
{
    char nome[50];
    printf("\n=======================================================\n");
    printf("Preparando Emissao do Bilhete\n\nDigite o nome do Passageiro: ");
    gets(nome);
    printf("\n=======================================================\n");
    printf("\n\nProcessando...");
    sleep(3) ;
    system("cls");

    printf("\t\t         BILHETE\n=======================================================\n");
    printf("\nNome: %s",nome);
    printf("\nNumero do Voo: %d", CA[posicao_tabela].numerovoo);
    printf("\nOrigem: %s",CA[posicao_tabela].cidadeorigem);
    printf("\nDestino: %s",CA[posicao_tabela].cidadedestino);
    printf("\nAssento: %c%d",letra,fileira);
    printf("\n=======================================================\n");
    system("pause");
    system("cls");
};

int main()
{
    reserva CiaAerea[10]= {{1234,"Viracopos","Afonso Pena",NULL},{4321,"Afonso Pena","Viracopos",NULL},{5678,"Guarulhos","Viracopos",NULL},{8765,"Viracopos","Guarulhos",NULL},
                         {2101,"Viracopos","Santos Dumont",NULL},{1012,"Santos Dumont","Viracopos",NULL},{6404,"Guarulhos","Serra Talhada",NULL},
                          {4046,"Serra Talhada","Guarulhos",NULL},{6565,"Confins    ","Guarulhos",NULL},{5656,"Guarulhos","Confins",NULL}};

    int posicao_tabela;
    int fileira;
    char letra;
    while(cabecalho()!=0)
    {
        posicao_tabela = escolhe_voo(CiaAerea,10);
        escolhe_assento(CiaAerea,10,posicao_tabela,&letra,&fileira);
        imprime_bilhete(CiaAerea,10,posicao_tabela,letra,fileira);
    };
    return 0;
}
