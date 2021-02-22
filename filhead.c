#include "filhead.h"
#include <string.h>

void send_string(FILE *outfile, char *string){
    int len;
    len = strlen(string);
    fwrite(&len, sizeof(int), 1, outfile);
    fwrite(string, sizeof(char), len, outfile);
}

void send_float(FILE *outfile, char *name, float number){
    send_string(outfile, name);
    fwrite(&number, sizeof(float), 1, outfile);
}

void send_double(FILE *outfile, char *name, double number){
    send_string(outfile, name);
    fwrite(&number, sizeof(double), 1, outfile);
}

void send_int(FILE *outfile, char *name, int number){
    send_string(outfile, name);
    fwrite(&number, sizeof(int), 1, outfile);
}

void send_long(FILE *outfile, char *name, long number){
    send_string(outfile, name);
    fwrite(&number, sizeof(long), 1, outfile);
}

void filterbank_header(FILE *outfile, char *infilename, char *jname, int mjd, double freq, double bw, int nchan, double tsmpl){
    
    int nbits = 16;
    int nbeams = 1;
    int ibeam = 1;
    int nifs = 1;
    int machine_id = 14;
    int telescope_id = 7;
  
    /* broadcast the header parameters to the output stream */
    send_string(outfile, "HEADER_START");
    
    send_string(outfile, "rawdatafile");
    send_string(outfile, infilename);
    
    send_string(outfile, "source_name");
    send_string(outfile, jname);
    
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
    
    send_int(outfile, "nbits", nbits);
    
    send_double(outfile, "tstart", mjd);
    
    send_double(outfile, "tsamp", tsmpl);
    
    send_int(outfile, "nifs", nifs);
    
    send_string(outfile, "HEADER_END");

}

