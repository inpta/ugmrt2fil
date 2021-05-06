#include "filhead.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

template<typename T>
void reverse_channels(T *data, int nchan){
    int i, j;
    T tmp;
    
    for(i=0; i<nchan/2; i++){
        j = nchan-i-1;
        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}

template<typename T>
void ugmrtusb2fil(FILE *infile, FILE *outfile, const char *infilename, const char *jname, double mjd, double freq, double bw, int nchan, double tsmpl, int nbit){
    
    fseek(infile, 0, SEEK_END);
    long infile_size = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    
    long data_size = sizeof(T)*nchan;
    
    if((infile_size%data_size) != 0){
        fprintf(stderr, "The input file size is incompatible with given nchan.\n");
        fprintf(stderr, "Exiting...\n");
        return;
    }
    
    long Nsmpl = infile_size/data_size;
    
    filterbank_header(outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl, nbit);
    
    T *data = (T*)malloc(data_size);
    
    for(long ismpl=0; ismpl<Nsmpl; ismpl++){
        fread(data, sizeof(T), nchan, infile);
        reverse_channels<T>(data, nchan);
        fwrite(data, sizeof(T), nchan, outfile);
    } 
    
    free(data);
}

int main(int argc, char **argv){

    char infilename[150], outfilename[150];
    char jname[20];
    double mjd, freq, bw, tsmpl;
    int nchan, nbit;
    
    if(argc != 10){
        fprintf(stderr, "Invalid number of arguments.\n");
        exit(1);
    }
    
    //infile, outfile, jname, mjd, freq, nchan, bw, tsmpl, nbit
    strcpy(infilename,  argv[1]);
    strcpy(outfilename, argv[2]);
    strcpy(jname,       argv[3]);
    mjd     = atof(argv[4]);
    freq    = atof(argv[5]);
    nchan   = atoi(argv[6]);
    bw      = atof(argv[7]);
    tsmpl   = atof(argv[8]);
    nbit    = atoi(argv[9]);
    
    if(mjd==0 || freq<=0 || nchan<=0 || bw==0 || tsmpl<=0 || (nbit!=8 && nbit!=16)){
        fprintf(stderr, "Invalid arguments found.\n");
        exit(1);
    }
    
    FILE *infile = fopen(infilename, "rb");
    if(infile==NULL){
        fprintf(stderr, "Error opening file %s for reading.\n", infilename);
        exit(1);
    }
    
    FILE *outfile = fopen(outfilename, "wb");
    if(outfile==NULL){
        fprintf(stderr, "Error opening file %s for writing.\n", outfilename);
        exit(1);
    }
    
    if(nbit == 8){
        ugmrtusb2fil<uint8_t>(infile, outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl, nbit);
    }
    else if(nbit == 16){
        ugmrtusb2fil<uint16_t>(infile, outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl, nbit);
    }
    
    fclose(infile);
    fclose(outfile);
    
    return 0;
}
