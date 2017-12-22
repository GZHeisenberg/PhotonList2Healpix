/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#ifndef AGILEEVTREADER_H
#define AGILEEVTREADER_H

#include <iostream>
#include <string>
#include <FitsUtils.h>

// Agile
#include <Selection.h>
#include "EvtReader.h"
#include "EvtParams.h"

using std::cout;
using std::endl;

class AgileEvtReader : public EvtReader
{
    public:

	AgileEvtReader(){}

	// Implements superclass method	
        void readEvtFile(const char *selectionFilename,  const char *templateFilename,EvtParams* evtParams);

};


#endif


