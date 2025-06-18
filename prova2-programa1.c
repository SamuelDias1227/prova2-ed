#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define TAM_NOME_ARQUIVO 25
#define QTD_MAX_SENSORES 50
#define TAM_NOME_SENSOR 50
#define TAM_NOME_TIPO_DADO 8 //INTEIRO, REAL, LITERAL, LOGICO
#define QTD_MAX_MEDICOES 50
#define TAM_STRING_VALOR 10
typedef struct
{
    int timestamp;
    char valor_str[TAM_STRING_VALOR];
} Medicao;

typedef struct
{
    char id_sensor[TAM_NOME_SENSOR];
    char tipo_dado_medicao[TAM_NOME_TIPO_DADO];
    int qtd_medicoes_sensor;
    Medicao medicao[QTD_MAX_MEDICOES];

} MedicoesPorTipo;

void lerConteudoArquivo(char nomeArquivo[TAM_NOME_ARQUIVO], MedicoesPorTipo medicoes_por_tipo[]);
void separarMedicoesPorTipoSensor(MedicoesPorTipo medicoes_por_tipo[], int *qtd_sensor_diferentes, int aux_timestamp, char aux_id_sensor[TAM_NOME_SENSOR], char aux_valor_str[TAM_STRING_VALOR]);
void ordenaDecrescentementeMedicoesPorTimestamp(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes);
char* recuperaTipoDado(char valor[TAM_STRING_VALOR]);
void gerarArquivosComMedicoes(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes);

int main(int argc, char *argv[])
{

    // 20 posições para o nome do arquivo (índices 0–19); 4 posições para a extensão ".txt" (índices 20–23); 25ª posição para o terminador nulo '\0' (índice 24)
    char nomeArquivo[TAM_NOME_ARQUIVO];
    MedicoesPorTipo medicoes_por_tipo[QTD_MAX_SENSORES];

    if (argc >= 2) {
        snprintf(nomeArquivo, TAM_NOME_ARQUIVO, "%.20s.txt", argv[1]);
    }

    printf("O nome do arquivo é: %s\n", nomeArquivo);

    lerConteudoArquivo(nomeArquivo, medicoes_por_tipo);

    return 0;
}

void lerConteudoArquivo(char nomeArquivo[TAM_NOME_ARQUIVO], MedicoesPorTipo medicoes_por_tipo[])
{

    int qtd_sensor_diferentes = 0;

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int qtd_leituras = 0;

    char linha[256];

    int aux_timestamp;
    char aux_id_sensor[TAM_NOME_SENSOR]; // 49 posições para o nome do sensor (índices 0-48); 50ª posição para o terminador nulo '\0' (índice 49)
    char aux_valor_str[TAM_STRING_VALOR]; // 9 posições para o valor da medicao (índices 0–8); 10ª posição para o terminador nulo '\0' (índice 9)

    // Ignora a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo))
    {
        char *token;

        //token = strtok(linha, " ");
        token = strtok(linha, " \n\r");
        if (token)
            aux_timestamp = atoi(token);

        //token = strtok(NULL, " ");
        token = strtok(NULL, " \n\r");
        if (token)
            snprintf(aux_id_sensor, TAM_NOME_SENSOR, "%s", token);

        //token = strtok(NULL, " ");
        token = strtok(NULL, " \n\r");
        if (token)
            snprintf(aux_valor_str, TAM_STRING_VALOR, "%s", token);

        qtd_leituras++;

        separarMedicoesPorTipoSensor(medicoes_por_tipo, &qtd_sensor_diferentes, aux_timestamp, aux_id_sensor, aux_valor_str);
    }
    ordenaDecrescentementeMedicoesPorTimestamp(medicoes_por_tipo, qtd_sensor_diferentes);
    gerarArquivosComMedicoes(medicoes_por_tipo, qtd_sensor_diferentes);
    fclose(arquivo);
}

void separarMedicoesPorTipoSensor(MedicoesPorTipo medicoes_por_tipo[], int *qtd_sensor_diferentes, int aux_timestamp, char aux_id_sensor[TAM_NOME_SENSOR], char aux_valor_str[TAM_STRING_VALOR])
{
    bool static jaFoiAddPrimeiraMedicao = false;
    bool existe = false;

    for (int i = 0; aux_valor_str[i] != '\0'; i++)
    {
        printf("aux_valor_str[%d]=%c\n", i, aux_valor_str[i]);
    }

    int i = 0;
    do
    {
        if (strcmp(medicoes_por_tipo[i].id_sensor, aux_id_sensor) == 0)
        {
            medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].timestamp = aux_timestamp;
            snprintf(medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].valor_str, TAM_STRING_VALOR, "%s", aux_valor_str);
            medicoes_por_tipo[i].qtd_medicoes_sensor++;
            existe = true;
        }
        i++;
    } while (i < *qtd_sensor_diferentes);

    if (!existe)
    {
        if (jaFoiAddPrimeiraMedicao == true)
        {
            snprintf(medicoes_por_tipo[i].id_sensor, TAM_NOME_SENSOR, "%s", aux_id_sensor);
            snprintf(medicoes_por_tipo[i].tipo_dado_medicao, TAM_NOME_TIPO_DADO, "%s", recuperaTipoDado(aux_valor_str));
            medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].timestamp = aux_timestamp;
            snprintf(medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].valor_str, TAM_STRING_VALOR, "%s", aux_valor_str);
            medicoes_por_tipo[i].qtd_medicoes_sensor++;
    
            (*qtd_sensor_diferentes)++;
        } else
        {
            snprintf(medicoes_por_tipo[i-1].id_sensor, TAM_NOME_SENSOR, "%s", aux_id_sensor);
            snprintf(medicoes_por_tipo[i-1].tipo_dado_medicao, TAM_NOME_TIPO_DADO, "%s", recuperaTipoDado(aux_valor_str));
            medicoes_por_tipo[i-1].medicao[medicoes_por_tipo[i-1].qtd_medicoes_sensor].timestamp = aux_timestamp;
            snprintf(medicoes_por_tipo[i-1].medicao[medicoes_por_tipo[i-1].qtd_medicoes_sensor].valor_str, TAM_STRING_VALOR, "%s", aux_valor_str);
            medicoes_por_tipo[i-1].qtd_medicoes_sensor++;
            (*qtd_sensor_diferentes)++;
            jaFoiAddPrimeiraMedicao = true;
        }
    }
}

char* recuperaTipoDado(char valor[TAM_STRING_VALOR]) {

    if (strcmp(valor, "true") == 0 || strcmp(valor, "false") == 0) {
        return "LOGICO";
    }

    bool jaTemPonto = false;
    bool temCaractere = false;

    for (int i = 0; valor[i] != '\0'; i++)
    {
        printf("valor[%d]=%c\n", i, valor[i]);
        if (valor[i] == '.')
        {
            if (jaTemPonto)
            {
                temCaractere = true;
                break;
            }
            jaTemPonto = true;
        } else if (!isdigit(valor[i]))
        {
            if (i != 0)
            {
                temCaractere = true;
                break;
            } else if (valor[i] != '-')
            {
                temCaractere = true;
                break;
            }
        }
    }

    if (!temCaractere) {
        if (jaTemPonto)
        {
            return "REAL";
        }else
        {
            return "INTEIRO";
        }
    }

    return "LITERAL";
}

void ordenaDecrescentementeMedicoesPorTimestamp(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes)
{
    int aux_timestamp;
    char aux_valor_str[TAM_STRING_VALOR];

    for (int p = 0; p < qtd_sensor_diferentes; p++)
    {
        int i, j;
        for (i = 0; i < medicoes_por_tipo[p].qtd_medicoes_sensor - 1; i++)
        {
            printf("\n[%d] ", i);

            for (j = 0; j < medicoes_por_tipo[p].qtd_medicoes_sensor - i - 1; j++)
            {
                printf("%d, ", j);

                if ((medicoes_por_tipo[p].medicao[j].timestamp) < (medicoes_por_tipo[p].medicao[j + 1].timestamp))
                {
                    aux_timestamp = medicoes_por_tipo[p].medicao[j + 1].timestamp;
                    medicoes_por_tipo[p].medicao[j + 1].timestamp = medicoes_por_tipo[p].medicao[j].timestamp;
                    medicoes_por_tipo[p].medicao[j].timestamp = aux_timestamp;

                    snprintf(aux_valor_str, TAM_STRING_VALOR, "%s", medicoes_por_tipo[p].medicao[j + 1].valor_str);
                    snprintf(medicoes_por_tipo[p].medicao[j + 1].valor_str, TAM_STRING_VALOR, "%s", medicoes_por_tipo[p].medicao[j].valor_str);
                    snprintf(medicoes_por_tipo[p].medicao[j].valor_str, TAM_STRING_VALOR, "%s", aux_valor_str);
                }
            }
        }
    }
}

void gerarArquivosComMedicoes(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes)
{

    char nome_arquivo[TAM_NOME_SENSOR + 5];

    for (int p = 0; p < qtd_sensor_diferentes; p++)
    {

        snprintf(nome_arquivo, TAM_NOME_SENSOR, "%.45s.txt", medicoes_por_tipo[p].id_sensor);

        FILE *file = fopen(nome_arquivo, "w");
        if (file == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return;
        }

        fprintf(file, "TIPO DE DADOS DESSE SENSOR: %s\n", medicoes_por_tipo[p].tipo_dado_medicao);
        fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");

        for (int i = 0; i < medicoes_por_tipo[p].qtd_medicoes_sensor; i++)
        {

            fprintf(file, "%d,%s,%s\n",
                    medicoes_por_tipo[p].medicao[i].timestamp,
                    medicoes_por_tipo[p].id_sensor,
                    medicoes_por_tipo[p].medicao[i].valor_str);
        }
        fclose(file);
    }
}