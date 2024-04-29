#include <iostream>
#include <vector>
#include "omp.h"
#include "commonFunction.cpp"

using namespace std;

vector<Point> kMeans(vector<Point> &data, vector<Point> &centroids, int k, int maxIterations) {
    int dimension = data[0].coordinate.size();
    vector<Point> newCentroids = allZerosCentroid(k, dimension);

    for (int iter = 0; iter < maxIterations; ++iter) {
        vector<int> counts(k, 0);
        newCentroids = allZerosCentroid(k, dimension);

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
            newCentroids[i].actualCentroid = counts[i];
            for (int c = 0; c < dimension; c++) {
                if (counts[i] != 0)
                    newCentroids[i].coordinate[c] = newCentroids[i].coordinate[c] / counts[i];
            }
        }


        /*
        if (areEqual(centroids, newCentroids)) {
            return centroids;
        }
        */

        centroids = newCentroids;

        writeCSV(centroids,
                 "../tmp/sequential_cen_I_" + to_string(iter) + "_K_" + to_string(k) + "_" + to_string(data.size()) +
                 ".csv");
        writeCSV(data,
                 "../tmp/sequential_data_I_" + to_string(iter) + "_K_" + to_string(k) + "_" + to_string(data.size()) +
                 ".csv");
    }

    return centroids;
}

int main() {
    std::vector<std::string> file_names = {"100", "1000", "10000", "100000", "1000000", "10000000"}; //
    std::vector<int> cen = {3, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    int maxIterations = 100;

    for (const std::string &name: file_names) {
        for (const auto k: cen) {
            vector<Point> data = loadDataset("../input/dataset_" + name + "_" + to_string(k) + ".csv");
            vector<Point> centroids = randomCentroid(k, data[0].coordinate.size(), data);
            double dtime = omp_get_wtime();
            centroids = kMeans(data, centroids, k, maxIterations);
            dtime = omp_get_wtime() - dtime;
            cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " Execution time sequential: " << dtime
                 << " seconds" << endl;
            writeResult(to_string(data.size()), to_string(k), 1, dtime, "../Times/Times_Sequential.txt");
            writeCSV(centroids,
                     "../output/centroids/sequential_" + to_string(k) + "_" + to_string(data.size()) + ".csv");
            writeCSV(data, "../output/clusters/sequential_" + to_string(k) + "_" + to_string(data.size()) + ".csv");
        }
    }

    return 0;
}