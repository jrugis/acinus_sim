/*
 * cAcinus.hpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#ifndef CACINUS_H_
#define CACINUS_H_

#include <fstream>
#include <string>
#include <vector>

class cParotid;
class cCell_x;
class cCellMesh;

class cAcinus {
friend class cCell_x;
public:
	cAcinus(int id, cParotid* parent);
	virtual ~cAcinus();
	void check_common();
	void step();

private:
	std::string id;
	cParotid* parent;
	std::ofstream out;
	std::vector<cCell_x*> cells;
};

#endif /* CACINUS_H_ */
