#!/bin/sh

module load agile-B24-r5
module load healpix-3.50

export PFILES=conf/

#Photon list GRB
./bin/PhotonList2Healpix healpix_map output_folder/ CTA ./INDEX/EVT.index 7 NEST -1 -1 -1 -1
