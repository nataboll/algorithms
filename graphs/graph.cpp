#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;


class Vertex {

public:
        enum Color {
        	WHITE,
                GRAY,
                BLACK,
        };

private:
	int num;
	int in_time;
	int out_time;
	Color color;
	vector<int> neighbors;

public:
	Vertex() {
		color = WHITE;
		in_time = 0;
		out_time = 0;
	}

	void set_status_not_visited() {
		color = WHITE;	
	}

	void set_status_in_process() {
		color = GRAY;
	}

	void set_status_visited() {
		color = BLACK;
	}

	bool is_not_visited(){
		return (color == WHITE);
	}

	bool is_in_process(){
		return (color == GRAY);
	}

	bool is_visited(){
		return (color == BLACK);
	}

	void set_num(int i) {
		num = i;
	}

	int get_num() {
		return num;
	}

	int get_in_time() {
		return in_time;
	}

	void set_in_time(int i) {
		in_time=i;
	}
	
	int get_out_time() {
		return out_time;
	}

	void set_out_time(int i) {
		out_time=i;
	}

	void add_neighbor(int i) {
		neighbors.push_back(i);
	}

	vector<int> get_neighbors() {
		return neighbors;
	}
};


class Graph {
	int n; // num of vertexes
	int m; // num of edges
	vector<vector<int>> g;	
	Vertex *vertexes;
	int *dfs_seq; // sequence of vertexes' numbers, got "black" in DFS
	int *dfs_in_times;
	int *dfs_out_times;
	int *bfs_seq; // sequence of vertexes' numbers, got "black" in BFS
	int *bfs_in_times;
	int *bfs_out_times;
	int cur_time;
	int num_of_v; // vertexes counter

public:
	Graph() {
		set_g();
		cur_time = 0;
		num_of_v = 0;
	}

	~Graph() {
		delete[] vertexes;
		delete[] dfs_seq;
		delete[] dfs_in_times;
		delete[] dfs_out_times;
		delete[] bfs_seq;
		delete[] bfs_in_times;
		delete[] bfs_out_times;
	}

private:
	void set_g() {
		cout << "Enter num of vertexes: " << endl;
		cin >> n;
		cout << "Enter num of edges: " << endl;
		cin >> m;
		vertexes = new Vertex[n];

		for (int i = 0; i < m; i++) {
			cout << "edge " << i << ": ";
			int out_ver = 0, in_ver = 0;
			cin >> out_ver >> in_ver;
			if (out_ver >= n || in_ver >= n) {
				cout << "Don't joke on me ..." << endl;
				i--;
				continue;
			}
			vertexes[out_ver].add_neighbor(in_ver);
		}

		for (int i = 0; i < n; i++) {
			vertexes[i].set_num(i);
			g.push_back(vertexes[i].get_neighbors());
		}

		dfs_seq = new int[n];
		dfs_in_times = new int[n];
		dfs_out_times = new int[n];
		bfs_seq = new int[n];
                bfs_in_times = new int[n];
                bfs_out_times = new int[n];
	}

	void set_status_all_not_visited() {
		for (int i = 0; i < n; i++) {
			vertexes[i].set_status_not_visited();
		}
		cur_time = 0;
		num_of_v = 0;
	}

public:
	void print_g() {
		for (int i = 0; i < n; i++) {
			cout << "Vertex " << i << ": ";
			const vector<int> &to_print = vertexes[i].get_neighbors();
			for (int j = 0; j < to_print.size(); j++) {
				cout << to_print[j] << endl;
			}
		}
		cout << endl;
	}

	void dfs() {
		set_status_all_not_visited();
		for (int s = 0; s < n; s++) {
			if (vertexes[s].is_not_visited()) {
				dfs_visit(s);
			}
		}
	}

private:
	void dfs_visit(int s) {
		vertexes[s].set_in_time(++cur_time);
		vertexes[s].set_status_in_process();
		const vector<int> &neigh = vertexes[s].get_neighbors();
		for(int i = 0; i < neigh.size(); i++){
			if (vertexes[neigh[i]].is_not_visited()){
				dfs_visit(vertexes[neigh[i]].get_num());
			}
		}
		vertexes[s].set_status_visited();
		dfs_seq[num_of_v++] = s;
		vertexes[s].set_out_time(++cur_time);
	}

        void set_dfs_in_times(){
        	for (int i = 0; i < n; i++){
                        dfs_in_times[i] = vertexes[i].get_in_time();
                }
        }

	void set_dfs_out_times(){
		for (int i = 0; i < n; i++){
			dfs_out_times[i] = vertexes[i].get_out_time();
		}
	}

public:
	void print_info_dfs(){
		cout << "DFS sequence: ";
		for (int i = 0; i < n; i++){
			cout << dfs_seq[i] << ' ' ;
		}
		cout << endl;
		set_dfs_in_times();
		set_dfs_out_times();

		cout << "DFS In\\Out times: ";
		for (int i = 0; i < n; i++){
                        cout << "Vertex " << i << ": " << dfs_in_times[i] << '\\' << dfs_out_times[i] << endl;
                }
	}

	void bfs(){
		set_status_all_not_visited();
		for (int s = 0; s < n; s++){
			if (vertexes[s].is_not_visited()){
				queue<int> q;
				q.push(s);
				vertexes[s].set_status_in_process();
				vertexes[s].set_in_time(++cur_time);
				while(!q.empty()){
					int u;
					u = q.front();
					vertexes[u].set_status_visited(); 
					bfs_seq[num_of_v++] = u;
					q.pop();
					vertexes[u].set_out_time(++cur_time);
					vector<int> to_add = vertexes[u].get_neighbors();
					for (int i = 0; i < to_add.size(); i++){
						if (vertexes[to_add[i]].is_not_visited()){
							q.push(vertexes[to_add[i]].get_num());
							vertexes[to_add[i]].set_status_in_process();
							vertexes[to_add[i]].set_in_time(++cur_time);
						}
					}	
				}
			}
		}
	}

private:
	void set_bfs_in_times(){
                for (int i = 0; i < n; i++){
                        bfs_in_times[i] = vertexes[i].get_in_time();
                }
        }

        void set_bfs_out_times(){
                for (int i = 0; i < n; i++){
                        bfs_out_times[i] = vertexes[i].get_out_time();
                }
        }

public:
	void print_info_bfs(){
                cout << "BFS sequence: ";
                for (int i = 0; i < n; i++){
                        cout << bfs_seq[i] << ' ' ;
                }
                cout << endl;
                set_bfs_in_times();
                set_bfs_out_times();

                cout << "BFS In\\Out times: ";
                for (int i = 0; i < n; i++){
                        cout << "Vertex " << i << ": " << bfs_in_times[i] << '\\' << bfs_out_times[i] << endl;
                }
        }
};

int main() {
	Graph g;
//	g.print_g();
	g.dfs();	
	g.print_info_dfs();
	g.bfs();
	g.print_info_bfs();
	return 0;
}

