# Prova2-ED
Segunda prova de estrutura de dados da faculdade.

# Atividade

Uma planta industrial inteligente realiza medições constantes por meio de sensores distribuídos na linha de produção. As leituras desses sensores são registradas sequencialmente em um arquivo bruto, sem distinção de tipo de sensor nem garantia de ordem temporal.

Com o crescimento do volume de dados, tornou-se necessário implementar um sistema que permita consultas rápidas e precisas com base em instantes específicos de tempo.

Como desenvolvedor de software, você é responsável por implementar **3 programas** para este sistema:

---

## Programa 1 – Organização dos Dados

O primeiro programa deve processar um arquivo contendo diversas leituras no seguinte formato:

< TIMESTAMP > < ID_SENSOR > < VALOR >

Onde os campos representam:

- `<TIMESTAMP>`: data e hora da medida no formato **unix epoch**.  
- `<ID_SENSOR>`: string sem espaço que representa cada sensor.  
- `<VALOR>`: Valor informado do sensor.

Cada sensor informa sempre o mesmo tipo de dado.
Sensores diferentes podem informar valores de tipos diferentes.
O programa deve suportar pelo menos 4 tipos de dados diferentes:

- Números inteiros;
- Booleano (true ou false);
- Número racional;
- String (código de até 16 letras).

Essas leituras referem-se a diferentes sensores, que aparecem misturados ao longo do arquivo.

Esse programa deverá:

- Tratar o arquivo indicado como argumento da linha de comando de execução do programa.
- Identificar os diferentes sensores presentes, dentro de uma lista de finita de tipos suportatos.
- Separar os dados em arquivos distintos para cada sensor.
- Em cada arquivo, ordenar as leituras por timestamp (data e hora representada em unix epoch) em ordem decrescente.

> A ordenação dos dados dentro de cada arquivo **não é opcional**: ela é necessária para permitir o uso de **busca binária** no processo de consulta descrito no Programa 2.

---

## Programa 2 – Consulta por Instante

O segundo programa deve pesquisar a medida de um sensor especifico mais próxima de uma data e hora informada.

Esse programa deve receber da linha de comando:

- O nome de um sensor (por exemplo, `TEMP`)
- Uma data e hora da medida consultada

O programa deve então localizar, usando **busca binária**, a leitura registrada com **timestamp mais próximo** daquele instante no arquivo correspondente ao sensor, e exibir as informações da leitura.

> A **busca binária é obrigatória** para garantir desempenho adequado em grandes volumes de dados.

---

## Programa 3 – Geração de Arquivo de Teste

Crie um programa adicional que gere um arquivo de teste com as seguintes características:

- O programa deve receber como argumento da linha de comando:

    - A **data de inicio do intervalo (dia, mês, ano, hora, min e seg)** de amostras geradas aleatoriamente.
    - A **data de fim do intervalo (dia, mês, ano, hora, min e seg)** de amostras geradas aleatoriamente.
    - Os nomes dos sensores.
    - O tipo do dado da amostra informada por cada tipo de sensor.
        - CONJ_Z:  para dados tipo inteiro
        - CONJ_Q: para dados do tipo float
        - TEXTO para dados do tipo string
        - BINARIO: para dados do tipo booleano.

- Para cada sensor, o programa deve criar **2000 leituras aleatórias**, com valores numéricos aleatórios e **timestamps sorteados dentro da data fornecida** pelo usuário.

- O arquivo gerado deve seguir o formato: < TIMESTAMP > < ID_SENSOR > < VALOR >

    - `<TIMESTAMP>`: data e hora da medida no formato **unix epoch**.  
    - `<ID_SENSOR>`: string sem espaço que representa cada sensor.  
    - `<VALOR>`: Valor aleatório da amostra de acordo com o tipo indicado para o sensor.

---

## Funções de Exemplo

## Captura e Conversão de Data/Hora para Timestamp

A função abaixo captura a data e hora da interface de entrada e retorna o timestamp correspondente.

### 📄 Exemplo em C:

```c
#include <stdio.h>
#include <time.h>

// Verificar antes de chamar essa funcao que os valores sao validos
time_t converter_para_timestap(int dia, int mes, int ano, int hora, int min, int seg) 
{
    struct tm t;

    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    t.tm_isdst = -1;

    time_t timestamp = mktime(&t);
    if (timestamp == -1) {
        printf("Data inválida. Tente novamente.\n");
    } else {
        return timestamp;
    }
}


```
## Geração de Timestamps Aleatórios

A função abaixo retorna um timestamp aleatório dentro de uma data representada pelos valores de dia, mês e ano:

### 📄 Exemplo em C:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t gerar_timestamp_aleatorio(struct tm * inicial, struct tm * final) {
    
    time_t timestamp_inicial, timestamp_final;
        
    timestamp_inicial = mktime(&inicial);
    if (timestamp_inicial == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    timestamp_final = mktime(&final);
    if (timestamp_final == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    time_t timestamp_aleatorio = timestamp_inicial + rand() % (timestamp_final - timestamp_inicial + 1);
    
    return timestamp_aleatorio;
}
```
