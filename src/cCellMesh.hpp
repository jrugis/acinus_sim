/*
 * cCellMesh.hpp
 *
 *  Created on: 30/03/2018
 *      Author: jrugis
 */

#ifndef CCELLMESH_H_
#define CCELLMESH_H_

#include <string>
#include <Eigen/Dense>

class cCell_x;

typedef double tCoord;
//typedef long tElement;
typedef long tIndex;

//typedef double tCalcs; // MOVE THIS????

//enum mesh_node_values{dist_lumen, dist_surface, MESHNCOUNT};
enum cell_to_cell{triangle, other_cell, other_triangle, C2CCOUNT};

class cCellMesh {
public:
	cCellMesh(std::string mesh_name, cCell_x* parent);
	virtual ~cCellMesh();
	void print_info();

	//tElement nodes_count;
	//tElement total_elements_count, surface_elements_count, volume_elements_count;
	//Eigen::Array<tCoord, Eigen::Dynamic, 3, Eigen::RowMajorBit> coordinates;
	//Eigen::Array<tElement, Eigen::Dynamic, 3, Eigen::RowMajorBit> surface_elements;
	//Eigen::Array<tElement, Eigen::Dynamic, 4, Eigen::RowMajorBit> volume_elements;
	//Eigen::Array<tCalcs, Eigen::Dynamic, MESHNCOUNT, Eigen::RowMajorBit> node_data;
	//Eigen::Array<bool, Eigen::Dynamic, 1> surface_node;
	tIndex vertices_count, tetrahedrons_count;
	tIndex surface_triangles_count, apical_triangles_count, basal_triangles_count;
	Eigen::Array<tCoord, Eigen::Dynamic, 3, Eigen::RowMajorBit> vertices;
	Eigen::Array<tIndex, Eigen::Dynamic, 3, Eigen::RowMajorBit> surface_triangles;
	Eigen::Array<tIndex, Eigen::Dynamic, 4, Eigen::RowMajorBit> tetrahedrons;
	Eigen::Array<tIndex, Eigen::Dynamic, 1> apical_triangles;
	Eigen::Array<tIndex, Eigen::Dynamic, 1> basal_triangles;
	Eigen::Array<tIndex, Eigen::Dynamic, C2CCOUNT, Eigen::RowMajorBit> cell_to_cell_data;

private:
	std::string id;
	cCell_x* parent;
	void get_mesh(std::string file_name);
	void calc_dist();
};

#endif /* CCELLMESH_H_ */
