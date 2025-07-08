#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#define CLEAR_CONSOLE() system("cls")
#else
  #define CLEAR_CONSOLE() system("clear")
#endif

/* Algoritmo de Luhn                          */
bool luhn_is_valid(const char* pan);

/* Devuelve "Visa", "Mastercard", "Amex",
   "Desconocida", etc.                        */
const char* detectar_franquicia(const char* pan);

/* true si tarjeta sigue vigente (MM/YY)      */
bool exp_es_valida(const char exp_mm_yy[6]);

#endif