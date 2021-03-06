/*
 * cCell_x.hpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#ifndef CCELL_X_H_
#define CCELL_X_H_

#include <fstream>
#include <string>
//#include <Eigen/Dense>
//#include <Eigen/Sparse>

class cAcinus;
class cCellMesh;
class cVCLSolver;

#include "defs.hpp"
#include "cVCLSolver.hpp"

#define VARIABLES 3 // the number of diffusing model variables
#define REF_MASS_SIZE 4   // reference mass dimension

// the 3D model parameters
enum model_parameters{ \
	delT, totalT, numT, reduce, \
	PLCsrt, PLCfin, \
	IPRdn, IPRdf, IPRmin, \
	PLCds, PLCdl, \
	c0, ip0, h0, ce0, gama, \
	Dc, Dp, De, Fc, Fip, \
	V_RyR, K_RyR, K_RyR2, d_RyR, \
	k_beta, K_p, K_c, K_h, kIPR, kIPR_min, \
	V_p, k_p, K_bar, \
	V_3K, V_5K, K_PLC, K3K, VPLC, \
	K_hRyR, tau, \
	PCOUNT};

enum model_node_values{IPR_n, PLC_n, MODELNCOUNT};            // node spatial factors
enum model_element_values{VOL_e, IPR_e, PLC_e, MODELECOUNT};  // element volume and spatial factors

// some convenience typedefs
typedef Eigen::Matrix<tCalcs, Eigen::Dynamic, Eigen::Dynamic> MatrixXXC;
typedef Eigen::Matrix<tCalcs, Eigen::Dynamic, 1> MatrixX1C;
typedef Eigen::Array<tCalcs, Eigen::Dynamic, 1> ArrayX1C;
typedef Eigen::Array<tCalcs, 1, VARIABLES> Array1VC;
typedef Eigen::Array<tCalcs, REF_MASS_SIZE, REF_MASS_SIZE> ArrayRefMass;
typedef Eigen::Triplet<tCalcs> Triplet;

class cCell_x {
friend class cAcinus;
friend class cCellMesh;
friend class cVCLSolver;
public:
	cCell_x(int id, cAcinus *parent);
	virtual ~cCell_x();

	void step();
	void save_results();

private:
	std::string id;
	std::ofstream out;
	cAcinus* parent;
	cCellMesh* mesh;
    cVCLSolver *solver;

	tCalcs p[PCOUNT]; // the model parameters array
	Eigen::Array<tCalcs, Eigen::Dynamic, MODELNCOUNT> node_data;
	Eigen::Array<tCalcs, Eigen::Dynamic, MODELECOUNT> element_data;

	tIndex time_steps;
	MatrixXXC u; // solution matrix
	SparseMatrixTCalcs sparseA, sparseMass; // A and mass matrices

	void fatal_error(std::string msg);
	void get_parameters();
	void init_u();
	void make_matrices();
	MatrixX1C make_load(long i);
	ArrayRefMass make_ref_mass();
	Array1VC getbodyreactions(tCalcs c, tCalcs ip, tCalcs ce, tCalcs ipr_f, tCalcs plc_f);
	tCalcs getboundaryflux(tCalcs c);
	void save_matrix(std::string file_name, MatrixXXC mat);
    void save_matrix_reduce(std::string file_name, MatrixXXC mat);
};

#endif /* CCELL_X_H_ */
