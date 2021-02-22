#include "filhead.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    char infilename[150], outfilename[150], headfilename[150];
    char jname[20];
    double mjd, freq, bw, tsmpl;
    int nchan;

    if(argc != 10){
        fprintf(stderr, "Invalid number of arguments.\n");
        exit(1);
    }
    
    //infile, outfile, jname, mjd, freq, nchan, bw, tsmpl, headfile
    strcpy(infilename,  argv[1]);
    strcpy(outfilename, argv[2]);
    strcpy(jname,       argv[3]);
    mjd     = atof(argv[4]);
    freq    = atof(argv[5]);
    nchan   = atoi(argv[6]);
    bw      = atof(argv[7]);
    tsmpl   = atof(argv[8]);
    strcpy(headfilename,argv[9]);
    
    if(mjd==0 || freq<=0 || nchan<=0 || bw==0 || tsmpl<=0){
        fprintf(stderr, "Invalid arguments found.\n");
        exit(1);
    }
    
    FILE *outfile = fopen(headfilename, "wb");
    if(outfile==NULL){
        fprintf(stderr, "Error opening file %s for writing.\n", headfilename);
        exit(1);
    }
    
    filterbank_header(outfile, infilename, jname, mjd, freq, bw, nchan, tsmpl);
    
    fclose(outfile);    

    return 0;
}
