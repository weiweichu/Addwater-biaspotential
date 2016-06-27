//
//  InsertWater.cpp
//  Solvation
//
//  Created by Weiwei Chu on 5/17/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#include "InsertWater.h"
#include "ReadPotential.h"

void InsertWater::insert(atom *inserted){
   // atomlist all;
    atomlist po = grid_.AtomList();
    int insertedwater=0;
    double ran;
    vector <double> potent;
    char potentialfile[] = "density.txt";
    ReadPotential readpotential(potentialfile);
    readpotential.potential(&potent);
    //cout << water_.size()<<endl;
    for (int i=0;i<water_.size();i++) {
		//cout << water_.size()<< "   "<< i<<endl;
        int flag=1;
        
        //for(int k =0; k<3;k++){
        if (i%3 == 0){
			
	        int kp = int(water_[i][0]-box_[0]);
	        ran = double(rand())/RAND_MAX;
		    if (ran < potent[kp]){
	        atom p = grid_.neighborlist(water_[i],po);
	        
	        //cout <<p.size()<<"  neighborlistsize per water"<<endl;
	        
	        for(int j=0;j<p.size();j++){
	                if (water_[i].dist(p[j])>radius_) {
	                    flag *= 1;
	                }
	                else{
	                    flag *= 0;
	                   // break;
	                }
	                if (flag == 0) {
	                    break;
	                }
	        }
		//}
	        if (flag == 1){
				insertedwater++;
				cout << "inserted   "<<i<<"   "<<water_.size()<<"   "  <<insertedwater<<"   "<< double(insertedwater)/i<<endl;
	            inserted->push_back(water_[i+0]);
	            //cout << water_[i+0][0]<<" "<< water_[i+1][1]<<" "<<water_[i+2][2]<<" "<<endl;
	            inserted->push_back(water_[i+1]);
	           // cout << water_[i+1][0]<<" "<< water_[i+1][1]<<" "<<water_[i+1][2]<<" "<<endl;
	            inserted->push_back(water_[i+2]);
	           // cout << water_[i+2][0]<<" "<< water_[i+2][1]<<" "<<water_[i+2][2]<<" "<<endl;
            }        
        }
    }
   } 
}
