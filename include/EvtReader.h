/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#ifndef EVTREADER_H
#define EVTREADER_H

#include "EvtParams.h"
#include "Intervals.h"

class EvtReader
{
    public:
        virtual ~EvtReader() {}
        virtual void readEvtFile(const char *selectionFilename,  const char *templateFilename,EvtParams* evtParams) = 0;
};



#endif
