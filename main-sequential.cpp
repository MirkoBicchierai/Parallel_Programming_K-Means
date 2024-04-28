#include <iostream>
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
    std::vector<std::string> file_names = {"10000000"}; // "100", "1000", "10000", "100000", "1000000",
    std::vector<int> cen;

    for (int i = 35; i <= 50; ++i) {
        cen.push_back(i);
    }
    int maxIterations = 100;

    for (const std::string &name: file_names) {
        for (const auto k: cen) {
            vector<Point> data = loadDataset("../input/dataset_" + name + "_"+to_string(k)+".csv");
            double dtime = omp_get_wtime();
            vector<Point> centroids = kMeans(data, k, maxIterations);
            dtime = omp_get_wtime() - dtime;
            cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " Execution time sequential: " << dtime<< " seconds" << endl;
            writeResult(to_string(data.size()), to_string(k), 1, dtime, "../Times/Times_Sequential.txt");
            writeCSV(centroids, "../output/centroids/sequential_" + to_string(k) + "_" + to_string(data.size()) + ".csv");
            writeCSV(data, "../output/clusters/sequential_" + to_string(k) + "_" + to_string(data.size()) + ".csv");
        }
    }

    return 0;
}