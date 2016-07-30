#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    char *line = 0;
    size_t n;
    char scale;
    int index, id;
    double lat_min, lon_min, lat_max, lon_max;
    int ind = 0;

    FILE *c = tmpfile(), *d = tmpfile();
    printf("seeds:\n");
    fprintf(c, "coverages:\n");
    fprintf(d, "caches:\n");
    while(getline(&line, &n, stdin) != EOF) {
        int ret = sscanf(line, "%c%d.%d %lf %lf %lf %lf\n", &scale, &index, &id,
                         &lat_min, &lon_min, &lat_max, &lon_max);
        free(line);
        line = 0;

        if(ret != 7)
            fprintf(stderr, "invalid line %d (%d): %s\n", ind, ret, line);
        else {
            char name[1024];
            sprintf(name, "%d.%d%c", index, id, scale);
            int level = 6 + 2*(scale - 'A');

            printf("  %s:\n", name);
            printf("    caches: [%s_mbtiles]\n", name);
            printf("    coverages: [%s_coverage]\n", name);
            printf("    levels:\n");
            printf("      from: %d\n", level);
            printf("      to: %d\n", level);
            printf("\n");

            fprintf(c, "  %s_coverage:\n", name);
            fprintf(c, "    bbox: [%f, %f, %f, %f]\n", lon_min, lat_min, lon_max, lat_max);
            fprintf(c, "    srs: \"EPSG:4326\"\n");

            fprintf(c, "\n");

            fprintf(d, "  %s_mbtiles:\n", name);
            fprintf(d, "    grids: [webmercator]\n");
            fprintf(d, "    sources: [config_2_60.00]\n");
            fprintf(d, "    cache:\n");
            fprintf(d, "      type: mbtiles\n");
            fprintf(d, "      filename: /home/sean/mymapproxy/tiles/%s.mbtiles\n", name);
        }
        ind++;
    }

    printf("\n\n");
    int ch;
    fseek(c, 0, SEEK_SET);
    while((ch = fgetc(c)) != EOF)
        fputc(ch, stdout);
    printf("\n");

    fseek(d, 0, SEEK_SET);
    while((ch = fgetc(d)) != EOF)
        fputc(ch, stderr);
    printf("\n");

}
