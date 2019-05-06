/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#include "CtaEvtReader.h"




void CtaEvtReader::readEvtFile(const char *selectionFilename, const char * templateFilename, EvtParams* evtParams)
{
	cout << "\n[CtaEvtReader] reading CTA evt file.." << endl;

	CtaEvtParams * ctaParams = (CtaEvtParams*) evtParams;
	ctaParams->print();


 	Intervals intervals;
 	Interval intv(ctaParams->tmin, ctaParams->tmax);
  intervals.Add(intv);


	string evtExpr = EvtExprString(intervals, 		// time interval, from tmin to tmax
															   ctaParams->emin,	//Min energy
															   ctaParams->emax); // Max energy



	cout << "\nString evtExpr: " << evtExpr << endl;

	/*char selectionFilename[FLEN_FILENAME];
    char templateFilename[FLEN_FILENAME];
    tmpnam(selectionFilename);
    tmpnam(templateFilename);
    */


	int status = selection::MakeSelection(ctaParams->evtFilePath, intervals, evtExpr, selectionFilename, templateFilename);

	if (status != 0 && status != -118) {
        cout << endl << "AG_CtaEvtReader......................selection failed" << endl;
        FitsFile sfile(selectionFilename);
        sfile.Delete();
        // FitsFile tfile(templateFilename);
        // tfile.Delete();
        exit(EXIT_FAILURE);
    }


}

string CtaEvtReader :: EvtExprString(const Intervals &intvs, double emin, double emax)
{
	if (intvs.Count() <= 0)
        return string("");
    stringstream str(std::ios_base::out);
    str << selection::TimesExprString(intvs);
    str << " && ENERGY >= " << emin;
    str << " && ENERGY <= " << emax;

    return str.str();
}
