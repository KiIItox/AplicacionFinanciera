#include "anulacion.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

static void imprimir_ticket(const Transaccion* tx);

void run_anulacion(AppContext* ctx)
{
    CLEAR_CONSOLE();
    puts("--- ANULACION ---");
    printf("Numero de referencia a anular: ");
    unsigned ref;  
    if (scanf("%u", &ref) != 1) return;

    /* Buscar transacción */
    Transaccion* tx = NULL;
    for (size_t i = 0; i < ctx->count; ++i)
        if (ctx->txs[i].ref == ref && ctx->txs[i].tipo == T_COMPRA) {
            tx = &ctx->txs[i]; break;
        }

    if (!tx) { puts("Referencia inexistente."); getchar(); getchar(); return; }

    if (tx->anulada) 
    { 
    puts("Ya estaba anulada."); getchar(); getchar(); 
    return;
    }

    char pan4[5], cvv[4];
    printf("Ultimos 4 digitos del PAN: ");
    scanf("%4s", pan4);
    printf("CVV: ");
    scanf("%3s", cvv);

    if (strcmp(pan4, tx->pan + strlen(tx->pan) - 4) != 0 ||
        strcmp(cvv, tx->cvv) != 0)
    {
        puts("Datos de validacion incorrectos."); getchar(); getchar(); return;
    }

    tx->anulada = true;
    tx->tipo    = T_ANULACION;
    save_context(ctx);

    imprimir_ticket(tx);
}

static void imprimir_ticket(const Transaccion* tx)
{
    CLEAR_CONSOLE();
    puts("---- Ticket de Anulacion ----");
    printf("Ref anulada: %u\n", tx->ref);
    printf("Monto devuelto: %.2f USD\n", tx->monto);
    printf("Fecha/Hora: %s", ctime(&tx->fechaHora));
    puts("-----------------------------");
    puts("Pulse ENTER para continuar...");
    getchar(); getchar();
}
