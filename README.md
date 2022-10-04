# ugmrt2fil
Convert uGMRT raw data files to sigproc-filterbank format. Only total intensity 16-bit data is supported at present.

Usage
======
`$ ugmrt2fil -i <infile> -o <outfile> -j <JNAME> -d <mjd> -f <freq> -c <nchan> -w <bandwidth> -t <sampling_time> [-u] [-h]`

|Option | Description                              |
|-------|------------------------------------------|
|`-i`   | Input file in uGMRT raw data format      |
|`-u`   | Output file in sigproc filterbank format |
|`-j`   | JNAME of the source                      |
|`-d`   | Timestamp in MJD                         |
|`-f`   | Observing frequency (MHz)                |
|`-c`   | Number of channels                       |
|`-w`   | Bandwidth of a single channel (MHz)      |
|`-t`   | Sampling time (s)                        |
|`-u`   | Enable USB (Default is LSB)              |
|`-h`   | Display help message.                    |
