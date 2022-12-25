#include "lz77.h"
#include "lz78.h"
#include "RLE.h"
#include "Huffman.h"
#include "fano.h"

int main(){
    setlocale(LC_ALL, "Russian");
    lz78("tertrektekertektrek");
    lz77("1110100110110001101");
    rle("MIREA");
    huffman("Ivanov Alexander Dmitrievich");
    fano("fano.txt");
}