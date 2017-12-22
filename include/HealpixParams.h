 /*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/


#ifndef HEALPIXPARAMS_H
#define HEALPIXPARAMS_H    

#include <iostream>

using std::cout;
using std::endl;

class HealpixParams
{
	public:
		double mdim;
		double mres;
		double laa;
		double baa;
		double lonpole;
		
		
	HealpixParams(double md, double mr, double la, double ba, double ln ) 
		: mdim(md), mres(mr), laa(la), baa(ba), lonpole(ln)
	{
	
	}

	void print()
	{
		cout << "\nHealpixParams: \nmdim: "<<mdim<<"\nmres: "<<mres<<"\nla: "<<laa<< "\nba: "<<baa<<"\nlonpole: "<<lonpole<<endl;
	}

		
};
#endif
