#include <stdio.h>
#include <string.h>

void process_field(int contadorCampo, char *valor) {
    if (contadorCampo == 0) {
        printf("Código do item:\t");
    }
    if (contadorCampo == 1) {
        printf("Descrição do Item:\t");
    }
    if (contadorCampo == 2) {
        printf("Grupo:\t");
    }
    if (contadorCampo == 3) {
        printf("Classe:\t");
    }
    if (contadorCampo == 4) {
        printf("PDM:\t");
    }
    if (contadorCampo == 5) {
        printf("Status:\t");
    }
    if (contadorCampo == 6) {
        printf("Sustentável:\t");
    }
    printf("%s\n", valor);
}

int main(void) {
    char buf[7024];
    char token[7024];

    int contadorLinha = 0;
    int contadorCampo = 0;
    int entreAspasDuplas = 0;
    int token_pos = 0;
    int i = 0;

    FILE *fp = fopen("materiais.csv", "r");

    if (!fp) {
        printf("Não foi possível abrir o arquivo\n");
        return 0;
    }


    while (fgets(buf, 7024, fp)) {
        contadorLinha++;

        if (contadorLinha == 1) {
            continue;
        }

        contadorCampo = 0;
        i = 0;
        do {
            token[token_pos++] = buf[i];

            if (!entreAspasDuplas && (buf[i] == ',' || buf[i] == '\n')) {
                token[token_pos - 1] = 0;
                token_pos = 0;
                process_field(contadorCampo++, token);
            }

            if (buf[i] == '"' && buf[i + 1] != '"') {
                token_pos--;
                entreAspasDuplas = !entreAspasDuplas;
            }

            if (buf[i] == '"' && buf[i + 1] == '"')
                i++;

        } while (buf[++i]);

        printf("\n");
        printf("--------------------------------------------------------------------------------");
        printf("\n");
    }

    fclose(fp);

    return 0;
}
