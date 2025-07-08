#include "reporte.h"
#include "utils.h"
#include <stdio.h>

void run_reporte(AppContext* ctx)
{
    CLEAR_CONSOLE();
    puts("--- REPORTE DE TOTALES ---");

    size_t n_compra = 0, n_anul = 0;
    double total_compra = 0, total_anul = 0;

    for (size_t i = 0; i < ctx->count; ++i)
    {
        const Transaccion* t = &ctx->txs[i];
        if (t->tipo == T_COMPRA) {
            ++n_compra;
            if (!t->anulada) total_compra += t->monto;
        } else if (t->tipo == T_ANULACION) {
            ++n_anul;
            total_anul += t->monto; /* monto devuelto */
        }
    }

    printf("Transacciones totales: %zu\n", ctx->count);
    printf("Compras:   %zu  (%.2f USD)\n", n_compra, total_compra);
    printf("Anuladas:  %zu  (%.2f USD devueltos)\n", n_anul, total_anul);
    printf("Neto acumulado: %.2f USD\n", total_compra - total_anul);

    puts("\nPulse ENTER para continuar...");
    getchar(); getchar();
}
