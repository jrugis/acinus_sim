/*
 * cParotid.cpp
 *
 *  Created on: 09/01/2016
 *      Author: jrugis
 */

#include "cAcinus.hpp"
#include "cParotid.hpp"

cParotid::cParotid() {
	for(int i=0; i<1; i++) acinii.push_back(new cAcinus(i+1, this)); // only one acinus (for now)
}

cParotid::~cParotid() {
	while(!acinii.empty()) {
		delete acinii.back();
		acinii.pop_back(); 
	}
}

