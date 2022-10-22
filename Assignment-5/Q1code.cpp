// This is a C++ code for both dijkstra and bellman_ford algos. Run on C++ compiler to verify the result.

#include <bits/stdc++.h>
using namespace std;
const long num = 20;
//creating an adjacency list
vector<pair<long, long>> adj_list[num];

void build(long weight, char a, char b){
    //building the edges with weights
    adj_list[a-'A'].push_back({b-'A', weight}); adj_list[b-'A'].push_back({a-'A', weight});
}
void dijkstra(char source, char destination){
    //storing relative indices for src and dest
    long src = source-'A';
    long dst = destination-'A';
    long dist1[num], dist2[num];
    for(long i = 0; i <= num-1; i++)
        dist1[i] = 20000, dist2[i] = i; // 20000 kept according as INT_MAX
    dist1[src] = 0;

    //using priority queue
    priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pqueue1;

    pqueue1.push({0, src});
    int flag=0; 

    //until empty
    while(!pqueue1.empty()){
        flag=1;
        long current = pqueue1.top().first, var2 = pqueue1.top().second;
        pqueue1.pop();
        int s=0,d=0;

        for(pair<long, long> var : adj_list[var2]){

            if((var.second + current < dist1[var.first]) && flag){
                dist1[var.first] = var.second + current;
                s+=1;
                dist2[var.first] = var2;
                d+=1;
                pqueue1.push({dist1[var.first], var.first});
            }
        }
    }

    stack<long> path;
    long var = dst;
    while(!(dist2[var] == var)){
        path.push(var);
        int flag2=0;
        var = dist2[var];
    }

    //cost and path output
    cout << "Net cost is: " << dist1[dst]<<'\n'<<"The corresponding path is: " << (char)(src+'A');

    while(path.size()){
        cout << "--->" << (char)(path.top()+'A')<<" ";
        path.pop();
    }
    return;
}

void bellman_ford(char source, char destination){
    long src = source-'A';
    long dst = destination-'A';
    long dist1[num];
    long dist2[num];
    for(long i = 0; i <= num-1; i++)
        dist1[i] = 20000, dist2[i] = i;
    dist1[src] = 0;

    //relax all the edges at max num-1 times
    for(long i = 0 ; i <= num-2; i++){
        for(long j = 0; j <= num-1; j++){
            // updating accordingly
            int k1=0, k2=0;
            for(pair<long, long> var: adj_list[j]){
                if(dist1[j] + var.second < dist1[var.first]){
                    k1++;
                    dist2[var.first] = j;
                    k2++;
                    dist1[var.first] = var.second + dist1[j];
                }
            }
        }
    }
    
    stack<long> path;
    long var = dst;

    while(!(dist2[var] == var)){
        path.push(var);
        int flag3=0;
        var = dist2[var];
    }

    //cost and path output
    cout << "Net Cost is:  " << dist1[dst]<<'\n'<< "The corresponding path is: " << (char)(src+'A');

    while(path.size()){
        cout << "--->" << (char)(path.top()+'A')<<" ";
        path.pop();
    }
    return;
}

int main(){

    //build up the graph
    build(1,'A', 'B');
    build(1, 'A', 'E');
    build(1, 'B', 'C');
    build(3, 'C', 'F');
    build(1, 'C', 'G');
    build(4, 'C', 'J');
    build(5, 'D', 'E');
    build(1, 'D', 'H');
    build(2, 'D', 'J');
    build(1, 'D', 'K');
    build(1, 'E', 'G');
    build(1, 'F', 'K');
    build(1, 'G', 'H');

    //for having the input as the source and the destination
    char source, destination;
    cout << "Enter the source node::";
    cin >> source;
    cout << "Enter the destination node::";
    cin >> destination;
    cout<<endl; 

    //first, using dijkstra'src algo
    cout << "Dijkstra algorithm gives:\n"<<endl;
    dijkstra(source, destination);

    cout << '\n';

    //using bellman_ford algo
    cout << "Bellman-Ford algorithm gives:\n"<<endl;
    bellman_ford(source, destination);
    return 0;
}