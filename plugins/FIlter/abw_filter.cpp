#include "abw_filter.h"
#include <stdlib.h>

void AutoBalanceWhite_filter::apply(RenderTargetI *data) {
    catchNullptr(data, );
    catchNullptr(params.data, );

    plugin::Texture *texture = data -> getTexture();

    int h = texture->height;
    int w = texture->width;

    uint64_t averageRed   = 0;
    uint64_t averageGreen = 0;
    uint64_t averageBlue  = 0;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            averageRed   += texture -> pixels[y * w + x].r;
            averageGreen += texture -> pixels[y * w + x].g;
            averageBlue  += texture -> pixels[y * w + x].b;
        }

    averageRed   /= h * w;
    averageGreen /= h * w;
    averageBlue  /= h * w;

    double k = params.data[0];

    double   redGain = k / averageRed  ;
    double greenGain = k / averageGreen;
    double  blueGain = k / averageBlue ;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            texture -> pixels[y * w + x].r *=   redGain;
            texture -> pixels[y * w + x].g *= greenGain;
            texture -> pixels[y * w + x].b *=  blueGain;
        }

    data -> drawTexture(Vec2(0, 0), Vec2(w, h), texture);
    // delete texture;

    return;
}

AutoBalanceWhite_filter::AutoBalanceWhite_filter() {
    paramNames.data = (const char **) calloc(1, sizeof(const char *));
    paramNames.data[0] = "AverageColorValue";
    
    params.data = (double *) calloc(1, sizeof(double));
    params.data[0] = 128;
}

DllExport plugin::Plugin* getInstance(plugin::App *app) {
    return new AutoBalanceWhite_plugin();
}