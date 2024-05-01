#include <iostream>
#include <vector>
#include "omp.h"
#include "commonFunction.cpp"

using namespace std;

vector<Point> kMeans(vector<Point> &data, vector<Point> &centroids, int k, int maxIterations) {

    vector<Point> newCentroids = allZerosCentroid(k, DIM);

    for (int iter = 0; iter < maxIterations; ++iter) {
        vector<int> counts(k, 0);
        newCentroids = allZerosCentroid(k, DIM);

        for (int i = 0; i < data.size(); i++) {
            double minDistance = distance(data[i], centroids[0]);
            int clusterIdx = 0;

            for (int j = 1; j < centroids.size(); j++) {
                if (distance(data[i], centroids[j]) < minDistance) {
                    minDistance = distance(data[i], centroids[j]);
                    clusterIdx = j;
                }
            }
            data[i].actualCentroid = clusterIdx;
            for (int c = 0; c < DIM; c++) {
                newCentroids[clusterIdx].coordinate[c] += data[i].coordinate[c];
            }

            counts[clusterIdx]++;

        }

        for (size_t i = 0; i < newCentroids.size(); ++i) {
            newCentroids[i].actualCentroid = counts[i];
            for (double &c: newCentroids[i].coordinate) {
                if (counts[i] != 0)
                    c = c / counts[i];
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

int runSingleTest(bool output, vector<Point> data, const int k, int n, int maxIterations) {

    //vector<Point> centroids = randomCentroid(k, data);
    vector<Point> centroids = initialization_kmean_seq(data, k);

    double sum_time = 0;
    for (int i = 0; i < n; ++i) {
        double dtime = omp_get_wtime();
        centroids = kMeans(data, centroids, k, maxIterations);
        dtime = omp_get_wtime() - dtime;
        sum_time += dtime;
    }
    sum_time = sum_time / n;

    cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " Execution time sequential: " << sum_time
         << " seconds" << endl;
    writeResult(to_string(data.size()), to_string(k), 1, sum_time, "../Times/Times_Sequential.txt");

    if (output) {
        writeCSV(centroids, "../output/centroids/sequential_" + to_string(k) + "_" + to_string(data.size()) + ".csv");
        writeCSV(data, "../output/clusters/sequential_" + to_string(k) + "_" + to_string(data.size()) + ".csv");
    }
    return 0;
}

int runSingleTest_initialization(bool output, vector<Point> data, const int k, int n) {

    double sum_time = 0;
    for (int i = 0; i < n; ++i) {
        double dtime = omp_get_wtime();
        vector<Point> centroids = initialization_kmean_seq(data, k);
        dtime = omp_get_wtime() - dtime;
        sum_time += dtime;
    }
    sum_time = sum_time / n;

    cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " Execution time sequential initialization: "
         << sum_time << " seconds" << endl;

    if (output)
        writeResult(to_string(data.size()), to_string(k), 1, sum_time, "../Times/Times_Kmeans_Sequential.txt");

    return 0;

}

int runAllTest(bool output, bool type, int n) {

    std::vector<std::string> file_names = {"100", "1000", "10000", "100000", "1000000", "10000000"};
    std::vector<int> cen = {3, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    int maxIterations = 100;

    for (const std::string &name: file_names) {
        for (const auto k: cen) {
            vector<Point> data = loadDataset("../input/dataset_" + name + "_" + to_string(k) + ".csv");
            if (type)
                runSingleTest(output, data, k, n, maxIterations);
            else
                runSingleTest_initialization(output, data, k, n);
        }
    }

    return 0;

}

int main() {

    int ret;
    int n_test = 10;

    //vector<Point> data = loadDataset("../input/dataset_" + to_string(100) + "_" + to_string(3) + ".csv");
    // ret = runSingleTest(false, 16, data, 3, n_test, 100);
    // ret = runSingleTest_initialization(false, 16, data, 3, n_test);

    ret = runAllTest(true, false, n_test);

    return ret;
}