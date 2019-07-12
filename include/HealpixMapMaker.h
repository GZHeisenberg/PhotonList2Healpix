/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/



#include <iostream>
#include <healpix_map.h>
#include <healpix_base.h>
#include <fitshandle.h>
#include <healpix_map_fitsio.h>
#include <Selection.h>
#include <Eval.h>
#include <string>
#include <cstring>

#include "EvtReader.h"
#include "EvtParams.h"
#include "HealpixParams.h"
#include "FitsUtils.h"



using namespace std;



class HealpixMapMaker
{
	public:

		static int EvalCountsHealpix(string outfile, int healpix_order, string healpix_schema, EvtReader * evtReader, EvtParams* evtParams, const char *selectionFilename, double tmin, double tmax); //const char *templateFilename,

	private:

		HealpixMapMaker();

};
