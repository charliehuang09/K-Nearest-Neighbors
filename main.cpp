#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <cmath>
#include <queue>
using namespace std;
struct coord{
    int x;
    int y;
    coord(int x_, int y_){
        x = x_;
        y = y_;
    };
};
class Compare
{
public:
    bool operator() (const pair<float, int> &a, const pair<float, int> &b) const
    {
        return a.first < b.first;
    }
};

class KNN {
private:
    float get_distance(coord a, coord b){
        return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
    }

public:
vector<vector<coord>> data;
int k;
    KNN(vector<vector<coord>> data_, int k_){
        data = data_;
        k = k_;
    }
    int predict(coord input){
        priority_queue<pair<float, int>, vector<pair<float, int>>, Compare> pq;
        for (int i = 0; i < data.size(); i++){
            for (int j = 0; j < data[i].size(); j++){
                pq.push(pair<float, int>(get_distance(input, data[i][j]), i));
                if (pq.size() > k) pq.pop();
            }
        }
        int t[data.size()];
        memset(t, 0, sizeof(t));
        while(!pq.empty()){
            t[pq.top().second]++;
            pq.pop();
        }
        int id, largest = -1;
        for (int i = 0; i < data.size(); i++){
            if (largest < t[i]){
                largest = t[i];
                id = i;
            }
        }
        return id;
    }
};

// Driver code
int main(){
    vector<coord> t;
    vector<vector<coord>> data;
    for (int i = 0; i < 20; i++){
        t.emplace_back(rand() % 20, rand() % 20);
    }
    data.push_back(t);
    t.clear();
    for (int i = 0; i < 20; i++){
        t.emplace_back(rand() % 20 + 40, rand() % 20 + 40);
    }
    data.push_back(t);
    KNN knn(data, 2);
    cout << knn.predict(coord(10, 10)) << "\n";
    cout << knn.predict(coord(100, 100)) << "\n";
    cout << knn.predict(coord(42, 14)) << "\n";
    cout << knn.predict(coord(30, 0)) << "\n";
}