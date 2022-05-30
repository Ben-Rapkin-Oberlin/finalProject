#include <vector>
#include <filesystem>
#include <string>
#include <utility>
#include <random>
#include <array>
#include <cmath>
#include "train.cxx"

using namespace std;



std::array<float, 20>bootstrap(vector<std::array<float, 10> > data, int bCount) {
	
	//device generates random seed for number generator
	std::random_device rd;

	//mersenne twister random number generator for bootstrap
	std::mt19937 gen(rd());

	//filters rng to be uniformly distibuted data element indices for random sampling
	std::uniform_int_distribution<int> dist(0, data.size() -1);

	std::vector<float * > bData; //create temp vector for bootstrap data, stores pointers to float arrays

	//creates new data samples equal to bCount, stores in bData
	for (int i = 0; i < bCount; ++i) {

		//creates new dynamically allocated array stored in vector at index i
		bData.push_back(new float[10]{
			//populates array by sampling with replacement from data set. This means that the array is a randomly generated new data piece that can be used for statistical analysis.
			data.at(dist(gen))[0],
			data.at(dist(gen))[1],
			data.at(dist(gen))[2],
			data.at(dist(gen))[3],
			data.at(dist(gen))[4],
			data.at(dist(gen))[5],
			data.at(dist(gen))[6],
			data.at(dist(gen))[7],
			data.at(dist(gen))[8],
			data.at(dist(gen))[9],
			});
	}

	//temp variable for adding all values to find mean and adding values to find standard deviation
	float tempSum;

	//stores standard devation and mean for function return
	std::array<float, 20> fData;

	for (int i = 0; i < 10; ++i) {

		tempSum = 0;

		//loops through each sample to add for mean
		for (int x = 0; x < bCount; ++x) {
			tempSum += bData.at(x)[i];
		}
		
		tempSum = tempSum / bCount;

		//inserts mean at correct position in fData
		fData[(i + 1) * 2] = tempSum;

		tempSum = 0;

		//loops through each sample to add for SD according to formula for standard deviation
		for (int x = 0; x < bCount; ++x) {
			tempSum = tempSum + std::pow(std::abs(bData.at(x)[i]/*value*/ - fData[(i + 1) * 2] /*mean*/), 2);
		}
		//finishes calulating SD and places it in correct position in fData
		fData[i*2] = std::sqrt(tempSum / bCount);
	}

	//cleans up
	for (int x = 0; x < bCount; ++x) {
		delete[] bData.at(x);
	}
	bData.~vector();

	return fData;
}

std::pair< std::vector<string>, std::vector<std::array<float, 20> > > dataAnalysis(string path, int bootCount) {
	std::vector<std::array<float, 20> > pData;
	std::vector<string> pNames; //index of name list correlates to index in pData with that person's data




	//loops through main directory of people
	for (const auto& person : std::filesystem::directory_iterator(path)) {
		pNames.push_back(person.path().stem().string()); //adds to name list
		std::vector<std::array<float, 10> > tempData; //create temp vector for person's code




		//loops through a person's code directory
		for (const auto& file : std::filesystem::directory_iterator(person.path())) {
			tempData.push_back(train(file.path().string()));
		}


		pData.push_back(bootstrap(tempData, bootCount));


		//cleans up
		tempData.~vector();
	}

	//array for return
	std::pair< std::vector<string>, std::vector<std::array<float, 20> > > fPair;
	fPair.first = pNames;
	fPair.second = pData;

	return fPair;

}
