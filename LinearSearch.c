#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX1 500000 // numero max de componentes do vetor

typedef enum boleano
{
    falso,
    verdadeiro
} Boleano;

Boleano Busca_Linear(int *Ptr, int Dim, int Chave)
{

    for (int i = 0; i < Dim; i++)
        if (*(Ptr + i) == Chave)
            return (verdadeiro); // elemento localizado

    return (falso); // elemento nao pertence ao array
} // Busca_Linear

int Maior_Elemento_Vetor(int *Ptr, int Dim)
{
    int i = 1, maior1;

    maior1 = *(Ptr); // inicializando maior1 com o primeiro elemento do vetor

    for (; i < Dim; i++) // a partir do segundo elemento - posição 1
        if (*(Ptr + i) > maior1)
            maior1 = *(Ptr + i);

    return (maior1);
} // Maior_Elemento_Vetor

void Imprime_Valores_Array(int *Ptr, int Dim, FILE *f)
{
    for (int i = 0; i < Dim; i++)
    {
        printf("\n[%d] = %d ", i, *(Ptr + i));

        fprintf(f, "\n[%d] = %d ", i, *(Ptr + i));
    }
}

int GetTextArr(int *Ptr, int *Pptr, int *Pdim)
{
    FILE *file;

    char frase[100];

    file = fopen("numeros.txt", "r");

    if (file == NULL)
    {
        printf("nao foi possivel abrir o arquivo");
        getchar();
        return falso;
    }

    while (fgets(frase, 100, file) != NULL)
    {
        printf("\n%s\n", frase);
    }
    fclose(file);

    char *str = frase, *p = str;
    long val;
    int i = 0;

    while (*p) // enquanto ainda tiver caracteres para percorrer...
    {
        if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p))))
        {
            // encontra um numero
            val = strtol(p, &p, 10); // Le o numero
            Ptr[i] = val;
        }
        else
        {
            // caso contrario vá para o próximo caractere.
            p++;
            i++;
        }
    }
    int Dim = i + 1;

    *Pptr = *Ptr;
    *Pdim = Dim;
}

int main()
{
    int n1,           // dimensao do array
        vetor1[MAX1], // array vetor1 para armazenar os elementos
        chave;        // chave a ser pesquisada

    GetTextArr(vetor1, &vetor1, &n1);

    FILE *file;
    file = fopen("numerosModf.txt", "w"); //o resultado sera devolvido no documento numerosModf.txt
    fprintf(file, "array: ");
    Imprime_Valores_Array(vetor1, n1, file);
    puts("\n");

    printf("\n\nO maior elemento do vetor1 eh o valor: << %d >> \n", Maior_Elemento_Vetor(vetor1, n1));

    printf("\ndigite o valor que deseja encontrar: ");
    scanf("%d", &chave);
    printf("\nrealizando uma busca linear...");

    if (Busca_Linear(&vetor1[0], n1, chave))
    {
        printf("\n\nO elemento %d PERTENCE ao vetor1.\n\n ", chave);
        fprintf(file, "\n\nO elemento %d PERTENCE ao vetor1.\n\n ", chave);
    }
    else{
        printf("\n\nO elemento %d NAO PERTENCE ao vetor1.\n\n", chave);
        fprintf(file, "\n\nO elemento %d NAO PERTENCE ao vetor1.\n\n", chave);
    }

    fclose(file);
    printf("Pressione enter/return para finalizar ...");
    fflush(stdin);
    getchar();
    return (0);
}