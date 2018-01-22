/*
 ============================================================================
 Name        : main.cpp
 Author      : J.Rugis
 Version     :
 Copyright   : (c) 2018 J.Rugis
 Description : Parotid Gland Simulation with openmp, vcl
 ============================================================================
*/

#include <iostream>
#include <sys/time.h>
#include <unistd.h>

#include "cParotid.hpp"

#define TEMP_SIZE 40

int main(int argc,char **args){
	cParotid* parotid;
	struct timeval start, end;
	int duration;
	std::string host_name;

	gettimeofday(&start, NULL); // get the time

	// get the hostname
	char temp[TEMP_SIZE];
	gethostname(temp, TEMP_SIZE);
	host_name = temp;
	std::cout << "<main> hostname:" << host_name<< std::endl;

	// setup and run a parotid object
	std::cout << "<main> creating parotid object" << std::endl;
	parotid = new cParotid;
	parotid->run();

	// save the results
	parotid->save_results();
	gettimeofday(&end, NULL);
	duration = end.tv_sec - start.tv_sec;
	std::cout << "<main> execution time: " << duration << " sec" << std::endl;

	delete parotid;

	return 0;
}
