#include "libs.h"
#include "lz77.h"
#include "lz78.h"
#include "RLE.h"
#include "Huffman.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    lz78("tertrektekertektrek");
    lz77("1110100110110001101");
    rle("WWWAAAWWWAWW");
    huffman("Ivanov Alexander Dmitrievich");
}