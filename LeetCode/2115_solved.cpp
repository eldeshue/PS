#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <algorithm>
#include <unordered_map>
#include <string>
#include <queue>

class Solution {
private:
public:
	vector<string> findAllRecipes(vector<string>& recipes,
		vector<vector<string>>& ingredients, vector<string>& supplies)
	{
		unordered_map<string, int> str_to_id;
		vector<string> id_to_str;
		vector<int> inbound_cnt;
		int id = 0;

		// build graph, pre processing
		vector<vector<int>> graph;
		auto AddNewNode = [&](std::string const& str) {
			str_to_id[str] = id;
			id_to_str.push_back(str);
			graph.push_back(vector<int>());
			inbound_cnt.push_back(0);
			++id;
			};

		// add nodes
		for (auto const& str : recipes)
		{
			AddNewNode(str);
		}
		for (int i = 0; i < ingredients.size(); ++i)
		{
			int const target_id = str_to_id[recipes[i]];
			for (auto const& str : ingredients[i])
			{
				if (str_to_id.count(str) == 0)
					AddNewNode(str);
				// build graph
				graph[str_to_id[str]].push_back(target_id);
				++inbound_cnt[target_id];
			}
		}

		// topology sort
		queue<int> q;
		for (auto const& str : supplies)
		{
			if (str_to_id.count(str) == 0)
				AddNewNode(str);
			q.push(str_to_id[str]);
		}
		vector<bool> visited(graph.size(), false);
		while (!q.empty())
		{
			int const cur_node_id = q.front();
			q.pop();

			for (int const next_node_id : graph[cur_node_id])
			{
				if (!visited[next_node_id])
				{
					--inbound_cnt[next_node_id];
					if (inbound_cnt[next_node_id] == 0)
					{
						visited[next_node_id] = true;
						q.push(next_node_id);
					}
				}
			}
		}

		// result
		vector<string> result;
		for (int i = 0; i < graph.size(); ++i)
		{
			if (visited[i])
				result.push_back(id_to_str[i]);
		}
		return result;
	}
};

