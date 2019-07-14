/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#include <string>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "HduHandler.hpp"
#include "AgileEvtReader.h" // -> imports EvtReader too
#include "CtaEvtReader.h" // -> imports EvtReader too
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
    { PilString, "outfile", "Output file name. (Healpix order and Fits extension will be automatically added)" },
    { PilString, "outfolder", "The name of the output folder" },
    { PilString, "photon_list_type", "Event telescope source" },
    { PilString, "photon_list_path", "Path of photon list"},
    { PilInt, "healpix_order", "Healpix map resolution (k)" },
    { PilString, "healpix_schema", "Healpix map schema"},
    // AGILE and CTA selection parameters
    { PilReal, "tmin", "Initial time(sec). Put -1 to ignore the time lower bound." },
    { PilReal, "tmax", "Final time(sec). Put -1 to ignore the time upper bound." },
    { PilReal, "emin", "Min energy. Put -1 to ignore the energy lower bound." },
    { PilReal, "emax", "Max energy. Put -1 to ignore the energy upper bound." },
    // only-AGILE selection parameters
    { PilReal, "albrad", "Radius of earth albedo (degrees)" },
    { PilInt, "phasecode", "Orbital phase code" },
    { PilInt, "filtercode", "Event filter code" },
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
    cout << endl;

    // temporary files used for selection event phase
    char selectionFilename[FLEN_FILENAME];
    tmpnam(selectionFilename);
    // mkstemp(selectionFilename);

    char templateFilename[FLEN_FILENAME];
    tmpnam(templateFilename);
    // mkstemp(templateFilename);

    int healpix_order = params["healpix_order"];
    string healpix_schema = string(params["healpix_schema"]);

    if( (healpix_schema!="RING") && (healpix_schema!="NEST") )
    {
      cout<< healpix_schema<< endl;
      cerr << "ERROR! Healpix map schema not valid!"<<endl;
  		exit(1);
    }

    double tmin = params["tmin"];
  	double tmax = params["tmax"];
    if (tmin == -1) tmin = 0;
    if (tmax == -1) tmax = 9999999999;

    double emin = params["emin"];
  	double emax = params["emax"];
    if (emin == -1) emin = 0;
    if (emax == -1) emax = 9999999999;


    // Creating output filename
    string outfolder = string(params["outfolder"]);
    string outfile = string(params["outfile"]);
    outfile += "_t_"+to_string(tmin)+"_"+to_string(tmax);
    outfile += "_e_"+to_string(emin)+"_"+to_string(emax);
    outfile += "_k_"+to_string(healpix_order)+".fits";

    outfile = outfolder+"/"+outfile;

    cout << "* Output filename: " << outfile << endl;

    // Creating the INDEX directory
    if (mkdir("./INDEX", 0777) != -1)
      cout << "* INDEX directory created" << endl;

    // Creating the INDEX directory
    if (mkdir(outfolder.c_str(), 0777) != -1)
      cout << "* Output "<<outfolder<<" directory created" << endl;

    // Creating EVT.index
  	const char * evtFile = "./INDEX/EVT.index";



    string plp = string(params["photon_list_path"]);
    string input2write = plp +" "+ to_string(tmin) + " " + to_string(tmax);
    FileWriter :: write2File(evtFile,input2write);
    cout << "* EVT file created! Content: " << input2write << endl;


  	EvtReader * evtReader;
  	EvtParams * readerParams; // emin, emax, phasecode, filtercode, tmin, tmax

    // not used anymore
  	//HealpixParams healpix2WriteParams(params["mdim"],healpix_order,params["la"],params["ba"], params["lonpole"]);



  	string _photon_list_type (params["photon_list_type"]);


  	if( _photon_list_type == "AGILE")
  	{
  		// cout << "AGILE selected" << endl;

  		evtReader     = new AgileEvtReader();

  		readerParams  = new AgileEvtParams( evtFile,
                            							emin,
                                          emax,
                            							params["albrad"],
                            							params["fovradmin"],
                            							params["fovradmax"],
                            							params["phasecode"],
                            							params["filtercode"],
                            							tmin,
                            							tmax
                            						);
  	}
  	else if( _photon_list_type == "CTA")
  	{
  		// cout << "CTA selected" << endl;

  		evtReader = new CtaEvtReader();

  		readerParams = new CtaEvtParams(	evtFile,
                          							emin,
                          							emax,
                          							tmin,
                          							tmax
                          						);
  	}


    evtReader->readEvtFile(selectionFilename, templateFilename, readerParams);


  	int status = HealpixMapMaker :: EvalCountsHealpix(	outfile,
                                                        healpix_order,
                                                        healpix_schema,
                                          							evtReader,
                                          							readerParams,
                                          							selectionFilename,
                                                        tmin,
                                                        tmax
                                          						);

    if(status > 0)
    {
      char err_text[50];
      fits_get_errstatus(status, &err_text[0]);
      cout << "Errors from EvalCountsHealpix (cfitsio error=" << err_text << ")";

    }


    // Adding keyword for the reference coordinate system
    HduHandler * hduHandlerOutFile;

    // Adding keyword for the reference coordinate system
    char coordsys_keyname[20] = "COORDSYS";
    char coordsys_value[20] = "G       ";
    char coordsys_comment[50] = "Ecliptic, Galactic or Celestial (equatorial)";
    hduHandlerOutFile->writeKeysValue(outfile, 2, coordsys_keyname, coordsys_value, coordsys_comment);


  	cout << endString << endl;
  	return 0;
}
