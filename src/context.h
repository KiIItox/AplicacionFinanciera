#ifndef CONTEXT_H
#define CONTEXT_H

#include <stddef.h>
#include <time.h>
#include <stdbool.h>

#define MAX_COMPRAS   20
#define DATAFILE      "transactions.dat"

typedef enum {
    T_COMPRA, T_ANULACION, T_CIERRE
} TxType;

typedef struct {
    unsigned ref;              /* Consecutivo local        */
    char     pan[20];          /* 19 + '\0'                */
    char     franquicia[16];   /* Visa, MC, Amex…          */
    char     exp[6];           /* MM/YY + '\0'             */
    char     cvv[4];           /* 3‑4 dígitos + '\0'       */
    double   monto;            /* USD                      */
    time_t   fechaHora;
    bool     anulada;          /* true si fue anulada      */
    TxType   tipo;
} Transaccion;

typedef struct {
    Transaccion txs[MAX_COMPRAS];
    size_t      count;
    unsigned    siguienteRef;
} AppContext;

/* Carga/guarda contexto desde/ hacia DATAFILE (modo binario).
   Devuelve 0 si OK, -1 si error de E/S.                    */
int  load_context (AppContext* ctx);
int  save_context (const AppContext* ctx);

/* Inicializa en blanco, resetea archivo. */
void reset_context(AppContext* ctx);

#endif
