//.b=22
#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class FileReader{
    public:
        FileReader( string inputFileName);
        vector<string> fileToVector();
        fstream fileReaderStream;
    
    private:
        string inputFileName;
};
//.i
FileReader::FileReader( string inputFileName){
    this -> fileReaderStream.open( inputFileName );
    this -> inputFileName = inputFileName;
}
//.i
vector<string> FileReader::fileToVector(){
    /*
        Esta funcion lee el archivo y hace que cada
        linea sea guardada en un vector de strings.
    */
    vector<string> fileLines;
    string fileLine;
    
    while( ! this->fileReaderStream.eof()){
        getline( this -> fileReaderStream, fileLine);

        fileLines.push_back( fileLine );

    }
    
    return fileLines;
}