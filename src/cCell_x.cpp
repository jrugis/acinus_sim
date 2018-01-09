/*
 * cCell_x.cpp
 *
 *  Created on: 09/01/2016
 *      Author: jrugis
 */

#include "cAcinus.h"
#include "cCellMesh.h"
#include "cCell_x.h"

cCell_x::cCell_x(int i, cAcinus* p) {
	id = i;
	parent = p;
}

cCell_x::~cCell_x() {
}


