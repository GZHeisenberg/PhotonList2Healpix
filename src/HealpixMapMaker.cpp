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

int HealpixMapMaker :: EvalCountsHealpix (string outfile, int healpix_order, string healpix_schema, EvtReader * evtReader, EvtParams* evtParams, const char *selectionFilename, double tmin, double tmax) { // const char *templateFilename,

	Healpix_Map<int> map;
	
	if(healpix_schema=="NEST")
	{
		map.Set(healpix_order, NEST);
	}
	else if(healpix_schema=="RING")
	{
		map.Set(healpix_order, RING);
	}

	for(int i = 0; i < map.Npix(); i++) map[i] = 0; // initializing with zeros
	int nside = pow(2,healpix_order);

	cout << "\n=> Creating Healpix map" << endl;
	cout << "* Resolution (k): " << healpix_order << endl;
	cout << "* Scheme: "<< healpix_schema << endl;
	cout << "* Nside: " << nside << endl;
	cout << "* Number of pixels: " << map.Npix() << endl;

  int hdutype = 0;
	int status = 0;



	fitsfile* selectionFits;

  if (fits_open_file(&selectionFits, selectionFilename, READONLY, &status))
	{
      cerr << "[HealpixMapMaker] ERROR opening selection file " << selectionFilename << endl;
      return status;
  }

	// int fits_movabs_hdu(fitsfile *fptr, int hdunum, int *hdutype, int *status) ==> Moves to the specified absolute HDU number in the FITS file.
	// In the case of the AGILE/CTA photon list we have 3 HDU (Primary, EVENTS and GTI). We take hdunum = 2 ==> EVENTS

	if (fits_movabs_hdu(selectionFits, 2, &hdutype, &status))
	{
		cerr << "[HealpixMapMaker] ERROR moving to HDU" << endl;
		return status;
	}


	cout << "Moved to hdutype " << hdutype << " of the selection file " << selectionFilename << endl;

  cout << "Evaluating counts.." << endl;



	long nrows;

	if (fits_get_num_rows(selectionFits, &nrows, &status)) {
		cerr << "[HealpixMapMaker] ERROR counting the number of rows from selection file "<< selectionFilename << endl;
		return status;
	}

	int raColumn, decColumn;
	if (fits_get_colnum(selectionFits, 1, (char*)"RA", &raColumn, &status)) // int fits_get_colnum(fitsfile *fptr, int casesen, char *template, int *colnum, int *status)
	{
		cerr << "[HealpixMapMaker] ERROR getting the index of the column RA" << endl;
		return status;
	}

	if (fits_get_colnum(selectionFits, 1, (char*)"DEC", &decColumn, &status)) // int fits_get_colnum(fitsfile *fptr, int casesen, char *template, int *colnum, int *status)
	{
		cerr << "[HealpixMapMaker] ERROR getting the index of the column DEC" << endl;
		return status;
	}


	#ifdef DEBUG
	cout <<"[HealpixMapMaker] Index of coloumn RA: " << raColumn << endl;
	cout <<"[HealpixMapMaker] Index of coloumn DEC: " << decColumn << endl;
	#endif

	double ra, dec, l, b = 0;	//the,, x, y, i, ii = 0

	for ( long k = 0; k<nrows; k++ ) {


				// int fits_read_col(fitsfile *fptr, int datatype, int colnum, long firstrow, long firstelem, long nelements, void *nulval, void *array, int *anynul, int *status)

				// Write or read elements in column number colnum, starting with row
				// firstsrow and element firstelem (if it is a vector column). firstelem
				// is ignored if it is a scalar column. The nelements number of elements
				// are read or written continuing on successive rows of the table if necessary.
				// array is the address of an array which either contains the values to be written,
				// or will hold the returned values that are read. When reading, array
				// must have been allocated large enough to hold all the returned values.
			  // nulval = NULL => no checks will be made for undefined values when reading the column.

			if (fits_read_col(selectionFits, TDOUBLE, raColumn, k+1, 1, 1, NULL, &ra, NULL, &status))
			{
				cerr << "[HealpixMapMaker] ERROR on reading the column RA of the template file" << endl;
				return status;
			}
			if (fits_read_col(selectionFits, TDOUBLE, decColumn, k+1, 1, 1, NULL, &dec, NULL, &status))
			{
				cerr << "[HealpixMapMaker] ERROR on reading the column DEC of the template file" << endl;
				return status;
			}

			Euler(ra, dec, &l, &b, 1);
			l *= DEG2RAD;
			b *= DEG2RAD;



			// Encodes an angular position on unitary sphere as colatitude and longitude
			pointing point = pointing((M_PI/2)-b,l);
			int index = map.ang2pix(point);

			// Increment the count
			map[index]++;

	}

	fits_close_file(selectionFits, &status);
	cout <<"SelectionFile" << selectionFilename <<  " closed." << endl;



	if( remove( outfile.c_str() ) == 0 )
		cout << "Deleted old file: " << outfile << endl;


	fitshandle handle;
	handle.create(outfile);

	write_Healpix_map_to_fits(handle, map, PLANCK_INT32);

	cout << "Map saved: " << outfile << endl;

  return status;
}
