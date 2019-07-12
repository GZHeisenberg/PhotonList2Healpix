#!/bin/sh

module load agile-B24-r5
module load healpix-3.31

export PFILES=conf/

./bin/PhotonList2Healpix agile_counts_to_healpix ph_2_heal_out AGILE ag1608151200_1608311200_STD1Kal_FM.EVT.gz 8 0 399729532 0 500000000 80 6 5 0 60 


#./bin/PhotonList2Healpix ag_healpix ph_2_heal_out CTA cta_events.fits 8 0 5000000000 0 500000000
