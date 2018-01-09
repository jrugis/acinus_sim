/*
 * cCell_x.cpp
 *
 *  Created on: 09/01/2016
 *      Author: jrugis
 */

#include "cAcinus.hpp"
#include "cCellMesh.hpp"
#include "cCell_x.hpp"

cCell_x::cCell_x(int i, cAcinus* p) {
	id = i;
	parent = p;
}

cCell_x::~cCell_x() {
}


