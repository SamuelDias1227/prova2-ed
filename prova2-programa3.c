#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50
#define MAX_MEDICOES 50

typedef struct
{
    int timestamp;
    char id_sensor[MAX];
    double valor;

} Medicao;

time_t gerar_timestamp_aleatorio(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    struct tm t1, t2;
    time_t timestamp_inicial, timestamp_final;
    
    t1.tm_year = ano1 - 1900;
    t1.tm_mon = mes1 - 1;
    t1.tm_mday = dia1;
    t1.tm_hour = 0;
    t1.tm_min = 0;
    t1.tm_sec = 0;
    t1.tm_isdst = -1;

    t2.tm_year = ano2 - 1900;
    t2.tm_mon = mes2 - 1;
    t2.tm_mday = dia2;
    t2.tm_hour = 0;
    t2.tm_min = 0;
    t2.tm_sec = 0;
    t2.tm_isdst = -1;
    
    timestamp_inicial = mktime(&t1);
    if (timestamp_inicial == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    t1.tm_hour = 23;
    t1.tm_min = 59;
    t1.tm_sec = 59;

    t2.tm_hour = 23;
    t2.tm_min = 59;
    t2.tm_sec = 59;
    
    timestamp_final = mktime(&t2);
    if (timestamp_final == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    time_t timestamp_aleatorio = timestamp_inicial + rand() % (timestamp_final - timestamp_inicial + 1);
    
    return timestamp_aleatorio;
}

void gerarArquivo(char nomes_sensores[5][10], int tipos_dados_dos_sensores[5] , FILE *file, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2){

    int static i = 0;

    if (i == 5)
    {
        printf("numero de chamadas a funcao excedido!");
        return;
    }
    
    file = fopen("dados.txt", "w");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    for (int k = 0; k < 5; k++)
    {
        if (tipos_dados_dos_sensores[i] = 1)
        {
            fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");
            for (int p = 0; p < 200; p++)
            {
                fprintf(file, "%ld,%s,%d\n",
                    gerar_timestamp_aleatorio(dia1, mes1, ano1, dia2, mes2, ano2),
                    nomes_sensores[i],
                    5 + ((int)rand() / RAND_MAX) * (15 - 5));
            }
        }else if (tipos_dados_dos_sensores[i] = 2)
        {
            fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");
            for (int p = 0; p < 200; p++)
            {
                fprintf(file, "%ld,%s,%.2lf\n",
                    gerar_timestamp_aleatorio(dia1, mes1, ano1, dia2, mes2, ano2),
                    nomes_sensores[i],
                    5.0 + ((double)rand() / RAND_MAX) * (15.0 - 5.0));
            }
        }else if (tipos_dados_dos_sensores[i] = 3)
        {
            fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");
            for (int p = 0; p < 200; p++)
            {
                fprintf(file, "%ld,%s,%s\n",
                    gerar_timestamp_aleatorio(dia1, mes1, ano1, dia2, mes2, ano2),
                    nomes_sensores[i],
                    "true");
            }
        }else if (tipos_dados_dos_sensores[i] = 4)
        {
            fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");
            for (int p = 0; p < 200; p++)
            {
                fprintf(file, "%ld,%s,%.2lf\n",
                    gerar_timestamp_aleatorio(dia1, mes1, ano1, dia2, mes2, ano2),
                    nomes_sensores[i],
                    "aleatorio");
            }
        }
        
        i++;  // Avança para o próximo nome
    }
}

int main()
{
    char nome1[10];
    char nome2[10];
    char nome3[10];
    char nome4[10];
    char nome5[10];
    int tipo_dados_sensor1;
    int tipo_dados_sensor2;
    int tipo_dados_sensor3;
    int tipo_dados_sensor4;
    int tipo_dados_sensor5;
    FILE *file;
    Medicao medicoes[MAX_MEDICOES];
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    printf("Digite a data e hora (dd mm aaaa hh mm ss) do inicio do intervalo de amostras: ");
    if (scanf("%d %d %d", &dia1, &mes1, &ano1) != 3) {
        while (getchar() != '\n');
        printf("Entrada inválida. Tente novamente.\n");
    }

    printf("Digite a data e hora (dd mm aaaa hh mm ss) do fim do intervalo de amostras: ");
    if (scanf("%d %d %d", &dia2, &mes2, &ano2) != 3) {
        while (getchar() != '\n');
        printf("Entrada inválida. Tente novamente.\n");
    }

    printf("\nDigite o nome do primeiro sensor: \n");
    scanf("%s", nome1);

    printf("Digite o seu tipo de dados: \n");
    printf("1 - INTERIO\n");
    printf("2 - REAL\n");
    printf("3 - LOGICO\n");
    printf("4 - TEXTO\n");
    scanf("%s", tipo_dados_sensor1);

    printf("Digite o nome do segundo sensor: \n");
    scanf("%s", nome2);

    printf("Digite o seu tipo de dados: \n");
    printf("1 - INTERIO\n");
    printf("2 - REAL\n");
    printf("3 - LOGICO\n");
    printf("4 - TEXTO\n");
    scanf("%s", tipo_dados_sensor2);

    printf("Digite o nome do terceiro sensor: \n");
    scanf("%s", nome3);

    printf("Digite o seu tipo de dados: \n");
    printf("1 - INTERIO\n");
    printf("2 - REAL\n");
    printf("3 - LOGICO\n");
    printf("4 - TEXTO\n");
    scanf("%s", tipo_dados_sensor3);

    printf("Digite o nome do quarto sensor: \n");
    scanf("%s", nome4);

    printf("Digite o seu tipo de dados: \n");
    printf("1 - INTERIO\n");
    printf("2 - REAL\n");
    printf("3 - LOGICO\n");
    printf("4 - TEXTO\n");
    scanf("%s", tipo_dados_sensor4);

    printf("Digite o nome do quinto sensor: \n");
    scanf("%s", nome5);

    printf("Digite o seu tipo de dados: \n");
    printf("1 - INTERIO\n");
    printf("2 - REAL\n");
    printf("3 - LOGICO\n");
    printf("4 - TEXTO\n");
    scanf("%s", tipo_dados_sensor5);

    char nomes_sensores[5][10] = {nome1,nome2,nome3,nome4,nome5};
    int tipos_dados_dos_sensores[5] = {tipo_dados_sensor1,tipo_dados_sensor2,tipo_dados_sensor3,tipo_dados_sensor4,tipo_dados_sensor5};

    for (int i = 0; i < 5; i++)
    {
        gerarArquivo(nomes_sensores, tipos_dados_dos_sensores, file, dia1, mes1, ano1, dia2, mes2, ano2);
    }

    return 0;
}