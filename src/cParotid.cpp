/*
 * cParotid.cpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#include <iostream>

#include "cAcinus.hpp"
#include "cParotid.hpp"

cParotid::cParotid() {
	int count = 1;  // only one acinus (for now)
	for(int i=0; i<count; i++) {
		std::cout << "<Parotid> creating acinus object " << i+1 << std::endl;
		acinii.push_back(new cAcinus(i+1, this));
	}
}

cParotid::~cParotid() {
	while(!acinii.empty()) {
		delete acinii.back();
		acinii.pop_back(); 
	}
}

void cParotid::run() {
	for(int i=0; i<acinii.size(); i++){
		acinii[i]->step();
	}
}

void cParotid::save_results() {
}

