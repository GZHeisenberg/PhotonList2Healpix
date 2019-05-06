/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#include <iostream>
#include <string>
#include <Selection.h>
#include <PilParams.h>
#include <FitsUtils.h>
#include <sstream>

#include "EvtReader.h"
#include "EvtParams.h"


using std::cout;
using std::endl;

class CtaEvtReader : public EvtReader
{
	public:

		CtaEvtReader() {};
		string EvtExprString(const Intervals &intvs, double emin, double emax);
    void readEvtFile(const char *selectionFilename,  const char *templateFilename,EvtParams* evtParams);
};
