/*
 * cCellMesh.cpp
 *
 *  Created on: 30/03/2018
 *      Author: jrugis
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>

#include "cCell_x.hpp"
#include "cCellMesh.hpp"

cCellMesh::cCellMesh(std::string mesh_name, cCell_x* p){
	// initialise member variables
	vertices_count = tetrahedrons_count = 0;
	surface_triangles_count = apical_triangles_count = basal_triangles_count = 0;
	common_triangles_count = 0;
	parent = p;
	id = mesh_name;	
	get_mesh(id + ".bin");
	//calc_dist();
}

cCellMesh::~cCellMesh(){
}

//void cCellMesh::calc_dist(){
//	parent->out << "<CellMesh> id:" + id + " calculating node distance to surface..." << std::endl;
//	Eigen::Matrix<tCoord,1,3> v1, v2;
//	for(tElement n = 0; n < nodes_count; n++){
//		if(surface_node(n)){
//			node_data(n, dist_surface) = 0.0;
//			continue;
//		}
//		v1 = coordinates.block<1,3>(n, 0);
//		node_data(n, dist_surface) = std::numeric_limits<tCalcs>::max();
//		for(tElement s = 1; s < nodes_count; s++){
//			if(!surface_node(s)) continue;
//			v2 = coordinates.block<1,3>(s, 0);
//			tCalcs d = (v1 - v2).squaredNorm();
//			if(d < node_data(n, dist_surface)) node_data(n, dist_surface) = d;
//		}
//		node_data(n, dist_surface) = std::sqrt(tCalcs(node_data(n, dist_surface)));
//	}
//}

void cCellMesh::get_mesh(std::string file_name){
    // local variables
	std::ifstream cell_file(file_name.c_str(), std::ios::in | std::ios::binary); // open the mesh file
	uint32_t i32;
	float f32;

    // check the file is open
    if (not cell_file.is_open()) {
        std::cerr << "<CellMesh> ERROR: the mesh file could not be opened (" << file_name << ")" << std::endl;
        exit(1);
    }
	// get the mesh vertices (int32 count, 3x-float32 vertices) 
	cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
	vertices_count = i32;
	vertices.resize(vertices_count, Eigen::NoChange);
	for(int n=0; n<vertices_count; n++){
		for(int m=0; m<3; m++){
			cell_file.read(reinterpret_cast<char *>(&f32), sizeof(f32));
			vertices(n,m) = f32;
		}

	}
	// get the surface triangles (int32 count, 3x-int32 vertex indices, float32 dnl)
	cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
	surface_triangles_count = i32;
	surface_triangles.resize(surface_triangles_count, Eigen::NoChange);
	dnl.resize(surface_triangles_count, Eigen::NoChange);
	for(int n=0; n<surface_triangles_count; n++){
		for(int m=0; m<3; m++){
			cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
			surface_triangles(n,m) = i32-1; // change to zero indexed
		}
		cell_file.read(reinterpret_cast<char *>(&f32), sizeof(f32));
		dnl(n) = f32;
	}
	// get the element tetrahedrons (int32 count, 4x-int32 vertex indices)
	cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
	tetrahedrons_count = i32;
	tetrahedrons.resize(tetrahedrons_count, Eigen::NoChange);
	for(int n=0; n<tetrahedrons_count; n++){
		for(int m=0; m<4; m++){
			cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
			tetrahedrons(n,m) = i32-1; // change to zero indexed
		}
	}
	// get the apical triangles (int32 count, int32 triangle indices)
	cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
	apical_triangles_count = i32;
	apical_triangles.resize(apical_triangles_count, Eigen::NoChange);
	for(int n=0; n<apical_triangles_count; n++){
		cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
		apical_triangles(n) = i32-1; // change to zero indexed
	}
	// get the basal triangles (int32 count, int32 triangle indices)
	cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
	basal_triangles_count = i32;
	basal_triangles.resize(basal_triangles_count, Eigen::NoChange);
	for(int n=0; n<basal_triangles_count; n++){
		cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
		basal_triangles(n) = i32-1; // change to zero indexed
	}
	// get the cell-to-cell data (int32 count, 3x-int32 this_triamgle, other_cell, other_triangle)
	cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
	common_triangles_count = i32;
	common_triangles.resize(common_triangles_count, Eigen::NoChange);
	for(int n=0; n<common_triangles_count; n++){
		for(int m=0; m<3; m++){
			cell_file.read(reinterpret_cast<char *>(&i32), sizeof(i32));
		    if (i32 < 1) {
		        std::cerr << "<CellMesh> ERROR: "<< m << ", " << n << std::endl;
//		        exit(1);
		    }
			common_triangles(n,m) = i32-1; // change to zero indexed
//			parent->out << i32-1 << " ";
//	        std::cerr << "<CellMesh> ERROR: "<< common_triangles(n,2) << std::endl;
		}
//		parent->out << std::endl;
	}
	cell_file.close();
}

void cCellMesh::print_info(){
	parent->out << "<CellMesh> id:" + id + " vertices_count: " << vertices_count << std::endl;
	parent->out << "<CellMesh> id:" + id + " tetrahedrons_count: " << tetrahedrons_count << std::endl;
	parent->out << "<CellMesh> id:" + id + " surface_triangles_count: " << surface_triangles_count << std::endl;
	parent->out << "<CellMesh> id:" + id + " apical_triangles_count: " << apical_triangles_count << std::endl;
	parent->out << "<CellMesh> id:" + id + " basal_triangles_count: " << basal_triangles_count << std::endl;
	parent->out << "<CellMesh> id:" + id + " common_triangles_count: " << common_triangles_count << std::endl;
}
