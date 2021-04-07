#ifndef _filhead_h_
#define _filhead_h_

#include <stdio.h>

void send_string(FILE *outfile, char *string);
void send_float(FILE *outfile, char *name, float number);
void send_double(FILE *outfile, char *name, double number);
void send_int(FILE *outfile, char *name, int number);
void send_long(FILE *outfile, char *name, long number);

void filterbank_header(FILE *outfile, char *infilename, char *jname, double mjd, double freq, double bw, int nchan, double tsmpl);

#endif
