#include <vector>
#include <iostream>
#include <map>


using namespace std;


int main() {
    vector<int> vec;
    int n = 573;
    while (n--) {
        int v;
        cin >> v;
        vec.push_back(v);
    }

    map<int, int> mp;

    for (auto v : vec)
        mp[v]++;
    for (auto [f, s] : mp)
        cout << f << ": " << s << "\n";
    
}