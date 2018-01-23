/*
 * cAcinus.cpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#include <iostream>
#include <string>

#include "cParotid.hpp"
#include "cCell_x.hpp"
#include "cAcinus.hpp"

cAcinus::cAcinus(int i, cParotid* p) {
	id = "a" + std::to_string(i);
	parent = p;
	int count = 7; // GET NUMBER OF CELLS FROM MESH FILE NAMES?
	for(int i=0; i<count; i++) {
		std::cout << "<Acinus> id:" << id << " creating cell object " << i+1 << std::endl;
		cells.push_back(new cCell_x(i+1, this));
	} 
}

cAcinus::~cAcinus() {
	while(!cells.empty()) {
		delete cells.back();
		cells.pop_back(); 
	}
}

void cAcinus::step() {
	#pragma omp parallel for
	for(int i=0; i<cells.size(); i++){
		cells[i]->step();
	}
}


