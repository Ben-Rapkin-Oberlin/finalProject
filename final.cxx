// final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <vector>


using namespace std;

std::pair< std::vector<string>, std::vector<float* > > dataAnalysis(string path, int bootCount);
array<float, 10> train(string a);

int main()
{
    float z = 2.576;
    auto result_from_dataAna = dataAnalysis("Data", 10000); // call dataAnalysis to get the mean and std
    vector<string> names = result_from_dataAna.first; // store the names
    vector<float*> values = result_from_dataAna.second; // store the standard diviation and mean


    auto result_from_train = train("testfile.c"); // call train to get the training results
    vector<vector < pair<float, float>>> conf_interval; // declare the confidential interval

    vector<int> result; // declare the vectore to store the rsult

   
    for (auto it = values.begin(); it != values.end(); it++) { // go through the dataAnalysis data part to calculate the confidential interval
        vector < pair<float, float>> current;
        for (int i = 1; i < 20; i+=2) {
            float lower = *it[i] - z * sqrt((*it[i] * (1 - *it[i])) / 10000);
            float higher = *it[i] + z * sqrt((*it[i] * (1 - *it[i])) / 10000);
                current.push_back(pair<float, float>(lower, higher));
        }
        
        conf_interval.push_back(current);
    }

    for (int i = 0; i < conf_interval.size(); i++) { // go through the confidential intervals and the trainning data to make decision
        int tempSum = 0;
        for (int j = 0; j < 10; j++) {
            if (result_from_train[i] > conf_interval.at(i).at(j).first
                && result_from_train[i] < conf_interval.at(i).at(j).second) {
                tempSum++;
            }
        }
        result.push_back(tempSum);
        if (tempSum >= 8) {
            cout << "The code belongs to " << names.at(i) << endl;
        }
        else {
            cout << "The code is incongruous for " << names.at(i) << endl;
        }
    }


    return 0;
}
