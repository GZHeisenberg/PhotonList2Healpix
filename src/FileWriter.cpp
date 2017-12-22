/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino,
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/


#include "FileWriter.h"

FileWriter::FileWriter()
{
    //ctor
}


void FileWriter::write2File(string outputFileName,string input){
	ofstream resultOfAnalysis;

	resultOfAnalysis.open(outputFileName, std::ofstream::trunc);

	if(resultOfAnalysis.is_open()){
		resultOfAnalysis << input;
		resultOfAnalysis.close();
	}else{
		printf("Cant open header file ");
	}
}

void FileWriter::write2FileAppend(string outputFileName,string input){
	ofstream resultOfAnalysis;

	resultOfAnalysis.open(outputFileName, std::ofstream::app);

	if(resultOfAnalysis.is_open()){
		resultOfAnalysis << input;
		resultOfAnalysis.close();
	}else{
		printf("Cant open header file ");
	}
}
/*
void FileWriter::write2FileHeader(string input, string observationDate, string outputFile,float classificationThreshold) {
    ofstream resultOfAnalysis;


    //time_t rawtime;
    //struct tm * timeinfo;
    //char date[80];

    //time (&rawtime);
    //timeinfo = localtime(&rawtime);

  //  strftime(date,sizeof(date),"%d-%m-%Y %I:%M:%S",timeinfo);
  //  std::string str(date);

    string outputText = outputFile+".txt";
    resultOfAnalysis.open (outputText, std::ofstream::out | std::fstream::app);
    if(resultOfAnalysis.is_open()){
        resultOfAnalysis << "\n------------------------------------------------------\n";
        resultOfAnalysis << "DETECTION OF: " << input << " -OBSD: "<<observationDate<< " -T: "<<classificationThreshold*100<<"\n";
        resultOfAnalysis.close();
    }else{
        printf("Cant open header file ");

    }

}


void FileWriter::write2FileBody(string input, string outputFile) {
    ofstream resultOfAnalysis;
    string outputText = outputFile+".txt";

    resultOfAnalysis.open (outputText, std::ofstream::out | std::fstream::app);
    if(resultOfAnalysis.is_open()){
        resultOfAnalysis << "\n" + input;
        resultOfAnalysis.close();
    }else{
        printf("Cant open body file ");

    }

}

void FileWriter::write2SourceFile(string pathToFile, string input){
    ofstream resultOfAnalysisSources;

    string outputTextSource = "LOG_sources.txt";

    resultOfAnalysisSources.open (outputTextSource, std::ofstream::out | std::fstream::app);
    if(resultOfAnalysisSources.is_open()){
        resultOfAnalysisSources << "\n"+ pathToFile +", "+input;
        resultOfAnalysisSources.close();
    }else{
        printf("Cant open sources file ");
    }


}*/


