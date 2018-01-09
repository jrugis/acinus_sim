/*
 * cAcinus.cpp
 *
 *  Created on: 09/01/2016
 *      Author: jrugis
 */

#include "cParotid.hpp"
#include "cCell_x.hpp"
#include "cAcinus.hpp"

cAcinus::cAcinus(int i, cParotid* p) {
	id = i;
	parent = p;
	for(int i=0; i<7; i++) cells.push_back(new cCell_x(i+1, this)); // GET NUMBER OF CELLS FROM MESH FILE NAMES
}

cAcinus::~cAcinus() {
	while(!cells.empty()) {
		delete cells.back();
		cells.pop_back(); 
	}
}


