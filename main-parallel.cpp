#include <iostream>
#include <vector>
#include <omp.h>
#include "commonFunction.cpp"
#include <string>

using namespace std;

vector<Point> kMeans(vector<Point> &data, vector<Point> &centroids, int k, int maxIterations, int threads) {

    int dimension = data[0].coordinate.size();
    int block = ceil(data.size() / threads);

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<Point> newCentroids = allZerosCentroid(k, dimension);
        vector<int> counts(k, 0);

#pragma omp parallel num_threads(threads)
        {

            vector<int> tmp_cluster_cardinality(k, 0);
            vector<Point> tmp_newCentroids = allZerosCentroid(k, dimension);

#pragma omp for nowait schedule(static, block)
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
                    tmp_newCentroids[clusterIdx].coordinate[c] += data[i].coordinate[c];
                }
                tmp_cluster_cardinality[clusterIdx]++;
            }

#pragma omp critical
            {
                for (int i = 0; i < k; i++) {
                    for (int c = 0; c < dimension; c++) {
                        newCentroids[i].coordinate[c] += tmp_newCentroids[i].coordinate[c];
                    }
                    counts[i] += tmp_cluster_cardinality[i];
                }
            }

        }

        for (int i = 0; i < newCentroids.size(); ++i) {
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
    }

    return centroids;
}

int main() {
    std::vector<int> threads = {2, 4, 8, 16};
    std::vector<std::string> file_names = { "100", "1000", "10000"}; // ,....., "100000", "1000000", "10000000"
    std::vector<int> cen = {3, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    int maxIterations = 100;

    for (const std::string &name: file_names) {
        for (const auto k: cen) {
            for (const auto t: threads) {
                vector<Point> data = loadDataset("../input/dataset_" + name + "_" + to_string(k) + ".csv");
                vector<Point> centroids = randomCentroid(k, data[0].coordinate.size(), data);
                double dtime = omp_get_wtime();
                centroids = kMeans(data, centroids, k, maxIterations, t);
                dtime = omp_get_wtime() - dtime;
                cout << "D:" + to_string(data.size()) + " K:" + to_string(k) + " T:" + to_string(t) + " Execution time parallel: " << dtime << " seconds" << endl;
                writeResult(to_string(data.size()), to_string(k), t, dtime, "../Times/Times_Parallel.txt");
                writeCSV(centroids,"../output/centroids/parallel_" + to_string(k) + "_" + to_string(data.size()) + "_" + to_string(t) + ".csv");
                writeCSV(data, "../output/clusters/parallel_" + to_string(k) + "_" + to_string(data.size()) + "_" +  to_string(t) + ".csv");
            }
        }
    }

    return 0;
}