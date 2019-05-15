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

int HealpixMapMaker :: EvalCountsHealpix (const char * outfile, EvtReader * evtReader, EvtParams* evtParams, HealpixParams healpix2WriteParams, const char *selectionFilename, double tmin, double tmax) { // const char *templateFilename,

	cout << "Healpix Map Maker" << endl;

	// ATTUALMENTE NON USATO!!!!!!!
	long mxdim = long(healpix2WriteParams.mdim / healpix2WriteParams.mres + 0.1); // dimension (in pixels) of the map

	cout << "Dimension map: " << mxdim << " pixel" << endl;
  cout << "mdim: " << healpix2WriteParams.mdim << " (degree)" << endl;
	cout << "mres: " << healpix2WriteParams.mres << endl;

  int hdutype = 0;
	int status = 0;


	fitsfile* selectionFits;

	cout << "\n[HealpixMapMaker] selectionFilename: " << selectionFilename <<"\n\n"<< endl;
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
	cout << "[HealpixMapMaker] Moved to hdutype " << hdutype << " of the selection file " << selectionFilename << endl;

  cout << "[HealpixMapMaker] Evaluating counts.." << endl;


	// mres is the resolution level and NEST is chosen for seek of efficency
  Healpix_Map<int> map((int)healpix2WriteParams.mres,NEST);

	//initialize the healpix map to all zeros
	cout << "Real number of map pixel: " << map.Npix() << endl;
 	for( int i = 0; i < map.Npix(); i++)
	{
		map[i]=0;
	}

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

	// This represent the coordinates of map center but at the moment are not used!
	// double baa = healpix2WriteParams.baa * DEG2RAD;
	// double laa = healpix2WriteParams.laa * DEG2RAD;

	cout << "The center of map coordinates should be: " << healpix2WriteParams.baa << ", " << healpix2WriteParams.laa << endl;

	for ( long k = 0; k<nrows; k++ ) {

			/*
				int fits_read_col(fitsfile *fptr, int datatype, int colnum, long firstrow, long firstelem, long nelements, void *nulval, void *array, int *anynul, int *status)

				Write or read elements in column number colnum, starting with row
				firstsrow and element firstelem (if it is a vector column). firstelem
				is ignored if it is a scalar column. The nelements number of elements
				are read or written continuing on successive rows of the table if necessary.
				array is the address of an array which either contains the values to be written,
				or will hold the returned values that are read. When reading, array
				must have been allocated large enough to hold all the returned values.
				// nulval = NULL => no checks will be made for undefined values when reading the column.
			*/
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

  cout << "[HealpixMapMaker] Ending Healpix evaluation. Writing the Healpix map on file." << endl;

	const char *_outfile = outfile;
	string OutFilePath(_outfile);
	OutFilePath = "./" + OutFilePath;

	if( remove( OutFilePath.c_str() ) != 0 )
		cout << "[HealpixMapMaker] Error deleting the file" << OutFilePath << endl;
	else
		cout << "[HealpixMapMaker] " << OutFilePath << " removed." << endl;


	fitshandle handle;
	handle.create(OutFilePath);

	write_Healpix_map_to_fits(handle,map,PLANCK_INT64);



	cout << "[HealpixMapMaker] Map saved." << endl;

	fits_close_file(selectionFits, &status);


	cout <<"[HealpixMapMaker] SelectionFile" << selectionFilename <<  " closed." << endl; //" and templateFile " <<templateFilename <<

  return status;
}
