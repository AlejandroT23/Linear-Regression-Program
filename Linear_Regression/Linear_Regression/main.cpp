//
//  main.cpp
//  Linear_Regression
//
//  Created by Alejandro Toledo on 11/6/25.
//

#include <iostream>
#include <vector>
#include "LinearRegressionModel.h"
using namespace std;

int main() {
    
    double learningRate = 0.1;
    
    vector<vector<double>> features1 = { {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0} };
    vector<double> labels1 =           {     3.0,        2.0,        1.0 };
    
    LinearRegressionModel model1(learningRate);
    model1.train(features1, labels1);

    vector<double> unknownInput1 = { 0.0, 4.0 };
    cout << model1.predict(unknownInput1) << endl;
    
    //test 2
    vector<vector<double>> features2 = { { 6.2 },{ 2.8 },{ 8.3 },{ 1.5 },{ 2.0 },{ 3.7 },{ 4.4 },{ 9.4 },{ 6.9 } };
    vector<double> labels2 =           {   19.0,   9.0,    40.0,   7.0,    20.0,   17.0,   27.0,   44.0,  30.0 };

    LinearRegressionModel model2(learningRate);
    model2.train(features2, labels2);

    vector<double> unknownInput2 = { -4.0 };
    model2.predict(unknownInput2);

        
    return 0;
    
}
