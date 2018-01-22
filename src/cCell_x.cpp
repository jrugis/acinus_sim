/*
 * cCell_x.cpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#include <iostream>
#include <string>

#include "cAcinus.hpp"
#include "cCellMesh.hpp"
#include "cCell_x.hpp"

cCell_x::cCell_x(int i, cAcinus* p) {
	id = i;
	parent = p;
	std::string mesh_name = "a" + std::to_string(p->id) + "c" + std::to_string(id);
	mesh = new cCellMesh(mesh_name);
	mesh->print_info();
}

cCell_x::~cCell_x() {
	delete mesh;
}

void cCell_x::step() {
	#pragma omp critical(print)
	{
		std::cout << "<Cell> id:" << id << " step" << std::endl;
	}
}

