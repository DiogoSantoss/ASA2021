int executeBFS(int source){
    for (unsigned int i = 0; i < graph.size(); ++i){
        graph[i].streak = 0;
    }
        
    graph[source].streak = 1;

    queue<int> q = queue<int>();
    q.push(source);

    int u, index, streak = 0, maxStreak = 0;

    while (!q.empty()){
        u = q.front();
        q.pop();
        cout << u;
        for (unsigned int i = 0; i < graph[u].adj.size(); ++i){
            streak = graph[u].streak;
            index = graph[u].adj[i];
            if (streak >= graph[index].streak){
                graph[index].streak = streak + 1;
                if (graph[index].streak > maxStreak)
                    maxStreak = graph[index].streak;
            }
            q.push(index);
        }
    }
    return maxStreak;
}

int executeDFS(int source){

    for(unsigned int i = 0; i < graph.size(); i++){
        graph[i].colour = WHITE;
        graph[i].end = 0;
    }

    int time = 0;

    stack<int> s = stack<int>();
    graph[source].colour = GREY;
    s.push(source);

    while(!q.empty()){
        u = s.top();
        s.pop();

        for(unsigned int i = 0; i<graph[u].size(); i++){
            if(graph[u].adj[i].colour == WHITE){
                graph[u].adj[i].colour = GREY
            }
        }
        graph[u].colour = BLACK;
        //graph[u].end = time+1;
    }


}