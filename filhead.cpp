#include "filhead.h"
#include <string.h>

/*
    This part of the code is based on sigproc program by Duncan Lorimer.
*/

void send_string(FILE *outfile, const char *string){
    int len;
    len = strlen(string);
    fwrite(&len, sizeof(int), 1, outfile);
    fwrite(string, sizeof(char), len, outfile);
}

void send_float(FILE *outfile, const char *name, float number){
    send_string(outfile, name);
    fwrite(&number, sizeof(float), 1, outfile);
}

void send_double(FILE *outfile, const char *name, double number){
    send_string(outfile, name);
    fwrite(&number, sizeof(double), 1, outfile);
}

void send_int(FILE *outfile, const char *name, int number){
    send_string(outfile, name);
    fwrite(&number, sizeof(int), 1, outfile);
}

void send_long(FILE *outfile, const char *name, long number){
    send_string(outfile, name);
    fwrite(&number, sizeof(long), 1, outfile);
}

void filterbank_header(FILE *outfile, const char *infilename, const char *jname, int mjd, double freq, double bw, int nchan, double tsmpl, int nbit, int npol){
    
    int nbeams = 1;
    int ibeam = 1;
    int machine_id = 14;
    int telescope_id = 7;
  
    /* broadcast the header parameters to the output stream */
    send_string(outfile, "HEADER_START");
    
    send_string(outfile, "rawdatafile");
    send_string(outfile, infilename);
    
    //send_string(outfile, "source_name");
    //send_string(outfile, jname);
    
    send_int(outfile, "machine_id", machine_id);
    send_int(outfile, "telescope_id", telescope_id);
    
    send_double(outfile, "src_raj", 0);
    send_double(outfile, "src_dej", 0);
    send_double(outfile, "az_start", 0);
    send_double(outfile, "za_start", 0);
    
    send_int(outfile, "data_type", 1);
      
    send_double(outfile, "fch1", freq);
    send_double(outfile, "foff", bw);
    send_int(outfile, "nchans", nchan);
    
    send_int(outfile, "nbeams", nbeams);
    send_int(outfile, "ibeam", ibeam);
    
    send_int(outfile, "nbits", nbit);
    
    send_double(outfile, "tstart", mjd);
    
    send_double(outfile, "tsamp", tsmpl);
    
    send_int(outfile, "nifs", npol);
    
    send_string(outfile, "HEADER_END");

}

