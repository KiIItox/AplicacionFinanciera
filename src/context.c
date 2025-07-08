#include "context.h"
#include <stdio.h>
#include <string.h>

static void init_blank(AppContext* ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->siguienteRef = 1;
}

int load_context(AppContext* ctx)
{
    FILE* f = fopen(DATAFILE, "rb");
    if (!f) { init_blank(ctx); return 0; }

    size_t n = fread(ctx, sizeof(*ctx), 1, f);
    fclose(f);
    if (n != 1) { init_blank(ctx); return -1; }
    return 0;
}

int save_context(const AppContext* ctx)
{
    FILE* f = fopen(DATAFILE, "wb");
    if (!f) return -1;
    size_t n = fwrite(ctx, sizeof(*ctx), 1, f);
    fclose(f);
    return n == 1 ? 0 : -1;
}

void reset_context(AppContext* ctx)
{
    init_blank(ctx);
    remove(DATAFILE);
}
