#!/bin/sh

module load agile-B24-r5
module load ../healpix-3.31-cxx

export PFILES=conf/

./bin/PhotonList2Healpix agile_counts_to_healpix AGILE /home/zollino/PhotonList2HealpixTask/PhotonList2Healpix/INDEX/ag1608151200_1608311200_STD1Kal_FM.EVT.gz 8 398347132 399729532 0 500000000 80 6 5 0 60 


#./bin/PhotonList2Healpix cta_counts_to_healpix CTA /home/zollino/ctoolGeneratedFile/photonlist/events.fits 8 0 5000000000 0 500000000
