/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#ifndef HDU_READER_H
#define HDU_READER_H

#include <iostream>
#include <string.h>

#include "FitsUtils.h"
#include "EvtParams.h"

using namespace std;

class HduHandler
{
  public:
    HduHandler();
    int readHdu(const char * evtPath);
    int readHduKeysValue(fitsfile* fitsptr, int hdunum);
    int writeKeysValue(const char * evtPath, int hdunum, char * keyname, char * value, char *comment);

};

#endif
