#include "ugmrt2fil.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


template <typename T>
void ugmrtstokes2fil(FILE *infile, FILE *outfile, const char *infilename, const char *jname, int mjd, double freq, double bw, int nchan, double tsmpl, int nbit, int usb){

    fseek(infile, 0, SEEK_END);
    long infile_size = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    const int npol = 4;

    long data_size = sizeof(T)*nchan*npol;
    
    if((infile_size%data_size) != 0){
        fprintf(stderr, "The input file size is incompatible with given nchan, nbit and npol.\n");
        fprintf(stderr, "Exiting...\n");
        return;
    }
    
    long Nsmpl = infile_size/data_size;
    
    filterbank_header(outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl, nbit, npol);
    
    T *data = (T*)malloc(data_size);
    
    for(long ismpl=0; ismpl<Nsmpl; ismpl++){
        fread(data, sizeof(T), nchan, infile);
        
        correct_stokes<T>(data, nchan);
        
        if(usb){
            reverse_channels<T>(data, nchan, npol);
        }
        
        fwrite(data, sizeof(T), nchan, outfile);
    } 
    
    free(data);
}

int main(int argc, char **argv){

    char infilename[150], outfilename[150];
    char jname[20];
    double mjd, freq, bw, tsmpl;
    int nchan, nbit, usb;
        
    if(argc != 11){
        fprintf(stderr, "Invalid number of arguments.\n");
        exit(1);
    }
    
    //infile, outfile, jname, mjd, freq, nchan, bw, tsmpl
    strcpy(infilename,  argv[1]);
    strcpy(outfilename, argv[2]);
    strcpy(jname,       argv[3]);
    mjd     = atof(argv[4]);
    freq    = atof(argv[5]);
    nchan   = atoi(argv[6]);
    bw      = atof(argv[7]);
    tsmpl   = atof(argv[8]);
    nbit    = atoi(argv[9]);
    usb     = atoi(argv[10]);
    
    if(mjd==0 || freq<=0 || nchan<=0 || bw==0 || tsmpl<=0 || (!(nbit==8 || nbit==16)) ){
        fprintf(stderr, "Invalid argument(s) found.\n");
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
        ugmrtstokes2fil<uint8_t>(infile, outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl, nbit, usb);
    }
    else if(nbit == 16){
        ugmrtstokes2fil<uint16_t>(infile, outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl, nbit, usb);
    }
    
    fclose(infile);
    fclose(outfile);
    
    return 0;
}
