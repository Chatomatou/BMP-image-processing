#include "bmp.h"

BMP_DataStructure* BMP_LoadImage(const char* const path)
{
    BMP_DataStructure* bitmap = malloc(sizeof(*bitmap)); /* Allouer une structure de type BMP_DataStructure */
    FILE* file = NULL; /*Pointeur sur fichier*/
    uint8_t byte = 0; /* permet de lire les octet du fichier */
    uint32_t i = 0; /* Compteur pour ma boucle */
    uint32_t w = 0;
    uint32_t h = 0;

    if(bitmap == NULL) /*Géstion des erreur */
        return NULL;

    file = fopen(path, "r"); /*Ouvre un fichier en lecture seul*/

    if(file == NULL) /*Gestion des erreur*/
    {
        fclose(file);
        BMP_Close(bitmap);
        return NULL;
    }
    /* Initialisation des membre de la structure */
    bitmap->pixel = NULL;
    bitmap->signature = 0;
    bitmap->offset = 0;
    bitmap->w = 0;
    bitmap->h = 0;
    bitmap->fSize = 0;
    bitmap->codingDepth = 0;
    bitmap->header = 0;
    bitmap->reserved = 0;
    bitmap->nop = 0;
    bitmap->compression = 0;
    bitmap->iSize = 0;
    bitmap->horizontalResolution = 0;
    bitmap->verticalResolution = 0;
    bitmap->paletteColor = 0;
    bitmap->paletteImportantColor = 0;
    bitmap->palette = 0;

    /* Lecture des données */
    /* Signature 2 octet */
    fseek(file, BMP_OFFSET_SIGNATURE, SEEK_SET); /* Place le curseur au debut pour lire la signature du fichier */
    byte = fgetc(file); /* Recupere l'octet et deplace le curseur de 1 */
    bitmap->signature |= (byte << 8); /*Ecrit dans la partit haute les bit contenu dans la variable byte*/
    byte = fgetc(file); /*Recupère l'octet de la signature */
    bitmap->signature |= byte; /*Ecrit dans la partis basse les bit de la variable byte*/

    /*La taille total du fichier 4 octet*/
    fseek(file, BMP_OFFSET_FSIZE, SEEK_SET);
    byte = fgetc(file);
    bitmap->fSize |= (byte << 24);
    byte = fgetc(file);
    bitmap->fSize |= (byte << 16);
    byte = fgetc(file);
    bitmap->fSize |= (byte << 8);
    byte = fgetc(file);
    bitmap->fSize |= byte ;

    /*Le champ reservé de 4 octet*/
    fseek(file, BMP_OFFSET_RESERVED, SEEK_SET);
    byte = fgetc(file);
    bitmap->reserved |= (byte << 24);
    byte = fgetc(file);
    bitmap->reserved |= (byte << 16);
    byte = fgetc(file);
    bitmap->reserved |= (byte << 8);
    byte = fgetc(file);
    bitmap->reserved |= byte;

    /*L'offset du debut de lecture des information de l'image 4 octet */
    fseek(file, BMP_OFFSET_START, SEEK_SET);
    byte = fgetc(file);
    bitmap->offset |= (byte << 24);
    byte = fgetc(file);
    bitmap->offset |= (byte << 16);
    byte = fgetc(file);
    bitmap->offset |= (byte << 8);
    byte = fgetc(file);
    bitmap->offset |= byte;

    fseek(file, BMP_OFFSET_HEADER, SEEK_SET);
    byte = fgetc(file);
    bitmap->header |= (byte << 24);
    byte = fgetc(file);
    bitmap->header |= (byte << 16);
    byte = fgetc(file);
    bitmap->header |= (byte << 8);
    byte = fgetc(file);
    bitmap->header |= byte;

    /*La largeur de l'image 4 octet*/
    fseek(file, BMP_OFFSET_WIDTH, SEEK_SET);
    byte = fgetc(file);
    bitmap->w |= (byte << 24);
    byte = fgetc(file);
    bitmap->w |= (byte << 16);
    byte = fgetc(file);
    bitmap->w |= (byte << 8);
    byte = fgetc(file);
    bitmap->w |= byte;

    byte = bitmap->w >> 24;
    w = byte;
    byte = 0;
    byte = bitmap->w >> 16;
    w |= byte;
    byte = 0;
    byte = bitmap->w >> 8;
    w |= byte;
    byte = 0;
    byte = bitmap->w;
    w |= byte;



    /*La hauteur de l'image 4 octet*/
    fseek(file, BMP_OFFSET_HEIGHT, SEEK_SET);
    byte = fgetc(file);
    bitmap->h |= (byte << 24);
    byte = fgetc(file);
    bitmap->h |= (byte << 16);
    byte = fgetc(file);
    bitmap->h |= (byte << 8);
    byte = fgetc(file);
    bitmap->h |= byte;

    byte = bitmap->h >> 24;
    h = byte;
    byte = 0;
    byte = bitmap->h >> 16;
    h |= byte;
    byte = 0;
    byte = bitmap->h >> 8;
    h |= byte;
    byte = 0;
    byte = bitmap->h;
    h |= byte;


    /*Le nombre de plan 2 octet*/
    fseek(file, BMP_OFFSET_NUMBER_OF_PLAN, SEEK_SET);
    byte = fgetc(file);
    bitmap->nop |= (byte << 8);
    byte = fgetc(file);
    bitmap->nop |= byte;

    /*La profondeur de codage 2 octet*/
    fseek(file, BMP_OFFSET_CODING_DEPTH, SEEK_SET);
    byte = fgetc(file);
    bitmap->codingDepth |= (byte << 8);
    byte = fgetc(file);
    bitmap->codingDepth |= byte;

    /*La compression 4 octet*/
    fseek(file, BMP_OFFSET_COMPRESSION, SEEK_SET);
    byte = fgetc(file);
    bitmap->compression |= (byte << 24);
    byte = fgetc(file);
    bitmap->compression |= (byte << 16);
    byte = fgetc(file);
    bitmap->compression |= (byte << 8);
    byte = fgetc(file);
    bitmap->compression |= byte;

    /*La taille totale de l'image 4 octet*/
    fseek(file, BMP_OFFSET_ISIZE, SEEK_SET);
    byte = fgetc(file);
    bitmap->iSize |= (byte << 24);
    byte = fgetc(file);
    bitmap->iSize |= (byte << 16);
    byte = fgetc(file);
    bitmap->iSize |= (byte << 8);
    byte = fgetc(file);
    bitmap->iSize |= byte;

    /*La resolution horizontal de l'image 4 octet*/
    fseek(file, BMP_OFFSET_HORIZONTAL_RESOLUTION, SEEK_SET);
    byte = fgetc(file);
    bitmap->horizontalResolution |= (byte << 24);
    byte = fgetc(file);
    bitmap->horizontalResolution |= (byte << 16);
    byte = fgetc(file);
    bitmap->horizontalResolution |= (byte << 8);
    byte = fgetc(file);
    bitmap->horizontalResolution |= byte;

     /*La resolution verticale de l'image 4 octet*/
    fseek(file, BMP_OFFSET_VERTICAL_RESOLUTION, SEEK_SET);
    byte = fgetc(file);
    bitmap->verticalResolution |= (byte << 24);
    byte = fgetc(file);
    bitmap->verticalResolution |= (byte << 16);
    byte = fgetc(file);
    bitmap->verticalResolution |= (byte << 8);
    byte = fgetc(file);
    bitmap->verticalResolution |= byte;

    /*Pallette de couleur 4octet*/
    fseek(file, BMP_OFFSET_PALETTE_COLOR, SEEK_SET);
    byte = fgetc(file);
    bitmap->paletteColor |= (byte << 24);
    byte = fgetc(file);
    bitmap->paletteColor |= (byte << 16);
    byte = fgetc(file);
    bitmap->paletteColor |= (byte << 8);
    byte = fgetc(file);
    bitmap->paletteColor |= byte;

    /*Pallette de couleur importante 4octet*/
    fseek(file, BMP_OFFSET_IMPORTANT_PALETTE, SEEK_SET);
    byte = fgetc(file);
    bitmap->paletteImportantColor |= (byte << 24);
    byte = fgetc(file);
    bitmap->paletteImportantColor |= (byte << 16);
    byte = fgetc(file);
    bitmap->paletteImportantColor |= (byte << 8);
    byte = fgetc(file);
    bitmap->paletteImportantColor |= byte;

    /*Pallette 4octet*/
    fseek(file, BMP_OFFSET_PALETTE, SEEK_SET);
    byte = fgetc(file);
    bitmap->palette |= (byte << 24);
    byte = fgetc(file);
    bitmap->palette |= (byte << 16);
    byte = fgetc(file);
    bitmap->palette |= (byte << 8);
    byte = fgetc(file);
    bitmap->palette |= byte;



    /* Alloue mes tableau qui contient les pixel bleu vert et rouge */
    bitmap->pixel = malloc(sizeof(uint8_t) * ((bitmap->w>>24) * (bitmap->h>>24)) * 3);
    if(bitmap->pixel == NULL)
    {
        fclose(file);
        return NULL;
    }
    bitmap->endiannesCorectionW = w;
    bitmap->endiannesCorectionH = h;
    fseek(file, bitmap->offset >> 24, SEEK_SET);
    for(i = 0; i < bitmap->endiannesCorectionW * bitmap->endiannesCorectionH * 3; i+=3)
    {
        fseek(file, (bitmap->offset>>24)+i, SEEK_SET);
        bitmap->pixel[i] = fgetc(file);
        bitmap->pixel[i+1] = fgetc(file);
        bitmap->pixel[i+2] = fgetc(file);
    }

    fclose(file);
    return bitmap;
}
void BMP_InfoBitmap(const BMP_DataStructure* const bitmap)
{

    printf("=====================\n");
    printf("=       bitmap      =\n");
    printf("=====================\n");

    printf("Signature : %d\n", bitmap->signature);
    printf("Dimension : %d x %d\n", bitmap->endiannesCorectionW, bitmap->endiannesCorectionH);
    printf("Offset Color : %x\n", bitmap->offset);
    printf("Coding Deph : %x\n", bitmap->codingDepth);
}
unsigned char BMP_AverageBGR(unsigned char cBlue, unsigned char cGreen, unsigned char cRed)
{
    return (cBlue + cGreen + cRed) / 3;
}
uint8_t BMP_TransformBlackWhite(uint32_t const color)
{
    if(color <= 127)
        return BMP_PIXEL_BLACK;
    return BMP_PIXEL_WHITE;
}
void BMP_Copy(const BMP_DataStructure* const bitmap, const char* const name)
{
    FILE* file = fopen(name, "w");
    uint32_t i = 0;


    if(file == NULL)
        return;

    /*Ecrit la signature*/
    fputc(bitmap->signature >> 8, file);
    fputc(bitmap->signature, file);

    /*Ecrit le taille total du fichier */
    fputc(bitmap->fSize >> 24, file);
    fputc(bitmap->fSize >> 16, file);
    fputc(bitmap->fSize >> 8, file);
    fputc(bitmap->fSize, file);

    /*Ecrit le champ reservé*/
    fputc(bitmap->reserved >> 24, file);
    fputc(bitmap->reserved >> 16, file);
    fputc(bitmap->reserved >> 8, file);
    fputc(bitmap->reserved, file);

    /*Ecrit l'offet du debut de lecture des information de l'image*/
    fputc(bitmap->offset >> 24, file);
    fputc(bitmap->offset >> 16, file);
    fputc(bitmap->offset >> 8, file);
    fputc(bitmap->offset, file);

    /*Ecrit la taille de l'entête de l'image */
    fputc(bitmap->header >> 24, file);
    fputc(bitmap->header >> 16, file);
    fputc(bitmap->header >> 8, file);
    fputc(bitmap->header, file);

    /*Ecrit la largeur de l'image*/
    fputc(bitmap->w >> 24, file);
    fputc(bitmap->w >> 16, file);
    fputc(bitmap->w >> 8, file);
    fputc(bitmap->w, file);

    /*Ecrit la hauteur de l'image*/
    fputc(bitmap->h >> 24, file);
    fputc(bitmap->h >> 16, file);
    fputc(bitmap->h >> 8, file);
    fputc(bitmap->h, file);

    /*Ecrit le nombre de plan */
    fputc(bitmap->nop >> 8, file);
    fputc(bitmap->nop, file);

    /*Ecrit la profondeur de codage*/
    fputc(bitmap->codingDepth >> 8, file);
    fputc(bitmap->codingDepth, file);

    /*Ecrit la compression*/
    fputc(bitmap->compression >> 24, file);
    fputc(bitmap->compression >> 16, file);
    fputc(bitmap->compression >> 8, file);
    fputc(bitmap->compression, file);

    /*Ecrit la taille total de l'image*/
    fputc(bitmap->iSize >> 24, file);
    fputc(bitmap->iSize >> 16, file);
    fputc(bitmap->iSize >> 8, file);
    fputc(bitmap->iSize, file);

    /*Ecrit la resolution horizontale */
    fputc(bitmap->horizontalResolution >> 24, file);
    fputc(bitmap->horizontalResolution >> 16, file);
    fputc(bitmap->horizontalResolution >> 8, file);
    fputc(bitmap->horizontalResolution, file);

    /*Ecrit la resolution vertical */
    fputc(bitmap->verticalResolution >> 24, file);
    fputc(bitmap->verticalResolution >> 16, file);
    fputc(bitmap->verticalResolution >> 8, file);
    fputc(bitmap->verticalResolution, file);

    /*Ecrit la palette de couleur*/
    fputc(bitmap->paletteColor >> 24, file);
    fputc(bitmap->paletteColor >> 16, file);
    fputc(bitmap->paletteColor >> 8, file);
    fputc(bitmap->paletteColor, file);

    /*Ecrit le nombre de couleur importante de la palette*/
    fputc(bitmap->paletteImportantColor >> 24, file);
    fputc(bitmap->paletteImportantColor >> 16, file);
    fputc(bitmap->paletteImportantColor >> 8, file);
    fputc(bitmap->paletteImportantColor, file);

    /*Ecrit la palette*/
    fputc(bitmap->palette >> 24, file);
    fputc(bitmap->palette >> 16, file);
    fputc(bitmap->palette >> 8, file);
    fputc(bitmap->palette, file);

    fseek(file, bitmap->offset >> 24, SEEK_SET);
    /*Copy les pixel*/
    for(i = 0; i < bitmap->endiannesCorectionW * bitmap->endiannesCorectionH * 3; i+=3)
    {
        if(BMP_TransformBlackWhite(BMP_AverageBGR(bitmap->pixel[i], bitmap->pixel[i+1], bitmap->pixel[i+2])) == BMP_PIXEL_BLACK)
        {
            fputc(BMP_PIXEL_BLACK, file);
            fputc(BMP_PIXEL_BLACK, file);
            fputc(BMP_PIXEL_BLACK, file);
         }
        else
        {
            fputc(BMP_PIXEL_WHITE, file);
            fputc(BMP_PIXEL_WHITE, file);
            fputc(BMP_PIXEL_WHITE, file);
         }
    }
    fclose(file);
}
void BMP_Close(BMP_DataStructure* dataAllocationStructureBMP)
{
    free(dataAllocationStructureBMP->pixel);
    free(dataAllocationStructureBMP);
}

void BMP_ReadPixel(const BMP_DataStructure* const bitmap, const char* const path)
{
    uint32_t i = 0;
    FILE* file = fopen(path, "r");

    if(file == NULL)
    {
        printf("err\n");
        return;
    }
    fseek(file, bitmap->offset>>24, SEEK_SET);

    for(i = 0; i < bitmap->endiannesCorectionW * bitmap->endiannesCorectionH * 3; i+=3)
    {
        fseek(file, (bitmap->offset>>24)+i, SEEK_SET);
        printf("Iteration %d (%x %x %x)\n", i, fgetc(file), fgetc(file), fgetc(file));
    }
}


