#include "filhead.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void reverse_channels(uint16_t *data, int nchan){
    int i, j;
    uint16_t tmp;
    
    for(i=0; i<nchan/2; i++){
        j = nchan-i-1;
        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}

int main(int argc, char **argv){

    char infilename[150], outfilename[150];
    char jname[20];
    double mjd, freq, bw, tsmpl;
    int nchan;
    
    long infile_size, Nsmpl, ismpl;
    int data_size;
    
    uint16_t *data;
    
    if(argc != 9){
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
    
    if(mjd==0 || freq<=0 || nchan<=0 || bw==0 || tsmpl<=0){
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
    
    data_size = sizeof(uint16_t)*nchan;
    
    fseek(infile, 0, SEEK_END);
    infile_size = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    if((infile_size%data_size) != 0){
        fprintf(stderr, "The input file size is incompatible with given nchan.\n");
        exit(1);
    }
    
    Nsmpl = infile_size/data_size;
    
    filterbank_header(outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl);
    
    data = (uint16_t*)malloc(data_size);
    
    for(ismpl=0; ismpl<Nsmpl; ismpl++){
        fread(data, sizeof(uint16_t), nchan, infile);
        reverse_channels(data, nchan);
        fwrite(data, sizeof(uint16_t), nchan, outfile);
    } 
    
    free(data);
    
    fclose(infile);
    fclose(outfile);
    
    return 0;
}
