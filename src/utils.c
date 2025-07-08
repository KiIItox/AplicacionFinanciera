#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <time.h>

/*──────────────── Luhn ────────────────*/
bool luhn_is_valid(const char* pan)
{
    int sum = 0, alt = 0, len = strlen(pan);
    for (int i = len - 1; i >= 0; --i, alt = !alt)
    {
        if (!isdigit((unsigned char)pan[i])) return false;
        int digit = pan[i] - '0';
        if (alt) { digit *= 2; if (digit > 9) digit -= 9; }
        sum += digit;
    }
    return sum % 10 == 0;
}

/*────────────── Franquicia ─────────────*/
static struct { const char* name; const char* prefix; size_t len; } rules[] = {
    { "Visa",       "4",          1 },
    { "Mastercard", "51",         2 },
    { "Mastercard", "52",         2 },
    { "Mastercard", "53",         2 },
    { "Mastercard", "54",         2 },
    { "Mastercard", "55",         2 },
    { "AmericanExpress", "34",    2 },
    { "AmericanExpress", "37",    2 },
    { NULL, NULL, 0 }
};

const char* detectar_franquicia(const char* pan)
{
    for (int i = 0; rules[i].name; ++i)
        if (strncmp(pan, rules[i].prefix, rules[i].len) == 0)
            return rules[i].name;
    return "Desconocida";
}

/*──────────────­ Expiración ────────────*/
bool exp_es_valida(const char exp_mm_yy[6])
{
    if (!isdigit(exp_mm_yy[0]) || !isdigit(exp_mm_yy[1]) ||
        exp_mm_yy[2] != '/' ||
        !isdigit(exp_mm_yy[3]) || !isdigit(exp_mm_yy[4]))
        return false;

    int mm = (exp_mm_yy[0]-'0')*10 + (exp_mm_yy[1]-'0');
    int yy = (exp_mm_yy[3]-'0')*10 + (exp_mm_yy[4]-'0');

    if (mm < 1 || mm > 12) return false;

    /* Obtener fecha actual */
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    int cur_yy = (tm->tm_year + 1900) % 100;
    int cur_mm = tm->tm_mon + 1;

    return (yy > cur_yy) || (yy == cur_yy && mm >= cur_mm);
}