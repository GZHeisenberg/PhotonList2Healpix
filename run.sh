#!/bin/sh

module load agile-B24-r5
module load healpix-3.50

export PFILES=conf/

# ./bin/PhotonList2Healpix agile_counts_to_healpix ph_2_heal_out AGILE ag1608151200_1608311200_STD1Kal_FM.EVT.gz 8 0 399729532 0 500000000 80 6 5 0 60
./bin/PhotonList2Healpix healpix_map output_folder AGILE /home/rt/baroncelli.leonardo/PhotonList2Healpix/ag1608151200_1608311200_STD1Kal_FM.EVT.gz 7 NEST 398347132.00498199 399728783.99772602 4 49148 80 6 5 0 60 

# ./bin/PhotonList2Healpix HealpixMap ph_to_healpix_out CTA /home/zollino/ctoolGeneratedFile/photonlist/events.fits 7 NEST 0 5000000000 0 500000000
#./bin/PhotonList2Healpix ag_healpix ph_2_heal_out CTA cta_events.fits 8 0 5000000000 0 500000000
