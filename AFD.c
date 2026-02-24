#include <stdio.h>
#include <ctype.h>

void tokenizar_linea(const char *texto) {
    int i = 0;

    while (texto[i] != '\0') {
        char c = texto[i];

        // Ignorar espacios
        if (isspace(c)) {
            i++;
            continue;
        }

        // '+' o '++'
        if (c == '+') {
            if (texto[i + 1] == '+') {
                printf("  INCR: ++\n");
                i += 2;
            } else {
                printf("  SUMA: +\n");
                i++;
            }
        }

        // ID = [A-Z][a-z0-9]*
        else if (c >= 'A' && c <= 'Z') {
            int inicio = i;
            i++;
            while ((texto[i] >= 'a' && texto[i] <= 'z') ||
                   (texto[i] >= '0' && texto[i] <= '9')) {
                i++;
            }

            printf("  ID: ");
            for (int j = inicio; j < i; j++)
                putchar(texto[j]);
            printf("\n");
        }

        // Rechazo
        else {
            printf("  NO ACEPTA: %c\n", c);
            i++;
        }
    }
}

int main() {
    FILE *archivo = fopen("texto.txt", "r");
    if (!archivo) {
        printf("Error: no se encontró 'input.txt'\n");
        return 1;
    }

    char linea[1024];
    int num = 1;

    while (fgets(linea, sizeof(linea), archivo)) {
        printf("\nLinea %d: %s", num++, linea);
        tokenizar_linea(linea);
    }

    fclose(archivo);
    return 0;
}