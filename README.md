# PhotonList2Healpix v0.0.1

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/67a1b7d4dec34f42a8b0ce331d8e57c8)](https://app.codacy.com/app/GZHeisenberg/PhotonList2Healpix?utm_source=github.com&utm_medium=referral&utm_content=GZHeisenberg/PhotonList2Healpix&utm_campaign=Badge_Grade_Dashboard)

The PhotonList2Healpix software takes in input a photon list (CTA or AGILE) and returns as output an Healpix map with a given resolution ("order" or "k") and NEST pixelization scheme.

## Dependencies

The following dependencies are needed:

	* cfitsio-3.370
	* agile-B24-r5
	* healpix-3.31

## Usage

```bash
	module load agile-B24-r5
	module load healpix-3.31-cxx
	export PFILES=~/PhotonList2HealpixTask/PhotonList2Healpix/conf
```

### Input

	outfile: the filename of the output file.

	photon_list_type: the format of the photon list.

	photon_list_path: the path to the photon list.

	healpix_order: the resolution of the Healpix map.




	tmin: observation start time for the photons selection (AGILE and CTA).

	tmax: observation end time for the photons selection (AGILE and CTA).

	emin: the minimum energy of the events for the photons selection (AGILE and CTA).

	emax: the maximum energy of the events for the photons selection (AGILE and CTA).




	albrad: radius of earth albedo (expressed in degrees) for the photons selection (AGILE only).

	phasecode: orbital phase code for the photons selection (AGILE only).

	filtercode: code used to select the particular event type (5 to select only gamma events) for the photons selection (AGILE only).

	fovradmin: Min off-axis angle (expressed in degrees) for the photons selection (AGILE only).

	fovradmax: Max off-axis angle (expressed in degrees) for the photons selection (AGILE only).
