# PhotonList2Healpix v0.0.1

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/67a1b7d4dec34f42a8b0ce331d8e57c8)](https://app.codacy.com/app/GZHeisenberg/PhotonList2Healpix?utm_source=github.com&utm_medium=referral&utm_content=GZHeisenberg/PhotonList2Healpix&utm_campaign=Badge_Grade_Dashboard)

The PhotonList2Healpix software takes in input a photon list (CTA or AGILE) and return as output an Healpix map.

The software requires a configuration file named EVT.index placed in INDEX directory.
This file is created at run-time using following input parameters:

	- photonListPath ( "./EVT_MAPS/ag1608151200_1608311200_STD1Kal_FM.EVT.gz" )

	- tmin ( 398347132 )

	- tmax ( 399729532 )

## Dependencies

The following dependencies are needed:

	* cfitsio
	* pil
	* agile
	* healpix-3.31-cxx

## Use

On inaf server load the following modues:

	module load agile-B24-r5
	module load healpix-3.31-cxx

Export path to pil params file configuration

```bash
	 export PFILES=~/PhotonList2HealpixTask/PhotonList2Healpix/conf
```

### Input

	outfile: HEALPix output file name;

	evtType: indicates if the input photon list is AGILE or CTA;

	photonListPath: indicates the input photon list path;

	mdim: indicates the HEALPix output map size (expressed in degrees);

	mres: indicates the HEALPix output map resolution;

	la: indicates the longitudinal coordinate of the center of the HEALPix output map;

	ba: indicates the latitude coordinate of the center of the HEALPix output map;

	lonpole: indicates the rotation of the HEALPix map (expressed in degrees);

	albrad: radius of earth albedo (expressed in degrees);

	phasecode: orbital phase code;

	filtercode: code used to select the particular event type ( 0 to select all photon list event, used for CTA photon list, 5 to select only gamma event, used for AGILE photon list);

	tmin: observation start time ( selection parameter to apply at the photon list );

	tmax: observation end time ( selection parameter to apply at the photon list );

	emin: the minimum observation energy of the events ( selection parameter to apply at the photon list );

	emax: the maximum observation energy of the events ( selection parameter to apply at the photon list );

	fovradmin: Min off-axis angle ( expressed in degrees);

	fovradmax: Max off-axis angle (expressed in degrees);
