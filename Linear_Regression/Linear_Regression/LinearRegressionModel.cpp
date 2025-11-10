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
    
    // Creates the scale data
    for (int col = 0; col < (sizeCol-1); col++) {
        
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
        
        sd.avg = totalVal / sizeCol;
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
    for (int i = 0; i < features.size(); i++) {
        for (int j = 0; j < features[i].size(); j++) {
            cout << features[i][j] << " ";
        }
        
        cout << endl;
    }
    
    // train
}





//-- CHANGE THIS
void LinearRegressionModel::trainOneFeatureHelper(vector < double >& features, vector < double >& label, vector < double >& weights, double weight) {
    
    // Are we just calling the weights from the vector, meaning we don't need to 
    
    double areaOfBox = 0;
    
    for (int i = 0; i < features.size(); i++) {
        
        // CHANGE THIS NAMES
        double singleError = (((weight * features[i]) - label[i]) * features[i]);
        areaOfBox = areaOfBox + singleError;
    }
     
    double newWeight = weight - (learnRate * areaOfBox);
    weights.push_back(newWeight);
    
    
    // Check if the weight is close to the slope (0.0001 difference)
    // CHANGE BEFORE TEST
    if (weight > 0) {
        
    } else {
        trainOneFeatureHelper(features, label, weights, newWeight);
    }
}


//LIST OF WHAT NEEDS TO BE DONE
//1. INITIALIZE UPDATED WEIGHT VECTOR FOR NEW WEIGHTS IN LOOP
//2. USE OLD WEIGHT TO CALCULATE NEW ONE
//3. CHECK FOR CONVERGENCE - IF YES, STOP, IF NOT, RECURSION
