#include "bmp.h"

int main(void)
{
    BMP_DataStructure* bitmap = BMP_LoadImage("Tux.bmp");

    if(bitmap == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir l'image.\n");
        return EXIT_FAILURE;
    }
    BMP_Copy(bitmap, "sortie.bmp");

    BMP_Close(bitmap);
    return EXIT_SUCCESS;
}
