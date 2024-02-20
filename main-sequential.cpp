#include <iostream>
#include <cstdlib>
#include <vector>
#include "omp.h"
#include "commonFunction.cpp"


using namespace std;


vector<Point> kMeans(vector<Point> &data, int k, int maxIterations) {
    int dimension = data[0].coordinate.size();
    vector<Point> centroids = randomCentroid(k, dimension, data);

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<Point> newCentroids = allZerosCentroid(k, dimension);
        vector<int> counts(k, 0);

        for (int i = 0; i < data.size(); i++) {
            double minDistance = euclideanDistance(data[i], centroids[0]);
            int clusterIdx = 0;
            for (int j = 1; j < centroids.size(); j++) {
                double distance = euclideanDistance(data[i], centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    clusterIdx = j;
                }
            }
            data[i].actualCentroid = clusterIdx;
            for (int c = 0; c < dimension; c++) {
                newCentroids[clusterIdx].coordinate[c] += data[i].coordinate[c];
            }
            counts[clusterIdx]++;
        }

        for (size_t i = 0; i < newCentroids.size(); ++i) {
            for (int c = 0; c < dimension; c++) {
                newCentroids[i].coordinate[c] = newCentroids[i].coordinate[c] / counts[i];
            }
        }

        /*
        if (areEqual(centroids, newCentroids)) {
            return centroids;
        }
        */
        centroids = newCentroids;
    }

    return centroids;
}


int main() {
    int seed = 17;
    srand(seed);
    int maxIterations = 100;
    int k = 4;

    vector<Point> data = loadDataset("../input/worldcities_mod.csv");

    double dtime = omp_get_wtime();
    vector<Point> centroids = kMeans(data, k, maxIterations);
    dtime = omp_get_wtime() - dtime;
    cout << "Execution time: " << dtime << " seconds" << endl;

    writeCSV(centroids,
             "../output/centroids/sequential_" + to_string(k) + "_" + to_string(seed) + "_" + to_string(data.size()) +
             ".csv");
    writeCSV(data,
             "../output/clusters/sequential_" + to_string(k) + "_" + to_string(seed) + "_" + to_string(data.size()) +
             ".csv");

    return 0;
}