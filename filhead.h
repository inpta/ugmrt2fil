#ifndef _filhead_h_
#define _filhead_h_

#include <stdio.h>

void send_string(FILE *outfile, const char *string);
void send_float(FILE *outfile, const char *name, float number);
void send_double(FILE *outfile, const char *name, double number);
void send_int(FILE *outfile, const char *name, int number);
void send_long(FILE *outfile, const char *name, long number);

void filterbank_header(FILE *outfile, const char *infilename, const char *jname, double mjd, double freq, double bw, int nchan, double tsmpl, int nbits);

#endif
