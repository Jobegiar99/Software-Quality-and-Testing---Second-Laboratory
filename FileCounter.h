
#include "FileInformation.h"
//.b=12
#include <vector>
#include <iostream>
#include <ctype.h>
#include <string>


using namespace std;

class FileCounter{
    public: 
        FileCounter( vector<string> fileVectorRepresentation, string inputFileName ); //.m
        void lineCounter( FileInformation& fileInfo );
        

    private:
        vector<string> fileVectorRepresentation;
        void classifyFile( FileInformation& fileInformation ); //.m
        int items; //.m
        int base; //.m
        int deleted; //.m
        int modified; //.m
        int codeLines; //called T but in this file the name will be codeLines
        string inputFileName;
};

//.i
FileCounter::FileCounter( vector<string> fileVectorRepresentation, string inputFileName){

    this -> fileVectorRepresentation = fileVectorRepresentation;

    this -> items = 0; //.m

    this -> base = 0; //.m
    
    this -> modified = 0; //.m

    this -> codeLines = 0;

    this -> deleted = 0;

    this -> inputFileName = inputFileName;

}

//.i
void FileCounter::lineCounter(FileInformation& fileInformation){

    /*
        Esta funcion itera sobre el vector para identificar a que categoría corresponde
        cada una de las líneas del archivo (si es que corresponde a alguna categoría)
    */
   
    bool multiLineComment = false;

    for(int index = 0 ; index < this -> fileVectorRepresentation.size() ; index++ ){

        string currentLine = this -> fileVectorRepresentation[ index ];

        int commentIndex = currentLine.size();
        bool checkIfIsCode = false;

        if ( currentLine.find("//.i") != string::npos ){ //.m
            this -> items++; //.m

        }else if ( currentLine.find("//.b=") != string::npos){ //.m{
            //.d=1
            int index = currentLine.find("//.b=") + 5;
            string lineAmount = "";

            while(  index < currentLine.size() && currentLine[index] >= '0' && currentLine[index] <= '9' ){

                lineAmount += currentLine[index];
                index += 1;
                
            }
            for(int i =0; i < lineAmount.size();i++){
                if(! isdigit(lineAmount[i]))
                    continue;
            }
            this -> base += stoi(lineAmount);
            

        }else if( currentLine.find("//.d=") != string::npos){ //.m
            //.d=2
            int index = currentLine.find("//.d=") + 5;
            string lineAmount = "";

            while(  index < currentLine.size() && currentLine[index] >= '0' && currentLine[index] <= '9' ){

                lineAmount += currentLine[index];
                index += 1;
                
            }
            for(int i =0; i < lineAmount.size();i++){
                if(! isdigit(lineAmount[i]))
                    continue;
            }
            this -> deleted += stoi(lineAmount);

        //.d=3
        } else if ( currentLine.size() > 0){ //.m

            checkIfIsCode = true; //.m
            //.d=1
            

        }
        //.d=2

        if(checkIfIsCode){ //.m

            bool isValid = false;

            if( currentLine.find("//") != string::npos){
                commentIndex = currentLine.find("//");

            }else if ( currentLine.find("/*") != string::npos){
                multiLineComment = true;
            }
            
       
            if ( !multiLineComment && currentLine.size() > 2 && currentLine.substr(commentIndex).find("//.m") != string::npos){//.m
                
                string lineInfo = currentLine.substr(commentIndex);
                int tagIndex = lineInfo.find("//.m");
                if( lineInfo.substr(0,tagIndex).find("\"") == string::npos && lineInfo.substr(tagIndex).find("\"") == string::npos){
                    this -> modified ++; 
                }

            }

            
            if(!multiLineComment){
                for( int charIndex = 0; charIndex < commentIndex; charIndex++ ){

                    if( !isspace( currentLine[ charIndex ] ) && currentLine[ charIndex ] != '}' && currentLine[ charIndex ] != '{' && currentLine[ charIndex ] != ';'){
                        isValid = true;
                    }


                }

                if( isValid ){ //.m
                    this -> codeLines++;
                    
                }//.d=2
            }

            if( multiLineComment ){
                if( currentLine.find("*/") != string::npos){
                    multiLineComment = false;
                }

                
            }
        }

    }

    classifyFile(fileInformation);
}

void FileCounter::classifyFile( FileInformation& fileInfo ){
    /*
        Esta funcion se encarga de identificar en que categoria se encuentra
        el archivo en case de no haber algun error.
        Luego crea el elemento en el mapa de fileInfo o aumenta en valor de sus atributos
        si el archivo estaba separado en varios.
    */

    string type = "";
    int typeIndex = -1;
    int newLines = this->codeLines - this->base + this->deleted;
    string fileToAdd = this->inputFileName.substr(0,this->inputFileName.find(".")); //.m
    //.d=12

    if( fileInfo.fileCategories.find(fileToAdd) 
                            == 
        fileInfo.fileCategories.end()
      ){
       fileInfo.fileCategories[fileToAdd] = FileInfoHolder(this->deleted, 
                                                                this->modified, 
                                                                this->items, 
                                                                this->base,
                                                                this->codeLines,
                                                                newLines
                                                            );
    }else{

        fileInfo.fileCategories[fileToAdd].deleted += this -> deleted;
        fileInfo.fileCategories[fileToAdd].modified += this -> modified;
        fileInfo.fileCategories[fileToAdd].items += this -> items;
        fileInfo.fileCategories[fileToAdd].base += this -> base;
        fileInfo.fileCategories[fileToAdd].T += this -> codeLines;
        fileInfo.fileCategories[fileToAdd].A += newLines;

    }


}

//.d=8