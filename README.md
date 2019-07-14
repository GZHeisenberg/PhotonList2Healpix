# PhotonList2Healpix v0.0.2

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/67a1b7d4dec34f42a8b0ce331d8e57c8)](https://app.codacy.com/app/GZHeisenberg/PhotonList2Healpix?utm_source=github.com&utm_medium=referral&utm_content=GZHeisenberg/PhotonList2Healpix&utm_campaign=Badge_Grade_Dashboard)

The PhotonList2Healpix software takes in input a photon list (CTA or AGILE) and returns as output an Healpix map with a given resolution ("order" or "k") and NEST or RING pixelization scheme.

## Dependencies

The following dependencies are needed:
* cfitsio-3.370
* agile-B24-r5
* healpix-3.50

## Usage

```bash
cd PhotonList2Healpix/
module load agile-B24-r5
module load healpix-3.50
export PFILES=~/PhotonList2HealpixTask/PhotonList2Healpix/conf

./bin/PhotonList2Healpix agile_counts_to_healpix AGILE ag1608151200_1608311200_STD1Kal_FM.EVT.gz 7 NEST
```

### Input

	outfile: the filename of the output file. [required]

	outfolder: the folder name for the output file. [required]

	photon_list_type: the format of the photon list. [required]

	photon_list_path: the path to the photon list. [required]

	healpix_order: the resolution of the Healpix map. [required]

	healpix_schema: the schema of the Healpix map. [required]


	tmin: observation start time for the photons selection (AGILE and CTA). [default =  0]

	tmax: observation end time for the photons selection (AGILE and CTA). [default =  399729532]

	emin: the minimum energy of the events for the photons selection (AGILE and CTA). [default = 0]

	emax: the maximum energy of the events for the photons selection (AGILE and CTA). [default = 500000000]


	albrad: radius of earth albedo (expressed in degrees) for the photons selection (AGILE only). [default = 80]

	phasecode: orbital phase code for the photons selection (AGILE only). [default = 6]

	filtercode: code used to select the particular event type (5 to select only gamma events) for the photons selection (AGILE only). [default = 5]

	fovradmin: Min off-axis angle (expressed in degrees) for the photons selection (AGILE only). [default = 0]

	fovradmax: Max off-axis angle (expressed in degrees) for the photons selection (AGILE only). [default = 60]



### How the qeury string is formed

```
str << "TIME >= " << tmin;
str << "TIME < " << tmax;
str << " && ENERGY >= " << emin;
str << " && ENERGY <= " << emax;
str << " && PH_EARTH > " << albrad;
str << " && THETA < " << fovradmax;
str << " && THETA >= " << fovradmin;
if ((phasecode & 1) == 1)
		str << " && PHASE .NE. 0";
if ((phasecode & 2) == 2)
		str << " && PHASE .NE. 1";
if ((phasecode & 4) == 4)
		str << " && PHASE .NE. 2";
if ((phasecode & 8) == 8)
		str << " && PHASE .NE. 3";
if ((phasecode & 16) == 16)
		str << " && PHASE .NE. 4";
if ((filtercode & 1) == 1)
		str << " && EVSTATUS .NE. 'L'";
if ((filtercode & 2) == 2)
		str << " && EVSTATUS .NE. 'G'";
if ((filtercode & 4) == 4)
		str << " && EVSTATUS .NE. 'S'";
```

Example:
```
TIME >= 0.000000 && TIME < 9999999999.000000 && ENERGY >= 0 && ENERGY <= 1e+10 && PH_EARTH > 80 && THETA < 60 && THETA >= 0 && PHASE .NE. 1 && PHASE .NE. 2 && EVSTATUS .NE. 'L' && EVSTATUS .NE. 'S'
```
