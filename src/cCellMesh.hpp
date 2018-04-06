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
typedef double tDist;
typedef long tIndex;

//typedef double tCalcs; // MOVE THIS????

class cCellMesh {
public:
	cCellMesh(std::string mesh_name, cCell_x* parent);
	virtual ~cCellMesh();
	void print_info();

	tIndex vertices_count, tetrahedrons_count;
	tIndex surface_triangles_count, apical_triangles_count, basal_triangles_count;
	tIndex common_triangles_count;
	Eigen::Array<tCoord, Eigen::Dynamic, 3, Eigen::RowMajorBit> vertices;
	Eigen::Array<tIndex, Eigen::Dynamic, 3, Eigen::RowMajorBit> surface_triangles;
	Eigen::Array<tIndex, Eigen::Dynamic, 4, Eigen::RowMajorBit> tetrahedrons;
	Eigen::Array<tIndex, Eigen::Dynamic, 3, Eigen::RowMajorBit> common_triangles;
	Eigen::Array<tDist, Eigen::Dynamic, 1> dnl;
	Eigen::Array<tIndex, Eigen::Dynamic, 1> apical_triangles;
	Eigen::Array<tIndex, Eigen::Dynamic, 1> basal_triangles;

private:
	std::string id;
	cCell_x* parent;
	void get_mesh(std::string file_name);
	void calc_dist();
};

#endif /* CCELLMESH_H_ */
