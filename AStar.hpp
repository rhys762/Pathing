
#include <vector>
#include <map>
#include <set>
#include <algorithm>

/*
 *	Rhys Trueman || 10/7/2020
 *	General purpose pathfinding
 *	start and goal are the respective start and goal of the pathfind
 *	double heuristic(Node * n) returns an estimate of how much further it is from n to goal
 *	double edge_cost(Node * a, Node * b) returns the cost of moving from a to b, this is only ever called when b is given as a neighbor to a (see below)
 *	neighbors(Node * n) returns a container with (pointers to) all nodes directly reachable from n, this container must have begin() and end() defined
 */

//helper functions:
//reconstruct the path from the came from map
template<typename Node>
std::vector<Node*> reconstruct_path(Node * goal, std::map<Node*, Node*> & cf);
//remove the node in open set  with the smallest f_score and return it
template<typename Node>
Node * pop_open_set(std::vector<Node*> & os, std::map<Node*,double> & fs);
//returns true if the node has a known g score
template<typename Node>
bool has_known_g_score(Node * n, std::map<Node*, double> & gs);

template<typename Node, typename H, typename E, typename N>
std::vector<Node*> AStar(Node * start, Node * goal, H heuristic, E edge_cost, N neighbors)
{
	//the set of nodes discovered but not explored
	std::vector<Node*> open_set;
       	open_set.push_back(start);

	//came_from[i] = j indicates we traversed j to i
	std::map<Node*, Node*> came_from;
	came_from[start] = nullptr;

	//g_score[Node * n] indicates how far we have actually travelled to get to n
	std::map<Node*, double> g_score;
	g_score[start] = 0.0;

	//f_score[Node * n] is the sum of g_score[n] and the estimated cost of reaching goal
	std::map<Node*, double> f_score;
	f_score[start] = heuristic(start);

	//while we have nodes to explore:
	while(open_set.size())
	{
		Node * current = pop_open_set(open_set, f_score);
		//if the next node is the goal, reconstruct the path and return
		if(current == goal)
		{
			return reconstruct_path(goal, came_from);
		}

		//for each node we can reach from current:
		for(auto n : neighbors(current))
		{
			//calculate a temp g score, ie the cost of getting to neighbor through current
			double tentative_gscore = g_score[current] + edge_cost(current, n);

			if(!has_known_g_score(n, g_score) || tentative_gscore < g_score[n])
			{
				came_from[n] = current;
				g_score[n] = tentative_gscore;
				f_score[n] = g_score[n] + heuristic(n);
				//if neighbor not in openset add it to openset
				if(std::find(open_set.begin(), open_set.end(), n) == open_set.end())
				{
					open_set.push_back(n);
				}
			}
		}

	}

	//failure, return empty vector
	return std::vector<Node*>();
}

//reconstruct the path from the came from map
template<typename Node>
std::vector<Node*> reconstruct_path(Node * goal, std::map<Node*, Node*> & cf)
{
	Node * current = goal;
	std::vector<Node*> path;

	while(cf[current] != nullptr)
	{
		path.push_back(current);
		current = cf[current];
	}	
	return path;
}

//remove the node in open set  with the smallest f_score and return it
template<typename Node>
Node * pop_open_set(std::vector<Node*> & os, std::map<Node*,double> & fs)
{
	size_t min_index = 0;

	for(size_t i = 1; i < os.size(); i++)
	{
		if(fs[os[i]] < fs[os[min_index]])
		{
			min_index = i;
		}
	}

	Node * min_node = os[min_index];
	os.erase(os.begin() + min_index);
	return min_node;
}

//returns true if the node has a known g score
template<typename Node>
bool has_known_g_score(Node * n, std::map<Node*, double> & gs)
{
	try
	{
		gs.at(n);
	}
	catch(...)
	{
		return false;
	}
	return true;
}
