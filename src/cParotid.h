/*
 * cParotid.h
 *
 *  Created on: 09/01/2016
 *      Author: jrugis
 */

#ifndef CPAROTID_H_
#define CPAROTID_H_

#include <vector>

class cAcinus;

class cParotid {
public:
	cParotid();
	virtual ~cParotid();
	//void run();
	//void save_results();

private:
	std::vector<cAcinus*> acinii;
};

#endif /* CPAROTID_H_ */
