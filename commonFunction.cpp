#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

struct Point{
    double x,y;
};

using namespace std;

double euclideanDistance(Point p1, Point p2) {
    double dist = 0;
    dist += pow(p2.x-p1.x,2);
    dist += pow(p2.y-p1.y,2);
    return sqrt(dist);
}

bool areEqual(const std::vector<Point>& p1, const std::vector<Point>& p2) {
    if (p1.size() != p2.size())
        return false;
    for (int i = 0; i < p1.size(); i++) {
        if (p1[i].x != p2[i].x || p1[i].y != p2[i].y)
            return false;
    }
    return true;
}

vector<Point> loadDataset(const string& path){

    vector<Point> data;
    ifstream file(path);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Point p{};

        getline(ss, temp, ',');
        getline(ss, temp, ',');
        getline(ss, temp, ',');
        getline(ss, temp, ',');
        getline(ss, temp, ',');

        getline(ss, temp, ',');
        double latitude = stod(temp);
        p.x = latitude;

        getline(ss, temp, ',');
        double longitude = stod(temp);
        p.y = longitude;

        data.push_back(p);
    }

    return data;
}
