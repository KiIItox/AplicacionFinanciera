#include "compra.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

static int solicitar_datos(Transaccion* tx);
static void imprimir_ticket(const Transaccion* tx);
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void run_compra(AppContext* ctx)
{
    CLEAR_CONSOLE();
    puts("--- NUEVA COMPRA ---");

    if (ctx->count >= MAX_COMPRAS) {
        puts("Limite de compras alcanzado (20). Ejecute un cierre.");
        getchar(); getchar();
        return;
    }

    Transaccion nueva = {0};
    if (solicitar_datos(&nueva) != 0) return;

    nueva.ref       = ctx->siguienteRef++;
    nueva.tipo      = T_COMPRA;
    nueva.anulada   = false;
    ctx->txs[ctx->count++] = nueva;
    save_context(ctx);
    imprimir_ticket(&nueva);
}

static int solicitar_datos(Transaccion* tx)
{
    printf("Monto (0.00): ");
    if (scanf("%lf", &tx->monto) != 1) return -1;
    limpiarBuffer();
    printf("PAN (sin espacios): ");
    scanf("%19s", tx->pan);
    if (!luhn_is_valid(tx->pan)) { puts("PAN invalido (Luhn)."); getchar(); getchar(); return -1; }

    strcpy(tx->franquicia, detectar_franquicia(tx->pan));

    printf("CVV: ");
    scanf("%3s", tx->cvv);

    printf("Expiracion (MM/YY): ");
    scanf("%5s", tx->exp);
    if (!exp_es_valida(tx->exp)) { puts("Tarjeta expirada."); getchar(); getchar(); return -1; }

    tx->fechaHora = time(NULL);
    return 0;
}

static void imprimir_ticket(const Transaccion* tx)
{
    CLEAR_CONSOLE();
    puts("---- Ticket de Compra ----");
    printf("Ref: %u\n",     tx->ref);
    printf("Monto: %.2f USD\n", tx->monto);
    printf("Franquicia: %s\n",  tx->franquicia);
    printf("Fecha/Hora: %s",    ctime(&tx->fechaHora));
    puts("--------------------------");
    puts("Pulse ENTER para continuar...");
    getchar(); getchar();
}
