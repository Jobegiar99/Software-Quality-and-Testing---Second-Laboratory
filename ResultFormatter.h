#include "FileInformation.h"
#include "iostream"
#include <fstream>
#include <string>

using namespace std;

class ResultFormatter{
    public:
        ResultFormatter(FileInformation& fileInfo);

    private:
        void scanCategories(FileInformation& fileInfo);

};

//.i
ResultFormatter::ResultFormatter(FileInformation& fileInfo){
    scanCategories(fileInfo);
}

//.i
void ResultFormatter::scanCategories(FileInformation& fileInfo){
    /*
        Esta funcion se encarga de clasificar las clases y de crear el output
    */
    ofstream outputFile ("ConteoLDC.txt");
    vector<string> linesForFile;
    int LDC = 0;

    vector<pair<string,FileInfoHolder>> BASE;
    vector<pair<string,FileInfoHolder>> NUEVA;
    vector<pair<string,FileInfoHolder>> REUSADA;

    for(unordered_map<string,FileInfoHolder>::iterator it=fileInfo.fileCategories.begin(); it!=fileInfo.fileCategories.end(); ++it){
        
        LDC += it->second.T;

        int typeIndex;
        if( it->second.base > 0 ){
            if( it->second.modified > 0 || it->second.deleted > 0 || it->second.A > 0 ){
                //BASE
                typeIndex = 0;
            }else{
                //REUSADA
                typeIndex = 2;
            }
        }else if ( it->second.base == 0 && it->second.modified == 0 && it->second.deleted == 0 && it->second.A > 0){
            //NUEVA
            typeIndex = 1;
        }else{
            continue;
        }


        switch(typeIndex){
            case 0:
                BASE.push_back(pair<string,FileInfoHolder>(it->first,it->second));
                break;
            
            case 1:
                NUEVA.push_back(pair<string,FileInfoHolder>(it->first,it->second));
                break;
            
            case 2:
                REUSADA.push_back(pair<string,FileInfoHolder>(it->first,it->second));
                break;

        }
    }

    linesForFile.push_back("CLASES BASE:\n");
    cout<<"CLASES BASE:"<<endl;
    
    for(int i = 0; i < BASE.size();i++){
        string line = 
                "   " + BASE[i].first + ": T=" + to_string(BASE[i].second.T) + 
                ", I=" + to_string(BASE[i].second.items) + 
                " , B=" + to_string(BASE[i].second.base) + 
                ", D=" + to_string(BASE[i].second.deleted) + 
                ", M=" + to_string(BASE[i].second.modified) + 
                ", A=" + to_string(BASE[i].second.A) + "\n";

        
        cout << line;
        linesForFile.push_back(line);
    }
    cout<<"--------------------------------------------"<<endl;
    linesForFile.push_back("--------------------------------------------\n");
    linesForFile.push_back("CLASES NUEVAS:\n");
    cout<<"CLASES NUEVAS:"<<endl;
    
    for(int i = 0; i < NUEVA.size();i++){
        string line = 
                "   " + NUEVA[i].first + ": T=" + to_string(NUEVA[i].second.T) + 
                ", I=" + to_string(NUEVA[i].second.items) + "\n";

        cout << line;
        linesForFile.push_back(line);
    }

    cout<<"--------------------------------------------"<<endl;
    linesForFile.push_back("--------------------------------------------\n");
    linesForFile.push_back("CLASES REUSADAS:\n");
    cout<<"CLASES REUSADAS:"<<endl;
    
    for(int i = 0; i < REUSADA.size();i++){
        string line = 
                "   " + REUSADA[i].first + ": T=" + to_string(REUSADA[i].second.T) + 
                ", I=" + to_string(REUSADA[i].second.items) + 
                " , B=" + to_string(REUSADA[i].second.base) + "\n";

        cout << line;
        linesForFile.push_back(line);
    }
    cout<<"--------------------------------------------"<<endl;
    linesForFile.push_back("--------------------------------------------\n");
    linesForFile.push_back("Total de LDC=" + to_string( LDC ) + "\n");
    cout<<"Total de LDC=" + to_string( LDC )<<endl;

    for(int index = 0 ; index < linesForFile.size(); index++){
        outputFile << linesForFile[index];
    }
    

}
