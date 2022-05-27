#include <vector>
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;
//add clean() for memory allocated, use vector destuctor

array <vector *> dataAnalysis(string path, int bootCount) {
	std::vector<void *> pData;

	//loops through main directory of people
	for (const auto &person: directory_iterator(path)){
		//loops through a person's code directory
		for (const auto& file : directory_iterator(person.path())
			//create temp vector for person's code
			std::vector<array *> 


}


