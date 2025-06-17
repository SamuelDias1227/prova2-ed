
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_MEDICOES 50
#define MAX 50

typedef struct
{
    int timestamp;
    char valor[MAX];
} Medicao;

typedef struct
{
    char id_sensor[MAX];
    char tipo_dados_medicoes[MAX];
    int qtd_medicoes_sensor;
    Medicao medicao[MAX_MEDICOES];
} MedicoesPorTipo;

char *retornaTipoDeDado(char aux_valor[MAX]);
void separarMedicoesPorTipoSensor(MedicoesPorTipo medicoes_por_tipo[], int *qtd_sensor_diferentes, int aux_timestamp, char aux_id_sensor[MAX], char aux_valor[MAX]);
void lerConteudoArquivo(char *nomeArquivo, MedicoesPorTipo medicoes_por_tipo[]);
void ordenarMedicoesPorTimestamp(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes);
void gerarArquivosComMedicoes(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes);

int main(int argc, char *argv[])
{
    char nomeArquivo[21];
    MedicoesPorTipo medicoes_por_tipo[MAX_MEDICOES];

    if (argc >= 2) {
        strcpy(nomeArquivo, argv[1]);
    } else {
        printf("Digite o nome do arquivo a ser lido: ");
        scanf("%20s", nomeArquivo);
    }

    lerConteudoArquivo(nomeArquivo, medicoes_por_tipo);
    printf("FIM...");
    return 0;
}

void lerConteudoArquivo(char *nomeArquivo, MedicoesPorTipo medicoes_por_tipo[])
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
    char aux_id_sensor[MAX];
    char aux_valor[MAX];

    // Ignora a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo))
    {
        char *token;

        token = strtok(linha, " ");
        if (token)
            aux_timestamp = atoi(token);

        token = strtok(NULL, " ");
        strncpy(aux_id_sensor, token, MAX);

        token = strtok(NULL, " ");
        strncpy(aux_valor, token, MAX);

        qtd_leituras++;

        separarMedicoesPorTipoSensor(medicoes_por_tipo, &qtd_sensor_diferentes, aux_timestamp, aux_id_sensor, aux_valor);
    }
    ordenarMedicoesPorTimestamp(medicoes_por_tipo, qtd_sensor_diferentes);
    gerarArquivosComMedicoes(medicoes_por_tipo, qtd_sensor_diferentes);
    fclose(arquivo);
}

void separarMedicoesPorTipoSensor(MedicoesPorTipo medicoes_por_tipo[], int *qtd_sensor_diferentes, int aux_timestamp, char aux_id_sensor[MAX], char aux_valor[MAX])
{

    bool static jaAdd = false;
    bool existe = false;

    int i = 0;
    do
    {
        if (strcmp(medicoes_por_tipo[i].id_sensor, aux_id_sensor) == 0)
        {
            medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].timestamp = aux_timestamp;
            strncpy(medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].valor, aux_valor, MAX);
            medicoes_por_tipo[i].qtd_medicoes_sensor++;
            existe = true;
        }
        i++;
    } while (i < *qtd_sensor_diferentes);

    if (!existe)
    {

        if (jaAdd == true)
        {
            strncpy(medicoes_por_tipo[i].id_sensor, aux_id_sensor, MAX);
            strncpy(medicoes_por_tipo[i].tipo_dados_medicoes, retornaTipoDeDado(aux_valor), MAX);
            medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].timestamp = aux_timestamp;
            strncpy(medicoes_por_tipo[i].medicao[medicoes_por_tipo[i].qtd_medicoes_sensor].valor, aux_valor, MAX);
            medicoes_por_tipo[i].qtd_medicoes_sensor++;
    
            (*qtd_sensor_diferentes)++;
        } else
        {
            strncpy(medicoes_por_tipo[i-1].id_sensor, aux_id_sensor, MAX);
            strncpy(medicoes_por_tipo[i-1].tipo_dados_medicoes, retornaTipoDeDado(aux_valor), MAX);
            medicoes_por_tipo[i-1].medicao[medicoes_por_tipo[i-1].qtd_medicoes_sensor].timestamp = aux_timestamp;
            strncpy(medicoes_por_tipo[i-1].medicao[medicoes_por_tipo[i-1].qtd_medicoes_sensor].valor, aux_valor, MAX);
            medicoes_por_tipo[i-1].qtd_medicoes_sensor++;
            (*qtd_sensor_diferentes)++;
            jaAdd = true;
        }
    }
}

void ordenarMedicoesPorTimestamp(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes)
{
    int aux_timestamp;
    char aux_valor[MAX];

    for (int p = 0; p < qtd_sensor_diferentes; p++)
    {
        int i, j;
        for (i = 0; i < medicoes_por_tipo[p].qtd_medicoes_sensor - 1; i++)
        {
            printf("\n[%d] ", i);

            for (j = 0; j < medicoes_por_tipo[p].qtd_medicoes_sensor - i - 1; j++)
            {
                printf("%d, ", j);

                if ((medicoes_por_tipo[p].medicao[j].timestamp) > (medicoes_por_tipo[p].medicao[j + 1].timestamp))
                {
                    aux_timestamp = medicoes_por_tipo[p].medicao[j + 1].timestamp;
                    medicoes_por_tipo[p].medicao[j + 1].timestamp = medicoes_por_tipo[p].medicao[j].timestamp;
                    medicoes_por_tipo[p].medicao[j].timestamp = aux_timestamp;

                    strncpy(aux_valor, medicoes_por_tipo[p].medicao[j + 1].valor, MAX);
                    strncpy(medicoes_por_tipo[p].medicao[j + 1].valor, medicoes_por_tipo[p].medicao[j].valor, MAX);
                    strncpy(medicoes_por_tipo[p].medicao[j].valor, aux_valor, MAX);
                }
            }
        }
    }
}

void gerarArquivosComMedicoes(MedicoesPorTipo medicoes_por_tipo[], int qtd_sensor_diferentes)
{

    char nome_arquivo[MAX + 5];

    for (int p = 0; p < qtd_sensor_diferentes; p++)
    {
        strcpy(nome_arquivo, medicoes_por_tipo[p].id_sensor);

        strcat(nome_arquivo, ".txt");

        FILE *file = fopen(nome_arquivo, "w");
        if (file == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return;
        }

        fprintf(file, "TIPO DE DADOS DESSE SENSOR: %s\n", medicoes_por_tipo[p].tipo_dados_medicoes);
        fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");

        for (int i = 0; i < medicoes_por_tipo[p].qtd_medicoes_sensor; i++)
        {

            fprintf(file, "%d,%s,%s\n",
                    medicoes_por_tipo[p].medicao[i].timestamp,
                    medicoes_por_tipo[p].id_sensor,
                    medicoes_por_tipo[p].medicao[i].valor);
        }
        fclose(file);
    }
}

void converteParaMinuscula(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

int ehBooleano(char *str) {
    char temp[MAX];
    strncpy(temp, str, MAX);
    converteParaMinuscula(temp);
    return (strcmp(temp, "true") == 0 || strcmp(temp, "false") == 0);
}

int ehInteiro(char *str) {
    if (*str == '-') str++;
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int ehReal(char *str) {
    int jaTemPontoFlutuante = 0;
    if (*str == '-') str++;
    if (*str == '\0') return 0;

    while (*str) {
        if (*str == '.') {
            if (jaTemPontoFlutuante) return 0;
            jaTemPontoFlutuante = 1;
        } else if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return jaTemPontoFlutuante;
}

char *retornaTipoDeDado(char aux_valor[MAX])
{
    if (ehBooleano(aux_valor))
    {
        return "Booleano (true ou false)";
    }else if (ehInteiro(aux_valor))
    {
        return "Números inteiros";
    }else if (ehReal(aux_valor))
    {
        return "Número racional";
    }else {

        return "String (código de até 16 letras)";
    }
}
