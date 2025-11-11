#include "LinearRegressionModel.h"

LinearRegressionModel::LinearRegressionModel(double lr){
    learnRate = lr;
}
//--
void LinearRegressionModel::train(vector < vector < double > >& features, const vector < double >& labels) {
    // Creates the scale data struct and gets statistics based on columns
    for (int col = 0; col < features[0].size(); col++) {
        
        scalingData sd;
        bool firstTime = true;
        double totalVal = 0;
        
        for (int row = 0; row < features.size(); row++) {
            
            if (firstTime == true) {
                sd.max = features[row][col];
                sd.min = features[row][col];
                totalVal = totalVal + features[row][col];
                firstTime = false;
            } else {
                if (features[row][col] < sd.min) {
                    sd.min = features[row][col];
                } else if (features[row][col] > sd.max) {
                    sd.max = features[row][col];
                }
                
                totalVal = totalVal + features[row][col];
            }
        }
        
        sd.avg = totalVal / features.size();
        dataForCol.push_back(sd);
    }
    
    // Scales the data for training
    for (int i = 0; i < features.size(); i++) {
        for (int j = 0; j < features[i].size(); j++) {
            features[i][j] = ((features[i][j] - dataForCol[j].avg) / (dataForCol[j].max - dataForCol[j].min));
        }
    }
    
    // Adds bias
    for (int row = 0; row < features.size(); row++) {
        features[row].insert(features[row].begin(), 1.0);
    }
    
    // Creates the weight vector
    for (int w = 0; w < features[0].size(); w++) {
        weight.push_back(0.0);
    }
    
    // helper function that allows us to recurse through function until convergence is met
    trainHelper(features, labels);
}
//--
void LinearRegressionModel::trainHelper(vector < vector < double > >& features,const vector < double >& labels) {
    
    vector < double > newWeights;
    
    for (int c = 0; c < features[0].size(); c++) {
        
        double areaBox = 0.0;
        
        for (int r = 0; r < features.size(); r++) {
            
            
            double feature = features[r][c];
            
            // Gradient Expression math is done here
            double singleError = (((weight[c] * feature) - labels[r]) * feature);
            areaBox = areaBox + singleError;
        }
        
        // check to ensure this works
        double newWeight = (weight[c] - learnRate * (areaBox / features.size()));
        newWeights.push_back(newWeight);
    }
    
    int convergence_check = 0;
    
    // Checks if the weights hits a convergence
    for (int i = 0; i < weight.size(); i++) {
        if (abs(newWeights[i] - weight[i]) <= .00001) {
            convergence_check++;
        }
    }
    
    // If all the weights reach a convergence
    if (convergence_check != weight.size()) {
        weight = newWeights;
        trainHelper(features, labels);
    }
}
//--
double LinearRegressionModel::predict(vector <double> &inputFeatures) {
    double result = 0.0;
    
    for (int i = 0; i < inputFeatures.size(); i++) {
        inputFeatures[i] = ((inputFeatures[i] - dataForCol[i].avg) / (dataForCol[i].max - dataForCol[i].min));
    }
    
    inputFeatures.insert(inputFeatures.begin(), 1.0);
    
    for (int i = 0; i < weight.size(); i++) {
        result = result + (inputFeatures[i] * weight[i]);
    }
    
    return result;
}
