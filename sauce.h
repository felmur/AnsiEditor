#ifndef SAUCE_H
#define SAUCE_H
#include <cstdint>

struct _sauce {
    char ID[5];          // SAUCE identification. This should be equal to "SAUCE"
    char version[2];     // SAUCE version number, should be "00"
    char title[35];      // The title of the file
    char author[20];     // The (nick)name or handle of the creator of the file.
    char group[20];      // The name of the group or company the creator is employed by.
    char date[8];        // The date the file was created. The format for the date is CCYYMMDD (century, year, month, day).
    uint32_t size=0;       // The original file size not including the SAUCE information
    uint8_t datatype=0;	 // Type of data
    uint8_t filetype=0;	 // Type of file
    uint16_t tinfo1=0;     // Type dependant numeric information field 1
    uint16_t tinfo2=0;     // Type dependant numeric information field 2
    uint16_t tinfo3=0;     // Type dependant numeric information field 3
    uint16_t tinfo4=0;     // Type dependant numeric information field 4
    uint8_t comments=0;    // Number of lines in the extra SAUCE comment block. 0 indicates no comment block is present.
    uint8_t flags=0;       // Type dependant flags
    char tinfos[22];      // Type dependant string information field
} __attribute__((__packed__));

#endif // SAUCE_H
