
#include "ResultFormatter.h"
//.b=7
#include <iostream>
#include "FileCounter.h"
#include "FileReader.h"
#include <locale>


using namespace std;


int main(){

    setlocale(LC_ALL, "es_ES");
   

    int fileAmount;
    FileInformation fileInfo;

    cout<< "Ingrese la cantidad de archivos que se van a leer"<<endl;
    cin>> fileAmount;
    cin.ignore();
    string inputFileName;
    while ( fileAmount > 0 ){
    
        //.b=11
        fileAmount --;
        cout<<" Ingrese el nombre del archivo junto a su extension" <<endl;
        getline( cin, inputFileName );

        FileReader fileReader( inputFileName );

        if( ! fileReader.fileReaderStream.is_open() ){

            continue; //.m

        } else {

            vector<string> fileVectorRepresentation = fileReader.fileToVector();

            if( fileVectorRepresentation.size() == 0 || ( fileVectorRepresentation.size() == 1 && fileVectorRepresentation[0].size() == 0)){
                
                continue; //.m

            } else {

                FileCounter fileCounter( fileVectorRepresentation, inputFileName ); //.m

                fileCounter.lineCounter(fileInfo);//.m

                //.d=1

            }
        }
    }

    ResultFormatter resultFormatter(fileInfo);
    getline(cin,inputFileName);
    return 0;
}