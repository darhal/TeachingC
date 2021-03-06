#include <assert.h>
#include "bmp_loader.h"
#include "utils.h"

// *** Questions related to PART 2 ***

void bmp_load_header(bmp_header* header,  FILE* file)
{
    // TODO: Implement this

    (void)fread(&header->signature, sizeof(char), 2, file);
    (void)fread(&header->file_size, sizeof(unsigned int), 1, file);
    char junk[4];
    (void)fread(junk, sizeof(char), 4, file);
    (void)fread(&header->offset_pixels, sizeof(unsigned int), 1, file);
}

void bmp_load_dib_header(bmp_dib_header* dib_header, FILE* file)
{
    // TODO: Implement this

    (void)fread(&dib_header->header_size, sizeof(unsigned int), 1, file);
    (void)fread(&dib_header->width, sizeof(unsigned int), 1, file);
    (void)fread(&dib_header->height, sizeof(unsigned int), 1, file);
    (void)fread(&dib_header->planes, sizeof(unsigned short), 1, file);
    (void)fread(&dib_header->bpp, sizeof(unsigned short), 1, file);

    int junk[6];
    (void)fread(junk, sizeof(unsigned int), 6, file);

    (void)fread(&dib_header->red_bitmask, sizeof(unsigned int), 1, file);
    (void)fread(&dib_header->green_bitmask, sizeof(unsigned int), 1, file);
    (void)fread(&dib_header->blue_bitmask, sizeof(unsigned int), 1, file);
    (void)fread(&dib_header->alpha_bitmask, sizeof(unsigned int), 1, file);
}

void bmp_load_pixels(const bmp_header* const header, const bmp_dib_header* const dib, unsigned** pixels, FILE* file)
{
    // TODO: Implement this

    // fseek(file, header->offset_pixels, SEEK_SET);
    for (int y = dib->height - 1; y >= 0; y--) {
        for (int x = 0; x < dib->width; x++) {
            (void)fread(&pixels[y][x], sizeof(unsigned int), 1, file);
        }
    }
}

void bmp_load(bmp* bmp, const char* filename)
{
    // TODO: Implement this
    FILE* file = fopen(filename, "rb");
    bmp_load_header(&bmp->header, file);
    assert(bmp->header.signature[0] == 'B');
    assert(bmp->header.signature[1] == 'M');
    bmp_load_dib_header(&bmp->dib_header, file);
    bmp->pixels = (unsigned**)mat_init(bmp->dib_header.height, bmp->dib_header.width, sizeof(unsigned));
    bmp_load_pixels(&bmp->header, &bmp->dib_header, bmp->pixels, file);
    fclose(file);
}

void bmp_destroy(bmp* bmp)
{
    // TODO: Implement this

    mat_free((void**)bmp->pixels);
    bmp->pixels = NULL;
}

void bmp_print_info(const bmp* const bmp)
{
    const bmp_header* const header = &bmp->header;
    const bmp_dib_header* const dib_header = &bmp->dib_header;

    printf("File size        : %u\n", header->file_size);
    printf("Offset to pixels : %u\n", header->offset_pixels);
    printf("DIB size         : %u\n", dib_header->header_size);
    printf("Width            : %u\n", dib_header->width);
    printf("Height           : %u\n", dib_header->height);
    printf("Planes           : %u\n", dib_header->planes);
    printf("BPP              : %u\n", dib_header->bpp);
    printf("Red bitmask      : %u\n", dib_header->red_bitmask);
    printf("Green bitmask    : %u\n", dib_header->green_bitmask);
    printf("Blue bitmask     : %u\n", dib_header->blue_bitmask);
    printf("Alpha bitmask    : %u\n", dib_header->alpha_bitmask);
}
