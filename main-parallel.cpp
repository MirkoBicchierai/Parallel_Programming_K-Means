#include <iostream>
#include <vector>
#include <omp.h>
#include "commonFunction.cpp"
#include <string>

using namespace std;

vector<Point> kMeans(vector<Point>& data, int k, int maxIterations, int threads) {

    int dimension = data[0].coordinate.size();
    vector<Point> centroids=randomCentroid(k,dimension,data);

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<Point> newCentroids = allZerosCentroid(k, dimension);
        vector<int> counts(k, 0);

        #pragma omp parallel num_threads(threads)
        {
            vector<int> tmp_cluster_cardinality(k, 0);
            vector<Point> tmp_newCentroids = allZerosCentroid(k, dimension);

            #pragma omp for nowait schedule(static, data.size() / threads)
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
                for (int c = 0; c<dimension;c++) {
                    tmp_newCentroids[clusterIdx].coordinate[c] += data[i].coordinate[c];
                }
                tmp_cluster_cardinality[clusterIdx]++;
            }

            #pragma omp critical
            {
                for (int i = 0; i < k; i++) {
                    for (int c = 0; c<dimension;c++) {
                        newCentroids[i].coordinate[c] += tmp_newCentroids[i].coordinate[c];
                    }
                    counts[i] += tmp_cluster_cardinality[i];
                }
            }

        }

        for (int i = 0; i < newCentroids.size(); ++i) {
            for (int c = 0; c<dimension;c++) {
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

//TODO relation, presentation, -O3 optmization (only compile)

int main() {
    string file_name = "1000";
    int k = 3;
    int threads = 16;
    int maxIterations = 100;

    vector<Point> data = loadDataset("../input/dataset_"+file_name+".csv");

    double dtime = omp_get_wtime();
    vector<Point> centroids  = kMeans(data,k,maxIterations,threads);
    dtime = omp_get_wtime() - dtime;
    cout << "Execution time: " << dtime << " seconds" << endl;

    writeResult("Parallel", to_string(data.size()), to_string(k), threads, dtime, "../Times/Times.txt");
    writeCSV(centroids, "../output/centroids/parallel_"+to_string(k)+"_"+to_string(data.size())+"_"+to_string(threads)+".csv");
    writeCSV(data, "../output/clusters/parallel_"+to_string(k)+"_"+to_string(data.size())+"_"+to_string(threads)+".csv");

    return 0;
}