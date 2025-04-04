#include "Mymap.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
using namespace std;

void chemformula(StringMap *map, const char *formula, int coef=1){
    int i=0;
    while(formula[i]!='\0'){
        if(formula[i]=='('){//當函式中出現(
            int depth=1;
            int start=i+1;
            i++;
            while(depth>0){
                if(formula[i]=='(')depth++;
                if(formula[i]==')')depth--;
                i++;
            }

            //子字串
            int len=i-start-1;
            char* subformula= new char[len+1];
            strncpy(subformula,formula+start,len);
            subformula[len]='\0';//將最後一個設為null判斷子字串已經結束

            int multipiler=1;
            while(isdigit(formula[i])){
                multipiler=0;
                multipiler=multipiler*10+(formula[i]-'0');
                i++;
            }

            chemformula(map, subformula, coef * multipiler);
            delete[] subformula;
        }
        else if(isupper(formula[i])){//為大寫元素的話，後面可能會有小寫符號跟隨且至多兩個(包含大寫)
            char element[3]={0};
            element[0]=formula[i++];
            if(islower(formula[i])){
                element[1]=formula[i++];

            }

            int count=1;
            if(isdigit(formula[i])){
                count=0;
                while(isdigit(formula[i])){
                    count=count*10+(formula[i++]-'0');//數字轉成int
                }
            }

            int* answer=find(map,element);
            if(answer){
                *answer+=count*coef;
            }else{
                insert(map,element,count*coef);
            }
        }else{
            i++;
        }

        
    }
}


void outputMap(StringMap* map, ofstream& outFile) {//輸出文件
    for (int i = 0; i < map->size; i++) {
        outFile << map->data[i].key;
        if (map->data[i].value > 1) {
            outFile << map->data[i].value;
        }
    }
    outFile << endl;
}

void process_formula(const char *formula, char *result){

}
int main(){
    ifstream inFile("testcase1.txt");
    ofstream outFile("output1.txt");
    string line;
    while (getline(inFile, line)) {
        StringMap atomMap;
        init_map(&atomMap);
        chemformula(&atomMap, line.c_str());
        outputMap(&atomMap, outFile);
    }
    
    inFile.close();
    outFile.close();
    return 0;
}