#include <iostream>
#include <vector>
#include <omp.h>
#include "commonFunction.cpp"
#include <string>

using namespace std;

vector<Point> kMeans(vector<Point> &data, vector<Point> &centroids, int k, int maxIterations, int threads) {

    int block = ceil(data.size() / threads);

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<Point> newCentroids = allZerosCentroid(k, DIM);
        vector<int> counts(k, 0);

#pragma omp parallel num_threads(threads)
        {

            vector<int> tmp_cluster_cardinality(k, 0);
            vector<Point> tmp_newCentroids = allZerosCentroid(k, DIM);

#pragma omp for nowait schedule(static, block)
            for (int i = 0; i < data.size(); i++) {
                double minDistance = distance(data[i], centroids[0]);
                int clusterIdx = 0;
                for (int j = 1; j < centroids.size(); j++) {
                    double dist = distance(data[i], centroids[j]);
                    if (dist < minDistance) {
                        minDistance = dist;
                        clusterIdx = j;
                    }
                }
                data[i].actualCentroid = clusterIdx;
                for (int c = 0; c < DIM; c++) {
                    tmp_newCentroids[clusterIdx].coordinate[c] += data[i].coordinate[c];
                }
                tmp_cluster_cardinality[clusterIdx]++;
            }

#pragma omp critical
            {
                for (int i = 0; i < k; i++) {
                    for (int c = 0; c < DIM; c++) {
                        newCentroids[i].coordinate[c] += tmp_newCentroids[i].coordinate[c];
                    }
                    counts[i] += tmp_cluster_cardinality[i];
                }
            }

        }

        for (int i = 0; i < newCentroids.size(); ++i) {
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

int runSingleTest(bool output, const int t, vector<Point> data, const int k, int n, int maxIterations) {

    //vector<Point> centroids = randomCentroid(k, data);
    vector<Point> centroids = initialization_kmean_par(data, k, t);
    double sum_time = 0;
    for (int i = 0; i < n; ++i) {
        double dtime = omp_get_wtime();
        centroids = kMeans(data, centroids, k, maxIterations, t);
        dtime = omp_get_wtime() - dtime;
        sum_time += dtime;
    }
    sum_time = sum_time / n;

    cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " T:" + to_string(t) +
            " Execution time parallel: " << sum_time << " seconds" << endl;

    if (output) {
        writeResult(to_string(data.size()), to_string(k), t, sum_time, "../Times/Times_Parallel.txt");
        writeCSV(centroids,
                 "../output/centroids/parallel_" + to_string(k) + "_" + to_string(data.size()) + "_" +
                 to_string(t) + ".csv");
        writeCSV(data, "../output/clusters/parallel_" + to_string(k) + "_" + to_string(data.size()) + "_" +
                       to_string(t) + ".csv");
    }
    return 0;
}

int runSingleTest_initialization(bool output, const int t, vector<Point> data, const int k, int n) {

    double sum_time = 0;
    for (int i = 0; i < n; ++i) {
        double dtime = omp_get_wtime();
        vector<Point> centroids = initialization_kmean_par(data, k, t);
        dtime = omp_get_wtime() - dtime;
        sum_time += dtime;
    }
    sum_time = sum_time / n;

    cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " T:" + to_string(t) +
            " Execution time parallel initialization: " << sum_time << " seconds" << endl;

    if (output)
        writeResult(to_string(data.size()), to_string(k), t, sum_time, "../Times/Times_Kmeans_Parallel.txt");

    return 0;

}

int runAllTest(bool output,bool type, int n) {

    std::vector<int> threads = {2, 4, 8, 16};
    std::vector<std::string> file_names = {"100", "1000", "10000", "100000", "1000000", "10000000"};
    std::vector<int> cen = {3, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    int maxIterations = 100;

    for (const std::string &name: file_names) {
        for (const auto k: cen) {
            vector<Point> data = loadDataset("../input/dataset_" + name + "_" + to_string(k) + ".csv");
            for (const auto t: threads) {
                if(type)
                    runSingleTest(output,t, data, k, n, maxIterations);
                else
                    runSingleTest_initialization(output,t, data, k, n);
            }
        }
    }

    return 0;

}

int main() {

    int ret;
    int n_test = 10;

    //vector<Point> data = loadDataset("../input/dataset_" + to_string(100) + "_" + to_string(3) + ".csv");
    //ret = runSingleTest(false, 16, data, 3, n_test, 100);
    //ret = runSingleTest_initialization(false, 16, data, 3, n_test);

    ret = runAllTest(true,false, n_test);

    return ret;
}