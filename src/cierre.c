#include "cierre.h"
#include "utils.h"
#include <stdio.h>

void run_cierre(AppContext* ctx)
{
    CLEAR_CONSOLE();
    puts("--- CIERRE ---");

    size_t n_compra = 0, n_anul = 0;
    double total = 0.0;
    for (size_t i = 0; i < ctx->count; ++i) {
        if (ctx->txs[i].tipo == T_COMPRA)            n_compra++;
        else if (ctx->txs[i].tipo == T_ANULACION)    n_anul++;
        total += (ctx->txs[i].anulada ? 0 : ctx->txs[i].monto) *
                 (ctx->txs[i].tipo == T_COMPRA ? 1 : -1);
    }

    printf("Total transacciones: %zu\n", ctx->count);
    printf(" - Compras:   %zu\n", n_compra);
    printf(" - Anuladas:  %zu\n", n_anul);
    printf("Monto acumulado neto: %.2f USD\n", total);

    puts("\n¿Confirmar cierre? (S/N): ");
    char ch; getchar(); ch = getchar();

    if (ch == 'S' || ch == 's')
    {
        reset_context(ctx);
        puts("Cierre ejecutado. Base vaciada.");
    }
    else  puts("Cierre cancelado.");

    puts("Pulse ENTER para continuar...");
    getchar();
}

