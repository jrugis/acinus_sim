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
	parent = p;
	id = "a" + std::to_string(i);
	out.open(id + ".out");

	int count = 7; // GET NUMBER OF CELLS FROM MESH FILE NAMES?
	out << "<Acinus> id:" << id << " creating " << count << " cell objects " << std::endl;
	for(int i=0; i<count; i++) {
		cells.push_back(new cCell_x(i+1, this));
	} 
}

cAcinus::~cAcinus() {
	out.close();
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


