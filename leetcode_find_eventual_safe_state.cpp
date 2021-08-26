class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int s = graph.size();
        vector<int> visited(s, 0);
        vector<int> res;
        for(int v = 0;v < s;v++) {
            dfs(visited, graph, v);
        }
        for(int v = 0;v < s;v++) {
            if(visited[v] == 2){
                res.push_back(v);
            }
        }
        return res;
    }
    bool dfs(vector<int> &visited,vector<vector<int>>& graph,int i) {
        if(visited[i] == 2){
            return true;
        }
        
        if(visited[i] == 1){
            return false;
        }
        visited[i] = 1;
        for(auto v : graph[i]) {
            if(!dfs(visited,graph,v)) {
                return false;
            }
        }
        visited[i] = 2;
        return true;
    }
};