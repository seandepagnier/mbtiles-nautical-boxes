#include <stdio.h>
#include <stdlib.h>

struct box
{
    char name[256];
    double lat_min, lon_min, lat_max, lon_max;
    struct box *next;
};

struct box *boxes[20];

int main(int argc, char **argv)
{
    if(argc < 2) {
        fprintf(stderr, "usage: %s level\n", argv[0]);
        exit(0);
    }
    
    int level=atoi(argv[1]);

    char *line = 0;
    size_t n;
    int index, id;
    int ind = 0;


    while(getline(&line, &n, stdin) != EOF) {
        struct box *b = malloc(sizeof(struct box));
        int level;
        int ret = sscanf(line, "%s %d %lf %lf %lf %lf\n", b->name, &level,
                         &b->lat_min, &b->lon_min, &b->lat_max, &b->lon_max);
        free(line);
        line = 0;

        if(ret != 6 || level < 0 || level > 20) {
            fprintf(stderr, "invalid line %d (%d): %s\n", ind, ret, line);
            return 1;
        } else {
            b->next = boxes[level];
            boxes[level] = b;
        }
        ind++;
    }

    printf("seeds:\n");
    
    for(int level = 0; level<20; level++) {
        if(!boxes[level])
            continue;

        printf("  level%d:\n", level);
        printf("    caches: [default]\n");
        printf("    coverages: [");
        for(struct box *b = boxes[level]; b; b=b->next)
            printf("%s_%d_coverage,", b->name, level);
        printf("]\n");
        printf("    levels:\n");
        printf("      from: %d\n", level);
        printf("      to: %d\n", level);
        printf("\n");
    }
    
    printf("coverages:\n");
    for(int level = 0; level<20; level++) {
        for(struct box *b = boxes[level]; b; b=b->next) {
            printf("  %s_%d_coverage:\n", b->name, level);
            printf("    bbox: [%f, %f, %f, %f]\n", b->lon_min, b->lat_min, b->lon_max, b->lat_max);
            printf("    srs: \"EPSG:4326\"\n");
        }
    }
    printf("\n");
    return 0;
}
