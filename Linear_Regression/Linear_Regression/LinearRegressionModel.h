using namespace std;

class LinearRegressionModel {
public:
    LinearRegressionModel(double lr);
    void train(vector < vector < double > >& features, const vector < double >& labels);
    double predict(vector < double >& inputFeatures);
private:
    
};
