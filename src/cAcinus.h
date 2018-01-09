/*
 * cAcinus.h
 *
 *  Created on: 09/01/2016
 *      Author: jrugis
 */

#ifndef CACINUS_H_
#define CACINUS_H_

#include <vector>

class cParotid;
class cCell_x;

class cAcinus {
public:
	cAcinus(int id, cParotid* parent);
	virtual ~cAcinus();

private:
	int id;
	cParotid* parent;
	std::vector<cCell_x*> cells;
};

#endif /* CACINUS_H_ */
