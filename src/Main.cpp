/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#include <string>

#include "HduHandler.hpp"
#include "AgileEvtReader.h" // -> imports EvtReader too
#include "CtaEvtReader.h" // -> imports EvtReader too
#include "HealpixParams.h" // to remove
#include <PilParams.h>
#include "HealpixMapMaker.h"
#include "FileWriter.h"


using namespace std;

const char* startString = {
"################################################################\n"
"###             Task PhotonList2Healpix v0.0.1               ###\n"
};

const char* endString = {
"\n### Task PhotonList2Healpix exiting ......................... ###\n"
"#################################################################"
};


const PilDescription paramsDescr[] = {
    { PilString, "outfile", "Output file name" },
    { PilString, "evtType", "Event telescope source" },
    { PilString, "photonListPath", "Path of photon list"},


    //i successivi 5 sono relativi alla proiezione nel cielo
    { PilReal, "mdim", "Size of Map (degrees)" },
    { PilReal, "mres", "Heaplix resolution (level)" },
    { PilReal, "la", "Longitude of map center (galactic)" },
    { PilReal, "ba", "Latitude of map center (galactic)" },
    { PilReal, "lonpole", "Rotation of map (degrees)" },

    { PilReal, "albrad", "Radius of earth albedo (degrees)" },
    { PilInt, "phasecode", "Orbital phase code" },
    { PilInt, "filtercode", "Event filter code" },
    { PilReal, "tmin", "Initial time(sec)" },
    { PilReal, "tmax", "Final time(sec)" },
    { PilReal, "emin", "Min energy" },
    { PilReal, "emax", "Max energy" },
    { PilReal, "fovradmin", "Min off-axis angle (degrees)" },
    { PilReal, "fovradmax", "Max off-axis angle (degrees)" },
    { PilNone, "", "" }
};


int main(int argc, char *argv[])
{
    cout << startString << endl;

    PilParams params(paramsDescr);

    if (!params.Load(argc, argv))
        return EXIT_FAILURE;

    cout << endl << "INPUT PARAMETERS:" << endl;
    params.Print();

    // this file is for...
    char selectionFilename[FLEN_FILENAME];
    tmpnam(selectionFilename);

    // this file is for...
    char templateFilename[FLEN_FILENAME];
    tmpnam(templateFilename);



  	// Data to insert in EVT.index
  	const char * evtFile = "./INDEX/EVT.index";
    const char * _photonListPath = params["photonListPath"];
    string _pLP(_photonListPath);
  	double _tmin = params["tmin"];
  	double _tmax = params["tmax"];

  	// Create EVT.index
    string input2write = _pLP +" "+ to_string(_tmin) + " " + to_string(_tmax);
    FileWriter :: write2File(evtFile,input2write);
    cout << "\nEVT file created!\n"<< endl;

  	EvtReader * evtReader;
  	EvtParams * readerParams; // emin, emax, phasecode, filtercode, tmin, tmax


  	HealpixParams healpix2WriteParams(params["mdim"],params["mres"],params["la"],params["ba"], params["lonpole"]);

    #ifdef DEBUG
  	healpix2WriteParams.print();
    #endif

  	string _evtType (params["evtType"]);


  	if( _evtType == "AGILE")
  	{
  		cout << "AGILE selected" << endl;

  		evtReader    = new AgileEvtReader();

  		readerParams  = new AgileEvtParams( evtFile,
                            							params["emin"],
                            							params["emax"],
                            							params["albrad"],
                            							params["fovradmin"],
                            							params["fovradmax"],
                            							params["phasecode"],
                            							params["filtercode"],
                            							params["tmin"],
                            							params["tmax"]
                            						);
  	}
  	else if( _evtType == "CTA")
  	{
  		cout << "CTA selected" << endl;

  		evtReader = new CtaEvtReader();

  		readerParams = new CtaEvtParams(	evtFile,
                          							params["emin"],
                          							params["emax"],
                          							params["tmin"],
                          							params["tmax"]
                          						);
  	}


    evtReader->readEvtFile(selectionFilename, templateFilename, readerParams);


  	int status = HealpixMapMaker :: EvalCountsHealpix(	params["outfile"],
                                          							evtReader,
                                          							readerParams,
                                          							healpix2WriteParams,
                                          							selectionFilename,
                                                        _tmin,
                                                        _tmax
                                          						);

    if(status > 0)
    {
      char err_text[50];
      fits_get_errstatus(status, &err_text[0]);
      cout << "Errors from EvalCountsHealpix (cfitsio error=" << err_text << ")";

    }
    else
    {
      cout << "No errors from EvalCountsHealpix (status=" << status << ")";
    }

    // Adding keyword for the reference coordinate system
    HduHandler * hduHandlerOutFile;
    // Adding keyword for the reference coordinate system
    char keyname[20] = "COORDSYS";
    char value[20] = "C       ";
    char comment[50] = "Ecliptic, Galactic or Celestial (equatorial)";
    hduHandlerOutFile->writeKeysValue(params["outfile"], 2, keyname, value, comment);


  	cout << endString << endl;
  	return 0;
}
