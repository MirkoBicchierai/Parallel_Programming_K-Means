#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <chrono>
#include "commonFunction.cpp"

using namespace std;

double euclideanDistance(Point p1, Point p2) {
    double dist = 0;
    dist += pow(p2.x-p1.x,2);
    dist += pow(p2.y-p1.y,2);
    return sqrt(dist);
}

bool areEqual(const std::vector<Point>& vec1, const std::vector<Point>& vec2) {
    if (vec1.size() != vec2.size()) // If sizes are different, vectors are not equal
        return false;

    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i].x != vec2[i].x || vec1[i].y != vec2[i].y) // If any corresponding elements differ, vectors are not equal
            return false;
    }

    return true; // Vectors are equal
}


vector<Point> kMeans(const vector<Point>& data, int k, int maxIterations) {

    vector<Point> centroids(k, {0, 0});
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[rand() % data.size()];
    }

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<int> clusters(data.size(), 0);

        #pragma omp parallel for schedule(static, data.size() / 16)
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
            clusters[i] = clusterIdx;
        }

        vector<Point> newCentroids(k, {0,0});
        vector<int> counts(k, 0);

        for (int i = 0; i < data.size(); i++) {
            int clusterIdx = clusters[i];
            newCentroids[clusterIdx].x += data[i].x;
            newCentroids[clusterIdx].y += data[i].y;
            counts[clusterIdx]++;
        }

        for (size_t i = 0; i < newCentroids.size(); ++i) {
            newCentroids[i].x = newCentroids[i].x / counts[i];
            newCentroids[i].y = newCentroids[i].y / counts[i];
        }

        if (areEqual(centroids, newCentroids)) {
            return centroids;
        }
        centroids = newCentroids;
    }

    return centroids;
}

int main() {

    srand(17);
    int maxIterations = 100;
    int k = 2;
    vector<Point> data = loadDataset("/home/mirko/CLionProjects/Parallel-Programming/worldcities.csv");
    auto start = chrono::high_resolution_clock::now();
    vector<Point> centroids  = kMeans(data,k,maxIterations);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " millisecond" << endl;

    cout<<"CENTROIDS:"<<endl;
    for(auto centroid:centroids)
        cout<<centroid.x<<" "<<centroid.y<<endl;

    return 0;
}