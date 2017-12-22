# PhotonList2Healpix v0.0.1

Il software genera una mappa Healpix partendo da una photons list che può provenire da contesti scientifici diversi. Le photons list attualmente supportate sono quelle generate da AGILE o CTA.

Affinchè il software funzioni correttamente necessità di un file di configurazione EVT.index. Questo file al momento viene generato in run-time tramite i seguenti parametri presi in input:

	- photonListPath ( "./EVT_MAPS/ag1608151200_1608311200_STD1Kal_FM.EVT.gz" )
	
	- tmin ( 398347132 )
	
	- tmax ( 399729532 )


### Input:

	outfile: nome che sarà associato alla mappa healpix generata del software (la mappa sarà salvata all'interno della directory HEALPIX_MAPS)
	
	evtType: indica la provenienza della photon list (AGILE o CTA)
	
	photonListPath: indica il path della photon list di partenza
	
	mdim: indica la dimensione della mappa healpix che sarà creata (espressa in gradi)
	
	mres: indica la risoluzione della pixelizzazione healpix
	
	la: indica la longitudine del centro della mappa healpix
	
	ba: indica la latitudine del centro della mappa healpix
	
	lonpole: indica la rotazine della mappa healpix (espressa in gradi)
	
	albrad: radius of earth albedo (degrees)
	
	phasecode: orbital phase code
	
	filtercode: rappresenta un codice di filtraggio dei fenomeni all'interno delle photon list (0 per photon list CTA, 5 per photon list AGILE per seleziore i soli eventi gamma)
	
	tmin: tempo iniziale degli eventi da osservare ( parametro di selezione degli eventi dalla photon list)
	
	tmax: tempo finale degli eventi da osservare ( parametro di selezione degli eventi dalla photon list)
	
	emin: energia minima degli eventi da osservare ( parametro di selezione degli eventi dalla photon list)
	
	emax: energia massima degli eventi da osservare ( parametro di selezione degli eventi dalla photon list)
	
	fovradmin: Min off-axis angle (degrees)
	
	fovradmax: Max off-axis angle (degrees)
	
	emax: energia massima di osservazione