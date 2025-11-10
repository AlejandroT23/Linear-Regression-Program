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
    
    vector<vector<double>> features1 = { {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0} };
    vector<double> labels1 =           {     3.0,        2.0,        1.0 };
    
    LinearRegressionModel model1(0.1);
    model1.train(features1, labels1);
    
    return 0;
    
}
