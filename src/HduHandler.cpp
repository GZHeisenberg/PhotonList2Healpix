/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#include "HduHandler.hpp"

HduHandler::HduHandler() {
  // constructor
}


int HduHandler::readHdu(string evtPath){

  int hdutype = 0;
	int status = 0;
	int keysexist=0;
	int morekeys =0;
  int hdunum = 0;

  fitsfile* fitsptr;

  #ifdef DEBUG
	cout << "\n[HduHandler] File path: " << evtPath <<"\n\n"<< endl;
  #endif

  if (fits_open_file(&fitsptr, evtPath.c_str(), READONLY, &status))
	{
      cerr << "[HduHandler] ERROR opening selection file " << evtPath << endl;
      return status;
  }

  if (fits_get_num_hdus(fitsptr, &hdutype, &status)) {
		cerr << "[HduHandler] ERROR reading number of file hdu " << fitsptr << endl;
    return status;
	}

	cout << "[HduHandler] This file contains " << hdutype << " hdu" << endl;

  for (int i = 0; i < hdutype; i++){

    #ifdef DEBUG
    cout << "[HduHandler] i value of loop: " << i << endl;
    cout << "[HduHandler] hdutype value: " << hdutype << endl;
    #endif

    if (fits_movabs_hdu(fitsptr, i+1, &hdunum, &status))
  	{
  		cerr << "[HduHandler] ERROR moving to HDU" << endl;
  		return status;
  	}
    #ifdef DEBUG
  	cout << "\n\n[HduHandler] Moved to hdutype " << i+1 << " of the selection file " << endl;
    #endif

    if(fits_get_hdrspace(fitsptr, &keysexist, &morekeys, &status))
    {
    	cerr << "[HduHandler] ERROR getting number of the exiting keywords" << endl;
    }

    #ifdef DEBUG
    cout << "[HduHandler] In the " << i+1 << " header are present " << keysexist << " keywords" << endl;
    #endif

    readHduKeysValue(fitsptr, keysexist);

  }


  if (fits_close_file(fitsptr, &status)) {
    cerr << "[HduHandler] ERROR closing file!" << endl;
  }

  return status;

}


int HduHandler::readHduKeysValue(fitsfile* fitsptr, int keysexist){

  int status = 0;
  char record[1024];

  cout << "\n" << endl;

    for(int j = 1; j <= keysexist; j++ ) {

      #ifdef DEBUG
      cout << "keyword number: " << j << endl;
      #endif

      if (fits_read_record(fitsptr, j, record, &status)) {
        cerr << "[HduHandler] ERROR reading key value record" << endl;
        return status;
      }

      cout << record << endl;

    }

    return status;

}

int HduHandler::writeKeysValue(string evtPath, int hdutype, char * keyname, char * value, char *comment){

  int status = 0;
  int hdunum = 0;

  fitsfile* fitsptr;

  #ifdef DEBUG
  cout <<"The keyword value is: " << value << endl;
  #endif

  if (fits_open_file(&fitsptr, evtPath.c_str(), READWRITE, &status))
	{
      cerr << "[HduHandler] ERROR opening selection file " << evtPath << endl;
      return status;
  }

  if (fits_movabs_hdu(fitsptr, hdutype, &hdunum, &status))
  {
    cerr << "[HduHandler] ERROR moving to HDU" << endl;
    return status;
  }
  #ifdef DEBUG
  cout << "\n\n[HduHandler] Moved to hdutype " << hdutype << " of the selection file " << endl;
  #endif

  if (fits_write_key(fitsptr, TSTRING, keyname, value, comment, &status))
  {
    cerr << "[HduHandler] ERROR writing new key!" << endl;
    return status;
  }

  if (fits_close_file(fitsptr, &status)) {
    cerr << "[HduHandler] ERROR closing file!" << endl;
  }

  return status;


}



int HduHandler::updateKeysValue(string evtPath, int hdutype, char * keyname, char * value, char *comment){

  int status = 0;
  int hdunum = 0;

  fitsfile* fitsptr;

  #ifdef DEBUG
  cout <<"The keyword value is: " << value << endl;
  #endif

  if (fits_open_file(&fitsptr, evtPath.c_str(), READWRITE, &status))
	{
      cerr << "[HduHandler] ERROR opening selection file " << evtPath << endl;
      return status;
  }

  if (fits_movabs_hdu(fitsptr, hdutype, &hdunum, &status))
  {
    cerr << "[HduHandler] ERROR moving to HDU" << endl;
    return status;
  }
  #ifdef DEBUG
  cout << "\n\n[HduHandler] Moved to hdutype " << hdutype << " of the selection file " << endl;
  #endif

  if (fits_update_key(fitsptr, TSTRING, keyname, value, comment, &status))
  {
    cerr << "[HduHandler] ERROR updating new key!" << endl;
    return status;
  }

  if (fits_close_file(fitsptr, &status)) {
    cerr << "[HduHandler] ERROR closing file!" << endl;
  }

  return status;


}
