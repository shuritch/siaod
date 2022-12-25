#include "fano.h"
static int pnode_compare(const void* elem1, const void* elem2) {
    const pnode a = *(pnode*)elem1;
    const pnode b = *(pnode*)elem2;
    if (a.p < b.p) return 1;
    else if (a.p > b.p) return -1;
    return 0;
}

void Coder::Encode(const char* inputFilename, const char* outputFilename) {
    map<char, int> freqs;
    int i;

    FILE* inputFile;
    inputFile = fopen(inputFilename, "r");
    assert(inputFile);

    char ch;
    unsigned total = 0;
    float bits = 0;
    while (fscanf(inputFile, "%c", &ch) != EOF) {
        freqs[ch]++;
        total++;
        bits += 1;
    }
    tsize = (int)freqs.size();

    ptable = new pnode[tsize];
    assert(ptable);
    float ftot = float(total);
    map<char, int>::iterator fi;
    for (fi = freqs.begin(), i = 0; fi != freqs.end(); ++fi, ++i) {
        ptable[i].ch = (*fi).first;
        ptable[i].p = float((*fi).second) / ftot * 100;
    }
    qsort(ptable, tsize, sizeof(pnode), pnode_compare);

    EncShannon(0, tsize - 1);

    FILE* outputFile;
    outputFile = fopen(outputFilename, "wb");
    assert(outputFile);


    printf("TABLE SIZE: %i\n", tsize);
    fprintf(outputFile, "%i\n", tsize);
    for (i = 0; i < tsize; i++) {
        printf("%c\t%f\t%s\n", ptable[i].ch, ptable[i].p, codes[ptable[i].ch].c_str());
        fprintf(outputFile, "%c\t%f\t%s\n", ptable[i].ch, ptable[i].p, codes[ptable[i].ch].c_str());
    }

    fseek(inputFile, SEEK_SET, 0);
    printf("\n");
    fprintf(outputFile, "\n");
    float bits2 = 0;
    while (fscanf(inputFile, "%c", &ch) != EOF)
    {
        bits2 += codes[ch].length();
        printf("%s", codes[ch].c_str());
        fprintf(outputFile, "%s", codes[ch].c_str());
    }
    printf("\n");
    cout << "\n%: " << bits * 8 / bits2  << endl;
    codes.clear();
    delete[] ptable;
    fclose(outputFile);
    fclose(inputFile);
}

void Coder::Decode(const char* inputFilename, const char* outputFilename) {

    FILE* inputFile;
    inputFile = fopen(inputFilename, "r");
    assert(inputFile);

    fscanf(inputFile, "%i", &tsize);
    char ch, code[128];
    float p;
    int i;
    fgetc(inputFile);
    for (i = 0; i < tsize; i++)
    {
        ch = fgetc(inputFile);
        fscanf(inputFile, "%f %s", &p, code);
        codes[ch] = code;
        fgetc(inputFile);
    }
    fgetc(inputFile);

    FILE* outputFile;
    outputFile = fopen(outputFilename, "w");
    assert(outputFile);

    string accum = "";
    map<char, string>::iterator ci;
    while ((ch = fgetc(inputFile)) != EOF) {
        accum += ch;
        for (ci = codes.begin(); ci != codes.end(); ++ci)
            if (!strcmp((*ci).second.c_str(), accum.c_str())) {
                accum = "";
                printf("%c", (*ci).first);
                fprintf(outputFile, "%c", (*ci).first);
            }
    }
    printf("\n");
    fclose(outputFile);
    fclose(inputFile);
}

void Coder::EncShannon(int li, int ri) {
    int i, isp;
    float p;
    float pfull;
    float phalf;

    if (li == ri) return;
    else if (ri - li == 1) {
        codes[ptable[li].ch] += '0';
        codes[ptable[ri].ch] += '1';
    }
    else {
        pfull = 0;
        for (i = li; i <= ri; ++i) pfull += ptable[i].p;
        p = 0;
        isp = -1;
        phalf = pfull * 0.5f;
        for (i = li; i <= ri; ++i) {
            p += ptable[i].p;
            if (p <= phalf)  codes[ptable[i].ch] += '0';
            else {
                codes[ptable[i].ch] += '1';
                if (isp < 0) isp = i;
            }
        }

        if (isp < 0) isp = li + 1;
        EncShannon(li, isp - 1);
        EncShannon(isp, ri);
    }
}


int fano(const char* decoded) {
    Coder* coder;
    coder = new Coder;
    assert(coder);
    cout << "\nEncoded Fano data:\n";
    coder->Encode(decoded, "encoded.txt");
    cout << "\nDecoded Fano data:\n";
    coder->Decode("encoded.txt", "decoded.txt");
    delete coder;
    printf("\n");
    return 0;
}