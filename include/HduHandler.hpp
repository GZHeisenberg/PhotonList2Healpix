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
    int readHdu(const char * evtPath/*, const char * selectionFilename, const char *templateFilename*/);
    int readHduKeysValue(fitsfile* fitsptr, int hdunum);
    int writeKeysValue(const char * evtPath, int hdunum, char * keyname, char * value, char *comment);


    // int hdutype = 0;
  	// int status = 0;
  	// int keysexist=0;
  	// int morekeys =0;
    // int hdunum = 0;
    // int keynum = 0;
    // fitsfile* fitsptr;

  private:



};

#endif
