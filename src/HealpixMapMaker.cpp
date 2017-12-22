/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino, Alessio Diamanti
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/


#include "HealpixMapMaker.h"

HealpixMapMaker :: HealpixMapMaker () 
{
	// constructor
}

int HealpixMapMaker :: EvalCountsHealpix (const char * outfile, EvtReader * evtReader, EvtParams* evtParams, HealpixParams healpix2WriteParams, const char *selectionFilename,  const char *templateFilename, Intervals intervals) {
	
	cout << "Healpix Map Maker" << endl;
	
	const char *_outfile = outfile;
	string OutFilePath(_outfile);
	OutFilePath = "./HEALPIX_MAPS/" + OutFilePath;
	
    int status = 0;

    long mxdim = long(healpix2WriteParams.mdim / healpix2WriteParams.mres + 0.1); // dimension (in pixels) of the map
    


    cout << "mdim: " << healpix2WriteParams.mdim << " mres: " << healpix2WriteParams.mres << " mxdim: " << mxdim << endl; 
    
    
	vector< vector<int> > counts;

    long npixels = mxdim * mxdim;
    counts.resize(intervals.Count());

    //crea l'array di pixels
    for (int i=0; i < intervals.Count(); i++) {
		
        counts[i].resize(npixels);
        for (int j=0; j < npixels; j++)
            counts[i][j] = 0;
    }

    int hdutype;
    fitsfile* selectionFits;
        
    if (fits_open_file(&selectionFits, selectionFilename, READONLY, &status)) {
        cerr << "ERROR opening selection file " << selectionFilename << endl;
        return -1;
    }
    fits_movabs_hdu(selectionFits, 2, &hdutype, &status);

    fitsfile* templateFits;
    if (fits_open_file(&templateFits, templateFilename, READWRITE, &status)) {
        cerr << "ERROR opening template file " << templateFilename << endl;
        return -1;
    }
    fits_movabs_hdu(templateFits, 2, &hdutype, &status);
    
    long oldnrows;
    fits_get_num_rows(templateFits, &oldnrows, &status);
    fits_delete_rows(templateFits, 1, oldnrows, &status);

    cout << "Evaluating counts.." << endl;
    


    int totalCounts = 0;
    int Nside = pow(2,healpix2WriteParams.mres);
    Healpix_Map<int> map((int)healpix2WriteParams.mres,NEST); // NEST is chosen for seek of efficency
    
    cout << "mres = " << healpix2WriteParams.mres << endl;
        
 	for( int i = 0; i < map.Npix(); i++){ 	//initialize the healpix map to all zeros
		
		map[i]=0;
		
	}
	
    for (int intvIndex = 0; intvIndex < intervals.Count(); intvIndex++) {
		


        cout << "Interval # " << intvIndex << endl;
        

        Intervals sIntv;
        sIntv.Add(intervals[intvIndex]);
        string selExpr = selection::TimesExprString(sIntv);
        


        cout << "selExpr: " << selExpr << endl;
        

        
        fits_select_rows(selectionFits, templateFits, (char*)selExpr.c_str(), &status);
        long nrows;
        fits_get_num_rows(templateFits, &nrows, &status);
        


        cout << "Reading all " << nrows << " rows" << endl;
        

		int raColumn, decColumn;
        fits_get_colnum(templateFits, 1, (char*)"RA", &raColumn, &status);
        fits_get_colnum(templateFits, 1, (char*)"DEC", &decColumn, &status);

        double ra, dec, l, b, the, x, y, i = 0, ii = 0;
        double baa = healpix2WriteParams.baa * DEG2RAD;
        double laa = healpix2WriteParams.laa * DEG2RAD;
        
        for ( long k = 0; k<nrows; k++ ) {
			
            fits_read_col(templateFits, TDOUBLE, raColumn, k+1, 1, 1, NULL, &ra, NULL, &status);
            fits_read_col(templateFits, TDOUBLE, decColumn, k+1, 1, 1, NULL, &dec, NULL, &status);
            Euler(ra, dec, &l, &b, 1);
            l *= DEG2RAD;
            b *= DEG2RAD;

			pointing point = pointing((M_PI/2)-b,l); // Encodes an angular position on unitary sphere as colatitude and longitude
			int index = map.ang2pix(point);
			map[index]++;

        }
        
        if (nrows > 0)
            fits_delete_rows(templateFits, 1, nrows, &status);
    }
    

    
    cout << "Ending Healpix evaluation " << endl;

	// Save Healpix map
	remove(OutFilePath.c_str());
	fitshandle handle = fitshandle() ;
	handle.create(OutFilePath.c_str());
	write_Healpix_map_to_fits(handle,map,PLANCK_INT64);
	fits_close_file(selectionFits, &status);
	fits_close_file(templateFits, &status);

    return status;
}
	

