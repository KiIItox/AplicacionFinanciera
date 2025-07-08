#include <stdio.h>
#include "context.h"
#include "compra.h"
#include "anulacion.h"
#include "cierre.h"
#include "reimpresion.h"
#include "reporte.h"
#include "utils.h"

static void mostrar_menu(void);

int main(void)
{
    AppContext ctx = {0};
    load_context(&ctx);

    int opcion = 0;
    do {
        CLEAR_CONSOLE();

        mostrar_menu();
        if (scanf("%d", &opcion) != 1) opcion = -1;

        switch (opcion) {
            case 1:
                run_compra(&ctx);
                break;
            case 2:
                run_anulacion(&ctx);
                break;
            case 3:
                run_cierre(&ctx);
                break;
            case 4:
                run_reimpresion(&ctx);
                break;
            case 5:
                run_reporte(&ctx);
                break;
            case 0:
                puts("Saliendo...");
                break;
            default: puts("Opcion invalida."); getchar(); getchar();
        }
    } while (opcion != 0);

    return 0;
}

static void mostrar_menu(void)
{
    puts("----------  MENU PRINCIPAL  ----------");
    puts("1) Compra");
    puts("2) Anulacion");
    puts("3) Cierre");
    puts("4) Reimpresion");
    puts("5) Reporte de Totales");
    puts("0) Salir");
    printf("Seleccione opcion: \n");
    puts("---------------------------------------");
}
