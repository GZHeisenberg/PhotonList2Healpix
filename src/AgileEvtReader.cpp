
#include "AgileEvtReader.h"

void AgileEvtReader::readEvtFile(const char *selectionFilename, const char * templateFilename, EvtParams* evtParams)
{
	cout << "[AgileEvtReader] reading AGILE evt file.." << endl;

	AgileEvtParams * agileParams = (AgileEvtParams*) evtParams;
	agileParams->print();
	


	Intervals intervals;
 	Interval intv(agileParams->tmin, agileParams->tmax);
    intervals.Add(intv);

	string evtExpr = selection::EvtExprString(	intervals, 
						  	agileParams->emin,      // "Min energy"
							agileParams->emax,      // "Max energy"
							agileParams->albrad,    // "Radius of earth albedo (degrees)"
							agileParams->fovradmax, // "Min off-axis angle (degrees)"
							agileParams->fovradmin, // "Max off-axis angle (degrees)"
							agileParams->phasecode, // "Orbital phase code"
							agileParams->filtercode // "Event filter code"
						 );

	cout << "\nString evtExpr: " << evtExpr << endl;


	/*char selectionFilename[FLEN_FILENAME];
    char templateFilename[FLEN_FILENAME];
    tmpnam(selectionFilename);
    tmpnam(templateFilename);*/

	int status = selection::MakeSelection(agileParams->evtFilePath, intervals, evtExpr, selectionFilename, templateFilename);

							
	if (status != 0 && status != -118) {
        cout << endl << "AG_AgileEvtReader......................selection failed" << endl;
        FitsFile sfile(selectionFilename);
        sfile.Delete();
        FitsFile tfile(templateFilename);
        tfile.Delete();
        exit(EXIT_FAILURE);
    }



}  
