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
#include "cCellMesh.hpp"
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

	check_common();
}

cAcinus::~cAcinus() {
	out.close();
	while(!cells.empty()) {
		delete cells.back();
		cells.pop_back(); 
	}
}

void cAcinus::check_common() {
	long this_tri, other_cell, other_tri;
	double v1, v2, v3;
	for(int n=0; n<cells[0]->mesh->common_triangles_count; n++){
		this_tri = cells[0]->mesh->common_triangles(n,0);
		other_cell = cells[0]->mesh->common_triangles(n,1);
		other_tri = cells[0]->mesh->common_triangles(n,2);
		out << "<Acinus> check_common:" << " common indices ";
		out << this_tri << " " << other_cell << " " << other_tri << std::endl;

		// this cell
		v1 = cells[0]->mesh->vertices(cells[0]->mesh->surface_triangles(this_tri,0));
		v2 = cells[0]->mesh->vertices(cells[0]->mesh->surface_triangles(this_tri,1));
		v3 = cells[0]->mesh->vertices(cells[0]->mesh->surface_triangles(this_tri,2));
		out << v1 << " " << v2 << " " << v3 << " " << std::endl;

		// other cell
		v1 = cells[other_cell]->mesh->vertices(cells[other_cell]->mesh->surface_triangles(other_tri,0));
		v2 = cells[other_cell]->mesh->vertices(cells[other_cell]->mesh->surface_triangles(other_tri,1));
		v3 = cells[other_cell]->mesh->vertices(cells[other_cell]->mesh->surface_triangles(other_tri,2));
		out << v1 << " " << v2 << " " << v3 << " " << std::endl;

		out << "." << std::endl;
	}
}

void cAcinus::step() {
	#pragma omp parallel for
	for(int i=0; i<cells.size(); i++){
		cells[i]->step();
	}
}


