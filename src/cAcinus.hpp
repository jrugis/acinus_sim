/*
 * cAcinus.hpp
 *
 *  Created on: 09/01/2018
 *      Author: jrugis
 */

#ifndef CACINUS_H_
#define CACINUS_H_

#include <string>
#include <vector>

class cParotid;
class cCell_x;

class cAcinus {
public:
	cAcinus(int id, cParotid* parent);
	virtual ~cAcinus();
	std::string id;
	void step();

private:
	cParotid* parent;
	std::vector<cCell_x*> cells;
};

#endif /* CACINUS_H_ */
