

//  main.cpp
//  Code Challenge
//
//  Created by Lily Li on 2018/11/2.
//  Copyright © 2018 Lily Li. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <iomanip>
using namespace std;

int findMin(int a,int b){
    if(a > b)
       return b;
    return a;
}


double Round(float num){
    float rem = num*10 - int(num*10);
    int intPart = int(num*10);
    if(rem >= 0.5){
        intPart += 1;
    }
    double res = intPart/10.0;
    return res;
}

bool isSTATUS(string s){
    if(s.find("STATUS") != string::npos)
        return true;
    return false;
}

bool isSOC(string s){
    if(s.find("SOC_NAME") != string::npos)
        return true;
    return false;
}

bool isWorkSite(string s){
    if(s.find("WORKSITE_STATE") != string::npos)
        return true;
    else if(s.find("WORKLOC1_STATE") != string::npos)
        return true;
    return false;
}

typedef pair<string, int> PAIR;
int cmp(const PAIR& x, const PAIR& y){
    return x.second > y.second;
}

int main() {
//     string F = "H1B_FY_2014.csv";//455144 /519503
//     string F = "H1B_FY_2015.csv";//547278 /618803
//     string F = "H1B_FT_2016.csv";//569646 /647851
       string F = "H1b_input.csv";
    
    string fileName = F;
    std::ifstream file("../input/" + fileName);
    std::ofstream occup,place;
    string piece;
    int certPos = 0;
    int SocPos = 0;
    int statePos = 0;
    occup.open("../output/top_10_occupations.txt");
    place.open("../output/top_10_states.txt");
    map<string,int> occMp;
    map<string,int> staMp;
    map<int,string> finalOcc;
    map<int,string> finalSta;
    if(!file.is_open()){
        cout << "Can't open the file." << endl;
    }
    
    if(file.good()){
        int i = 0;
        while(i < 100 ){
            getline(file, piece, ';');
            i++;
            if(isSTATUS(piece)){
                certPos = i;
            }
            if(isSOC(piece)){
                SocPos = i;
            }
            if(isWorkSite(piece)){
                statePos = i;
		cout << "statePos is: " << statePos << endl;
            }
        }
    }
    
    float cc = 0;
    while(file.good()){
        int i = 0;
        while(i < certPos){
            getline(file, piece, ';');
            i++;
        }
        if(piece == "CERTIFIED"){
            cc++;
            while(i < SocPos){
                 getline(file, piece, ';');
                 i++;
            }
            if(!piece.empty())
                occMp[piece]++;
            
            while(i < statePos){
                getline(file, piece, ';');
                i++;
            }
            if(!piece.empty()){
//              cout << "piece is: " << piece <<endl;
		staMp[piece]++;
		}
        }
            getline(file, piece, '\n');
    }
    
    vector<PAIR> pair_vec1;
    vector<PAIR> pair_vec2;
    for(map<string,int>::iterator map_itr = occMp.begin(); map_itr != occMp.end(); map_itr++){
        pair_vec1.push_back(make_pair(map_itr->first, map_itr->second));
    }
    sort(pair_vec1.begin(), pair_vec1.end(), cmp);
    
    for(map<string,int>::iterator map_itr2 = staMp.begin(); map_itr2 != staMp.end(); map_itr2++){
        pair_vec2.push_back(make_pair(map_itr2->first, map_itr2->second));
    }
    sort(pair_vec2.begin(), pair_vec2.end(), cmp);


    
    occup << "TOP_OCCUPATIONS;NUMBER_CERTIFIED_APPLICATIONS;PERCENTAGE"<<endl;
    for(int i = 0; i < findMin(10,pair_vec1.size()); i++){
        occup << pair_vec1[i].first << ";" << pair_vec1[i].second << ";" <<std::fixed << std::setprecision(1)<< Round(pair_vec1[i].second * 100.0/cc) << "%" << endl;
    }
    
    place << "TOP_STATES;NUMBER_CERTIFIED_APPLICATIONS;PERCENTAGE" << endl;
    for(int i = 0; i < findMin(10,pair_vec2.size()); i++){
        place << pair_vec2[i].first << ";" << pair_vec2[i].second << ";"<<std::fixed << std::setprecision(1)<< Round(pair_vec2[i].second * 100.0/cc) << "%" << endl;
    }
    
    occup.close();
    place.close();
    file.close();
    cout << "finished!" <<endl;
}
