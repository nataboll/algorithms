#include <iostream>
#include <vector>
#include <memory>
 
 
class Vertex {
 
private:
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
    	std::vector<int> in_neighbors;
    	std::vector<int> out_neighbors;
 
public:
    	typedef std::shared_ptr<Vertex> Ref;
 
    	Vertex(int _num) {
        	num = _num;
        	color = WHITE;
        	in_time = 0;
        	out_time = 0;
    	}
 
    	void unvisit() {
        	color = WHITE; 
    	}
 
    	void process(int _in_time) {
        	color = GRAY;
        	in_time = _in_time;
    	}
 
   	void visit(int _out_time) {
        	color = BLACK;
        	out_time = _out_time;
    	}
 
    	bool is_not_visited() const{
        	return (color == WHITE);
    	}
 
    	bool is_in_process() const{
        	return (color == GRAY);
    	}
 
    	bool is_visited() const{
        	return (color == BLACK);
    	}
 
    	int get_num() const{
        	return num;
    	}
 
    	int get_in_time() const {
        	return in_time;
    	}
 
    	int get_out_time() const {
        	return out_time;
    	}
 
    	void add_in_neighbor(int i) {
        	in_neighbors.push_back(i);
    	}
 
    	std::vector<int> get_in_neighbors() const {
        	return in_neighbors;
    	}
 
    	void add_out_neighbor(int i) {
        	out_neighbors.push_back(i);
    	}
 
    	std::vector<int> get_out_neighbors() const {
        	return out_neighbors;
    	}
};
 
 
class Graph {
    	std::vector<Vertex::Ref> vertexes;
    	std::vector<int> dfs_seq; // sequence of vertexes' numbers, got "black" in DFS
    	std::vector<int> component_number;
    	int csrj_num = 0;
private:
    	int cur_time = 0;
    	int num_of_v = 0; // vertexes counter
 
public:
    	Graph(int n, int m)
        	: vertexes(n)
        	, dfs_seq(n)
        	, component_number(n)
    	{
        	for (int i = 0; i < n; i++) {
        	    	vertexes[i] = std::shared_ptr<Vertex>(new Vertex(i));
        	}
 
        	for (int i = 0; i < m; i++) {
            		int out_ver = 0, in_ver = 0;
            		std::cin >> out_ver >> in_ver;
            		vertexes[--out_ver]->add_out_neighbor(--in_ver);
            		vertexes[in_ver]->add_in_neighbor(out_ver);
        	}
    	}
 
private:
    	void reset() {
        	for (auto vertex : vertexes) {
            		vertex->unvisit();
        	}
        	cur_time = 0;
        	num_of_v = 0;
    	}
 
public:
    	void dfs() {
        	reset();
        	for (auto vertex : vertexes) {
            		if (vertex->is_not_visited()) {
                		dfs_visit(vertex->get_num());
            		}
        	}
    	}
 
private:
    	void dfs_visit(int s) {
        	vertexes[s]->process(++cur_time);
        	for (auto neighbor : vertexes[s]->get_out_neighbors()) {
            		if (vertexes[neighbor]->is_not_visited()){
                		dfs_visit(neighbor);
            		}
        	}
        	vertexes[s]->visit(++cur_time);
        	dfs_seq[num_of_v] = s;
        	num_of_v++;
    }
 
	void transposed_dfs_visit(int s, int *counter_ptr) {    // makes dfs_visit from given vertex in transposed graph
        	vertexes[s]->process(++cur_time);
		for (auto neighbor : vertexes[s]->get_in_neighbors()) {
                        if (vertexes[neighbor]->is_not_visited()){
                		component_number[neighbor] = *counter_ptr;
                		transposed_dfs_visit(neighbor, counter_ptr);
                        }
                }
                vertexes[s]->visit(++cur_time);
	}
 
public:
	void cosaraju() {
        	dfs();
        	reset();
        	int counter = 0;
        	int *counter_ptr = &counter;
        	for (int i = dfs_seq.size() - 1; i >= 0; i--) {
            		if (vertexes[dfs_seq[i]]->is_not_visited()) {
                		(*counter_ptr)++;
                		component_number[dfs_seq[i]] = *counter_ptr;
                		transposed_dfs_visit(dfs_seq[i], counter_ptr);
            		}
        	}
        	csrj_num = *counter_ptr;
    	}
 
    	void print_components() {
        	std::cout << csrj_num << std::endl;
        	for (int i = 0; i < vertexes.size(); i++) {
            	std::cout << component_number[i] << " ";
        	}
        	std::cout << std::endl;
    	}
};
 
int main() {
    	int n, m = 0;
    	std::cin >> n >> m;
    	Graph g(n, m);
    	g.cosaraju();
    	g.print_components();
    	return 0;
}
 
