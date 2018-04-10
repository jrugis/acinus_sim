/*
 * cAcinus.cpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#include <iostream>
#include <string>
#include <cmath>
#include <Eigen/Dense>

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
	cells.resize(count);

	#pragma omp parallel for
	for(int i=0; i<count; i++) {
		//cells.push_back(new cCell_x(i+1, this));
		cells[i] = new cCell_x(i+1, this);
	} 
	//check_common();
}

cAcinus::~cAcinus() {
	out.close();
	while(!cells.empty()) {
		delete cells.back();
		cells.pop_back(); 
	}
}

// checks for matching common triangle faces between two cells
void cAcinus::check_common() {
	long this_tri, other_cell, other_tri;
	Eigen::Matrix<tCoord,1,3> v1, v2, v3, c1, c2;
	tCalcs d;
	for(int c=0; c<7; c++){
		for(int n=0; n<cells[c]->mesh->common_triangles_count; n++){
			this_tri = cells[c]->mesh->common_triangles(n,0);
			other_cell = cells[c]->mesh->common_triangles(n,1);
			other_tri = cells[c]->mesh->common_triangles(n,2);		

			// this cell - triangle face centroid
			v1 = cells[c]->mesh->vertices.block<1,3>(cells[c]->mesh->surface_triangles(this_tri,0), 0);
			v2 = cells[c]->mesh->vertices.block<1,3>(cells[c]->mesh->surface_triangles(this_tri,1), 0);
			v3 = cells[c]->mesh->vertices.block<1,3>(cells[c]->mesh->surface_triangles(this_tri,2), 0);
			c1 = (v1+v2+v3)/3.0;

			// other cell - triangle face centroid
			v1 = cells[other_cell]->mesh->vertices.block<1,3>(cells[other_cell]->mesh->surface_triangles(other_tri,0), 0);
			v2 = cells[other_cell]->mesh->vertices.block<1,3>(cells[other_cell]->mesh->surface_triangles(other_tri,1), 0);
			v3 = cells[other_cell]->mesh->vertices.block<1,3>(cells[other_cell]->mesh->surface_triangles(other_tri,2), 0);
			c2 = (v1+v2+v3)/3.0;

			// the two centroids should be very close to each other
			d = (c1-c2).norm();
			if(d > 0.001) out << d << std::endl;
		}
	}
}

void cAcinus::step() {
	#pragma omp parallel for
	for(int i=0; i<cells.size(); i++){
		cells[i]->step();
	}
}


