#ifndef __BMP__H_INCLUDED

#include <stdio.h> /* Inclus pour utilisez les flux d'entré et de sortis */
#include <stdlib.h>
#include <stdint.h> /* Inclus des types dont la place mémoire ne dépend pas de l'os */

enum BMP_HEADER_OFFSET
{
    BMP_OFFSET_SIGNATURE = 0x0,
    BMP_OFFSET_FSIZE = 0x2,
    BMP_OFFSET_RESERVED = 6,
    BMP_OFFSET_START = 0xA,
    BMP_OFFSET_HEADER = 0xE,
    BMP_OFFSET_WIDTH = 0x12,
    BMP_OFFSET_HEIGHT = 0x16,
    BMP_OFFSET_NUMBER_OF_PLAN = 0x1A,
    BMP_OFFSET_CODING_DEPTH = 0x1C,
    BMP_OFFSET_COMPRESSION = 0x1E,
    BMP_OFFSET_ISIZE = 0x22,
    BMP_OFFSET_HORIZONTAL_RESOLUTION = 0x26,
    BMP_OFFSET_VERTICAL_RESOLUTION = 0x2A,
    BMP_OFFSET_PALETTE_COLOR = 0x2E,
    BMP_OFFSET_IMPORTANT_PALETTE = 0x32,
    BMP_OFFSET_PALETTE = 0x36
};

enum BMP_PIXEL_MAP
{
    BMP_PIXEL_BLACK = 0,
    BMP_PIXEL_WHITE = 255,
    BMP_PIXEL_COLOR_BLACK = 32,
    BMP_PIXEL_COLOR_WHITE = 178
};

/*
    Définition de la structure pour le traitement d'image bitmap
*/
typedef struct BMP_DataStructure
{
            /* Définition BGR (BVR) */
    uint8_t* pixel; /* La composante bleu */


    uint32_t offset; /* Le décalage  */
    uint32_t w; /* La largeur de l'image */
    uint32_t h; /* La hauteur de l'image */
    uint32_t fSize; /* La taille totale de l'image */
    uint32_t header; /*La taille de l'entête de l'image en octet*/
    uint32_t reserved; /*Le champ reservé*/
    uint32_t compression; /*La compression*/
    uint32_t iSize; /*La taille total de l'image*/
    uint32_t horizontalResolution; /*La resolution horizontale */
    uint32_t verticalResolution; /*La resolution vertical*/
    uint32_t paletteColor; /*La couleur de la palette*/
    uint32_t paletteImportantColor; /*Le nombre de couleur importante de la palette*/
    uint32_t palette; /*La pelette */
    uint32_t endiannesCorectionW; /*Corection du boutisme pour la largeur*/
    uint32_t endiannesCorectionH; /*Correction du boutisme pour la hauteur*/


    uint16_t signature; /* En tête du format BMP */
    uint16_t nop; /*Le nombre de plan*/
    uint16_t codingDepth; /* Profondeur de codage */
}BMP_DataStructure;

BMP_DataStructure* BMP_LoadImage(const char* const path);
void BMP_InfoBitmap(const BMP_DataStructure* const bitmap);
uint8_t BMP_AverageBGR(uint8_t const cBlue, uint8_t const cGreen, uint8_t const cRed);
uint8_t BMP_TransformBlackWhite(uint32_t const color);
void BMP_ReadPixel(const BMP_DataStructure* const bitmap, const char* const path);
void BMP_Copy(const BMP_DataStructure* const bitmap, const char* const name);
void BMP_Close(BMP_DataStructure* dataAllocationStructureBMP);

#endif // __BMP__H_INCLUDED
