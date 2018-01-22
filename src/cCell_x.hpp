/*
 * cCell_x.hpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#ifndef CCELL_X_H_
#define CCELL_X_H_

#include <string>

class cAcinus;
class cCellMesh;

class cCell_x {
public:
	cCell_x(int id, cAcinus *parent);
	virtual ~cCell_x();
	void step();

private:
	int id;
	cAcinus* parent;
	cCellMesh* mesh;
};

#endif /* CCELL_X_H_ */
