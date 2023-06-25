#include <iostream>
#include <vector>

using namespace std;

int numeroDeFormas(vector<string> E, vector<int> p){
    int n = E.size();
    vector<int> dp(n+1, 0);
    dp[0] = 1;

    for(int i = 1; i <= n; i++){
        if(E[i-1] == "roto")
            continue;
        for(int j : p){
            if(j <= i)
                dp[i] += dp[i-j];
        }
    }

    return dp[n];
}

int main(){
    vector<string> E = {"sano", "sano", "sano", "roto", "roto", "sano", "sano", "roto", "sano", "sano"};
    vector<int> p = {1, 2, 4, 8};
    cout << numeroDeFormas(E, p) << endl;

    return 0;
}
