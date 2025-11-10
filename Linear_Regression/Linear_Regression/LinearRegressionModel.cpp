#include "LinearRegressionModel.h"

LinearRegressionModel::LinearRegressionModel(double lr){
    learnRate = lr;
}
//--
void LinearRegressionModel::train(vector < vector < double > >& features, const vector < double >& labels) {
    
    int sizeCol = 0;
    
    // Gets the length for scaling
    // This only
    for (int i = 0; i < features.size(); i++) {
        sizeCol++;
    }
    
    // Creates the scale data struct
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
    
    // Scales the data
    // Zeros are printed as 0 instead of 0.0
    for (int i = 0; i < features.size(); i++) {
        for (int j = 0; j < features[i].size(); j++) {
            features[i][j] = ((features[i][j] - dataForCol[j].avg) / (dataForCol[j].max - dataForCol[j].min));
        }
    }
    
    // Adds bias
    for (int row = 0; row < features.size(); row++) {
        features[row].insert(features[row].begin(), 1.0);
    }
    
    // Test print statement
//    for (int i = 0; i < features.size(); i++) {
//        for (int j = 0; j < features[i].size(); j++) {
//            cout << features[i][j] << " ";
//        }
//        
//        cout << endl;
//    }
    
    for (int w = 0; w < labels.size(); w++) {
        weight.push_back(0.0);
    }
    
    trainHelper(features, labels, sizeCol);
    
    //-- Issues
//    for (int i = 0; i < weight.size(); i++) {
//        cout << weight[i] << endl;
//    }
}
//--
void LinearRegressionModel::trainHelper(vector < vector < double > >& features,const vector < double >& labels, int size_col) {
    
    vector < double > newWeights;
    
    for (int c = 0; c < features[0].size(); c++) {
        
        double areaBox = 0.0;
        
        for (int r = 0; r < features.size(); r++) {
            // CHANGE THIS NAMES
            
            double feature = features[r][c];
            
            // I believe the error is here
            double singleError = (((weight[c] * feature) - labels[r]) * feature);
            areaBox = areaBox + singleError;
        }
        
        // check to ensure this works
        double newWeight = (weight[c] - learnRate * (areaBox / features.size()));
        newWeights.push_back(newWeight);
    }
    
    int convergence_check = 0;
    
    // FIX WEIGHT SIZE!!!!
    for (int i = 0; i < weight.size(); i++) {
        if (abs(newWeights[i] - weight[i]) <= .00001) {
            convergence_check++;
        }
    }
    
    if (convergence_check != weight.size()) {
        weight = newWeights;
        trainHelper(features, labels, features[0].size());
    }
}
//--
double LinearRegressionModel::predict(vector <double> &inputFeatures) {
    double result = 0.0;
    
    for (int i = 0; i < inputFeatures.size(); i++) {
        inputFeatures[i] = ((inputFeatures[i] - dataForCol[i].avg) / (dataForCol[i].max - dataForCol[i].min));
    }
    
    inputFeatures.insert(inputFeatures.begin(), 1.0);
    
//    for (int row = 0; row < features.size(); row++) {
//        features[row].insert(features[row].begin(), 1.0);
//    }
    
    for (int i = 0; i < weight.size(); i++) {
        result = result + (inputFeatures[i] * weight[i]);
//        cout << result << endl;
    }
    
    return result;
}

//LIST OF WHAT NEEDS TO BE DONE
//1. INITIALIZE UPDATED WEIGHT VECTOR FOR NEW WEIGHTS IN LOOP
//2. USE OLD WEIGHT TO CALCULATE NEW ONE
//3. CHECK FOR CONVERGENCE - IF YES, STOP, IF NOT, RECURSION
