/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/


#ifndef EVTPARAMS_H
#define EVTPARAMS_H

//enum EVT_TYPE { AGILE, CTA };

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class EvtParams
{
	public:

	EvtParams(){}

};



class AgileEvtParams : public EvtParams
{

	public:
		const char * evtFilePath;
		double emin;
		double emax;
		double albrad;
		double fovradmin;
		double fovradmax;
		int phasecode;
		int filtercode;
		double tmin;
		double tmax;

	AgileEvtParams(const char * evtFP, double emi, double ema, double al, double fmin, double fmax, int pc, int fc, double tmi, double tma)
		: evtFilePath(evtFP), emin(emi), emax(ema), albrad(al), fovradmin(fmin), fovradmax(fmax), phasecode(pc), filtercode(fc), tmin(tmi), tmax(tma)
	{

	}

	//using EvtParams::print;
	void print()
	{
		cout << "\n[AgileEvtReaderParams]: \nevtFilePath: "<<evtFilePath<<"\nemin: "<<emin<<"\nemax: "<<emax<<"\nalbrad: "<<albrad<<"\nfovradmin: "<<fovradmin<<"\nfovradmax: "<<fovradmax<<"\nphasecode: "<<phasecode<<"\nfiltercode: "<<filtercode<<"\ntmin: "<<tmin<<"\ntmax: "<<tmax<<endl;
	}
};



class CtaEvtParams : public EvtParams
{

	public:
		const char * evtFilePath;
		double emin;
		double emax;
		double tmin;
		double tmax;

		CtaEvtParams(const char * evtFP, double emi, double ema, double tmi, double tma)
			: evtFilePath(evtFP), emin(emi), emax(ema), tmin(tmi), tmax(tma)
		{

		}


	void print()
	{
		cout << "\nCtaEvtReaderParams: \nevtFilePath: "<<evtFilePath<<"\nemin: "<<emin<<"\nemax: "<<emax <<"\ntmin: "<<tmin<<"\ntmax: "<<tmax<<endl;
	}
};

#endif
