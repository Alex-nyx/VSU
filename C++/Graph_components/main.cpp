#include<iostream>
#include<vector>
#include<forward_list>

using namespace std;

using uint = unsigned int;

using adj_list = forward_list<uint>;
using Graph = vector<adj_list>;
using Components = vector<forward_list<uint>>;

void init_graph(Graph&);
void add_edge(Graph&, uint const, uint const);
void show(Graph const&);
void show_components(Components const&);

Components find_comps(Graph const&);
Components find_comps(Graph const&, uint const);

void dfs(Graph const&, vector<uint>&, uint const, uint const);
void dfs(Graph const&, vector<uint>&, uint const, uint const, uint const);

int main()
{
    Graph graph;
    init_graph((graph));

    cout << "The origin graph: " << endl;
    show(graph);

    Components origin_g = find_comps(graph);
    cout << endl << "The connected components in origin graph:" << endl;
    show_components(origin_g);

    for (uint vertex_to_skip = 0; vertex_to_skip < graph.size(); ++vertex_to_skip)
    {
        Components comps = find_comps(graph, vertex_to_skip);

        if(comps.size() >= origin_g.size())
        {
            cout << endl << "The connected components in graph without vertex <" << vertex_to_skip << ">" << endl;
            show_components(comps);
        }
    }

    cin.get();
}

void dfs(Graph const& graph, vector<uint>& used, uint const vertex, uint const comps_cnt)
{
    used[vertex] = comps_cnt;

    for(uint v : graph[vertex])
    {
        if(!used[v])
        {
            dfs(graph, used, v, comps_cnt);
        }
    }
}

void dfs(Graph const& graph, vector<uint>& used, uint const vertex, uint const comps_cnt, uint const vertex_to_skip)
{
    used[vertex] = comps_cnt;

    for(uint v : graph[vertex])
    {
        if(v == vertex_to_skip)
        {
            continue;
        }
        else if(!used[v])
        {
            dfs(graph, used, v, comps_cnt, vertex_to_skip);
        }
    }
}

Components find_comps(Graph const& graph)
{
    vector<uint> used(graph.size());

    uint comps_cnt = 0;
    for(uint vertex = 0; vertex < graph.size(); ++vertex)
    {
        if(!used[vertex])
        {
            dfs(graph, used, vertex, ++comps_cnt);
        }
    }

    Components comps(comps_cnt);

    for(uint vertex = 0; vertex < graph.size(); ++vertex)
    {
        comps[used[vertex] - 1].push_front(vertex);
    }

    return comps;
}

Components find_comps(Graph const& graph, uint const vertex_to_skip)
{
    vector<uint> used(graph.size());

    uint comps_cnt = 0;
    for(uint vertex = 0; vertex < graph.size(); ++vertex)
    {
        if(vertex == vertex_to_skip)
        {
            continue;
        }
        else if(!used[vertex])
        {
            dfs(graph, used, vertex, ++comps_cnt, vertex_to_skip);
        }
    }

    Components comps(comps_cnt);

//    cout << "\nUsed:\n";
//    for (auto x : used)
//        cout << x << endl;

    for(uint vertex = 0; vertex < graph.size(); ++vertex)
    {
        if(vertex != vertex_to_skip)
        {
            comps[used[vertex] - 1].push_front(vertex);
        }
    }

    return comps;
}


void init_graph(Graph& graph)
{
    uint vertex_num = 0;
    uint edge_num = 0;

    cout << "Number of vertex: ";
    cin >> vertex_num;
    cout << "Number of edges: ";
    cin >> edge_num;

    graph.resize(vertex_num);

    cout << "Edges (first vertex, second vertex):" << endl;
    for (uint i = 0; i < edge_num; ++i)
    {
        uint first_v, second_v;
        cin >> first_v >> second_v;
        add_edge(graph,first_v, second_v);
    }

    for(adj_list& adj_l : graph)
    {
        adj_l.sort();
        adj_l.unique();
    }
}

void add_edge(Graph& g, uint const v, uint const u)
{
    if(u == v)
    {
        return;
    }

    g[v].push_front(u);
    g[u].push_front(v);
}

void show(Graph const& g)
{
    for(uint i = 0; i < g.size(); ++i)
    {
        cout << i << " : ";
        if(!g[i].empty())
        {
            for(auto it : g[i])
            {
                cout << " <" << it << "> ";
            }
            cout << endl;
        }
        else
        {
            cout << "no edges" << endl;
        }
    }
}

void show_components(Components const& c)
{
    for(uint comp = 0; comp < c.size(); ++comp)
    {
        cout << "Component " << comp << " :" << endl;
        cout << "    ";
        for (auto v : c[comp])
        {
            cout << " <" << v << "> ";
        }
        cout << endl;
    }
}













