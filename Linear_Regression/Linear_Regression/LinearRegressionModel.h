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
    void trainOneFeatureHelper(vector < vector < double > >& features, vector < double >& weights);
    void trainMultiFeatureHelper(vector < vector < double > >& features, vector < vector < double > >& weights);
    
    
    double learnRate = 0.0;
    vector < double > weight;
    vector < vector < double > > weights;
};
