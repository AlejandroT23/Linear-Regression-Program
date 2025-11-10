#pragma once
#include <iostream>
#include <vector>
using namespace std;

class LinearRegressionModel {
public:
    LinearRegressionModel(double lr);
    void train(vector < vector < double > >& features, const vector < double >& labels);
    double predict(vector < double >& inputFeatures);
private:
    void trainHelper(vector < vector < double > >& features, const vector < double >& labels, int sizeCol);
    
    struct scalingData {
        double min = 0;
        double max = 0;
        double avg = 0;
    };
    
    double learnRate = 0.0;
    vector < scalingData > dataForCol;
    vector < double > weight;
//    vector < double > newWeights;
};
