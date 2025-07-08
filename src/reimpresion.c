#include "reimpresion.h"
#include "utils.h"
#include <stdio.h>

static void imprimir_tx(const Transaccion* tx);

void run_reimpresion(AppContext* ctx)
{
    CLEAR_CONSOLE();
    puts("--- REIMPRESION ---");
    if (ctx->count == 0) { puts("Sin transacciones."); getchar(); getchar(); return; }

    for (ssize_t i = (ssize_t)ctx->count - 1; i >= 0; --i)
        imprimir_tx(&ctx->txs[i]);

    puts("FIN de reimpresion. ENTER para volver.");
    getchar(); getchar();
}

static const char* tipo_str(const Transaccion* tx)
{
    if (tx->tipo == T_COMPRA)     return "COMPRA";
    if (tx->tipo == T_ANULACION)  return "ANULACION";
    return "CIERRE";
}

static void imprimir_tx(const Transaccion* tx)
{
    puts("------------------------------");
    printf("[%s] Ref %u  (%.2f USD)\n", tipo_str(tx), tx->ref, tx->monto);
    printf("Franquicia: %s\n", tx->franquicia);
    printf("Fecha/Hora: %s", ctime(&tx->fechaHora));
    if (tx->anulada) puts("** ANULADA **");
}
