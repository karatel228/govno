#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <set>
#include <array>
#include <algorithm> 


using namespace std;

struct Node {
	string name;
	int program_point [2] = {0, 0};
	int label;
	Node* parent;
	Node* next;
	vector<Node*> children;
};

struct Pattern {
	string name;
	string label;
	vector<Pattern*> patterns;
};

Node* init(string a)
{
	struct Node* lst = new Node;
	lst->label = 0;
	lst->parent = 0;
	lst->next = 0;
	lst->name = a;

	return(lst);
}

vector<string> split(string str, const string& delimiter) {
	size_t pos = 0;
	string token;
	vector<string> tokens;
	vector<string> buffer;
	while ((pos = str.find(delimiter)) != string::npos) {
		tokens.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	}
	if (str.find(delimiter) == string::npos)
		tokens.push_back(str);
	for (int t = 0; t < tokens.size(); t++) {
		if (tokens[t] == "") {
			tokens.erase(tokens.begin() + t);
		}
		if (delimiter == "<") {
			if (tokens[t].find(" ") != string::npos) {
				buffer = split(tokens[t], " ");
				tokens.erase(tokens.begin() + t);
				tokens.insert(tokens.begin() + t, buffer.begin(), buffer.end());
			}
			if (tokens[t].back() == '>')
				tokens[t] = "<" + tokens[t];
		}
	}

	return tokens;
}
int ZhangSasha(Node* root1, Node* root2) {
	return 5;
}

vector<int> keyrots(Node* root) {
	vector<int> keys;
	keys.push_back(1);
	keys.push_back(2);

	return keys;
}

vector<vector<string>> split_rule(string str) {

	vector<string> tokens;
	vector<string> elements;
	vector<vector<string>> right_side;

	tokens = split(str, "::=");
	right_side.push_back(vector<string>());
	right_side.back().push_back(tokens[0]);
	tokens = split(tokens[1], " | ");

	for (int j = 0; j < tokens.size(); j++) {
		if (tokens[j].find("<") != string::npos && tokens[j].find(">") != string::npos)
			elements = split(tokens[j], "<");
		else
			elements.push_back(tokens[j]);
		right_side.push_back(elements);
		elements.clear();
	}

	return right_side;
}
void fix_left_recursion(vector<vector<string>> &right_side, string &rule) {
	string subname = "";
	for (int j = 1; j < right_side.size(); j++) {
		if (right_side[j].front() == right_side.front().front()) {
			if (rule == "") {
				subname = right_side.front().front();
				subname.erase(subname.size() - 1);
				subname += "'>";
			}
			right_side[j].push_back(subname);
			right_side[j].erase(right_side[j].begin());
			for (string token : right_side[j]) {
				if (token.front() != '<') {
					if (rule == "") {
						rule += token;
						rule += " ";
					}
					else {
						if (rule.back() == ' ') {
							if (token != right_side[j].back())
							{
								rule += token;
								rule += " ";
							}
							else
								rule += token;
						}
						else {
							if (token != right_side[j].back())
							{
								rule += " ";
								rule += token;
								rule += " ";
							}
							else {
								rule += " ";
								rule += token;
							}

						}
					}

				}
				else
					rule += token;
			}
			rule += " | ";
			right_side.erase(right_side.begin() + j);
			j--;
		}
	}

	if (rule != "") {
		rule += "empty";
		for (int i = 1; i < right_side.size(); i++) {
			right_side[i].push_back(subname);
		}
		rule.insert(0, subname + "::=");
	}

}

void fix_2_rule(vector<vector<string>> &right_side, string &rule) {

	for (int j = 0; j < right_side.size(); j++) {
		for (int z = j + 1; z < right_side.size(); z++) {
			if (right_side[j].front() == right_side[z].front()) {
				if (right_side[z] == right_side.back() && rule!="" && rule.find("::=") != rule.size() - 3) {
					break;
				}
				int p = 0;
				if (rule.find("::=")==rule.size()-3 || rule=="") {
					right_side.push_back(vector<string>());
					while (right_side[j][p] == right_side[z].front()) {
						right_side.back().push_back(right_side[j][p]);
						right_side[z].erase(right_side[z].begin());
						if (right_side[z].size() == 0 || p == right_side[j].size() - 1)
							break;
						p++;
					}
				}
				else {
					vector<string> buff;
					if (right_side[z].size() >= right_side.back().size()) {
						buff.insert(buff.begin(), right_side[z].begin(), right_side[z].begin() + right_side.back().size());
					}
					if (buff == right_side.back()) {
						right_side[z].erase(right_side[z].begin(), right_side[z].begin() + buff.size());
					}
					else
						continue;
				}

				if (right_side[z].size() == 0 && rule.find(" | empty") == string::npos)
					rule += "empty";
				else {
					for (string token : right_side[z]) {
						if (token.front() != '<') {
							if (rule == "") {
								rule += token;
								rule += " ";
							}
							else {
								if (rule.back() == ' ') {
									if (token != right_side[z].back())
									{
										rule += token;
										rule += " ";
									}
									else
										rule += token;
								}
								else {
									if (token != right_side[z].back())
									{
										rule += " ";
										rule += token;
										rule += " ";
									}
									else {
										rule += " ";
										rule += token;
									}

								}
							}

						}
						else
							rule += token;
					}
				}
				rule += " | ";
				right_side.erase(right_side.begin() + z);
				z--;
			}
		}
		if (rule!="" && rule.find("::=") != rule.size() - 3) {
			right_side[j].erase(right_side[j].begin(), right_side[j].begin() + right_side.back().size());
			if (right_side[j].size() == 0 && rule.find(" | empty") == string::npos)
				rule += "empty";
			else {
				for (string token : right_side[j]) {
					if (token.front() != '<') {
						if (token == right_side[j].front()) {
							rule += token;
							rule += " ";
						}
						else {
							if (rule.back() == ' ') {
								if (token != right_side[j].back())
								{
									rule += token;
									rule += " ";
								}
								else
									rule += token;
							}
							else {
								if (token != right_side[j].back())
								{
									rule += " ";
									rule += token;
									rule += " ";
								}
								else {
									rule += " ";
									rule += token;
								}

							}
						}

					}
					else
						rule += token;
				}
			}
			
			if (rule.find("::=") != string::npos) {
				right_side.back().push_back(split(rule, "::=")[0]);
				rule.erase(0, rule.find("::=") + 3);
			}
			else
				right_side.back().push_back(right_side.front().front());
			right_side.back().back().erase(right_side.back().back().end() - 1);
			right_side.back().back() += "'>";
			right_side.erase(right_side.begin() + j);
			rule.insert(0, right_side.back().back()+"::=");
			break;
		}

	}
}

int find(vector<pair<string, vector<string>>>& vect, const string& symbol) {

	for (int i = 0; i < vect.size(); i++) {
		if (vect[i].first == symbol)
			return i;
	}
	return -1;
}

int find(vector<pair<string, string>>& vect, const string& symbol) {

	for (int i = 0; i < vect.size(); i++) {
		if (vect[i].first == symbol)
			return i;
	}
	return -1;
}

int find_vector(vector<vector<pair<string, string>>> & table, string & non_term) {

	for (int i = 0; i < table.size(); i++) {
		if (table[i].begin()->first == non_term)
			return i;
	}

	return -1;


}




int find_vector(vector<vector<pair<string, vector<string>>>> & table, string & non_term) {

	for (int i = 0; i < table.size(); i++) {
		if (table[i].begin()->first == non_term)
			return i;
	}

	return -1;


}

vector<vector<pair<string, vector<string>>>> firsts(vector<vector<vector<string>>>& grammar) {
	vector<vector<pair<string, vector<string>>>> first;
	vector<string> alternate;
	vector<vector<vector<string>>> empty_case_array;


	for (int i = grammar.size() - 1; i >= 0; i--) {
		first.push_back(vector<pair<string, vector<string>>>());
		first.back().push_back(pair<string, vector<string>>(grammar[i].front().front(), vector<string>()));
		for (int j = 1; j < grammar[i].size(); j++) {
			alternate.insert(alternate.begin(), grammar[i][j].begin(), grammar[i][j].end());
			if (grammar[i][j].size()==1 || grammar[i][j][0].front() != '<' && grammar[i][j][0].back() != '>') {
				first.back().push_back(pair<string, vector<string>>(grammar[i][j][0], alternate));
				alternate.clear();
				continue;
			}
			else {
				int pos = 0;
				int ind = 0;
				do {
					bool empty_flag = false;
					if (grammar[i][j][pos].back() == '>') {
						ind = find_vector(first, grammar[i][j][pos]);
						if (ind != -1) {
							for (int k = 1; k < first[ind].size(); k++) {
								if (first[ind][k].first == "empty")
									empty_flag = true;
								if (find(first.back(), first[ind][k].first) == -1)
									first.back().push_back(pair<string, vector<string>>(first[ind][k].first, alternate));
							}
						}
						else {
							first.back().push_back(pair<string, vector<string>>(grammar[i][j][pos], alternate));
						}
						if (empty_flag) {
							pos++;
						}
						else {
							alternate.clear();
							break;
						}

					}
					else {
						first.back().push_back(pair<string, vector<string>>(grammar[i][j][pos], alternate));
					}

				} while (pos != grammar[i][j].size());

			}

		}
	}

	for (auto& kek : first) {
		for (auto& elem : kek) {
			if (elem == kek.front()) {
				cout << elem.first;
				cout << "       ";
			}
			else {
				cout << elem.first;
				cout << ";";
			}

		}
		cout << endl;
	}


	//cout << "==============================================================================================================================" << endl;;


	//for (auto& kek : empty_case_array) {
	//	for (auto& elem : kek) {
	//		for (int t = 0; t < elem.size(); t++) {
	//			if (t == 0) {
	//				cout << elem[t];
	//				cout << "======";
	//			}
	//			else {
	//				cout << elem[t];
	//				cout << ";";
	//			}

	//		}

	//	}
	//	cout << endl;
	//}


	for (auto& vect : first) {
		for (int i = 1; i < vect.size(); i++) {
			if (vect[i].first.front() == '<' && vect[i].first.back() == '>') {
				int pos = 0;
				int ind = 0;
				bool empty_flag = false;
				do {
					ind = find_vector(first, vect[i].first);
					if (ind != -1) {
						for (int j = 1; j < first[ind].size(); j++) {
							if (first[ind][j].first == "empty")
								empty_flag = true;
							if (find(vect, first[ind][j].first) == -1)
								vect.push_back(pair<string, vector<string>>(first[ind][j].first, vect[i].second));
						}

						if (empty_flag) {
							for (auto& elem : vect[i].second) {
								if (elem == vect[i].first)
									vect[i].first == elem;
							}
							pos++;
						}
						else {
							vect.erase(vect.begin() + i);
							i--;
							break;
						}
					}
					else {
						break;
					}

				} while (pos != vect.size());
			}

		}

	}

	return first;

}

vector<vector<pair<string, string>>> follows(vector<vector<vector<string>>>& grammar, vector<vector<pair<string, vector<string>>>>& firsts) {
	vector<vector<pair<string, string>>> follow;
	follow.push_back(vector <pair<string, string>>());
	follow[0].push_back(pair<string, string>(grammar[0][0][0], ""));
	follow[0].push_back(pair<string, string>("$", ""));

	for (auto& elem : grammar) {
		for (int i = 1; i < elem.size(); i++) {
			for (int j = 0; j < elem[i].size(); j++) {
				if (elem[i][j].back() == '>' && elem[i][j].front() == '<') {
					int pos = 0;
					for (int y = follow.size() - 1; y >= 0; y--) {
						if (follow[y].begin()->first == elem[i][j]) {
							pos = y;
							break;
						}
						if ((y == 0) && follow[y].begin()->first != elem[i][j]) {
							follow.push_back(vector <pair<string, string>>());
							follow.back().push_back(pair<string, string>(elem[i][j], ""));
							pos = follow.size() - 1;
						}
					}
					if (j != elem[i].size() - 1) {
						if (find(follow[pos], elem[i][j + 1]) == -1)
							follow[pos].push_back(pair<string, string>(elem[i][j + 1], ""));
					}
					else
						follow[pos].push_back(pair<string, string>(elem[0][0], "follow"));
				}


			}


		}


	}


	for (auto& kek : follow) {
		for (auto& elem : kek) {
			if (elem == kek.front()) {
				cout << elem.first;
				cout << "       ";
			}
			else {
				cout << elem.first;
				cout << ";";
			}

		}
		cout << endl;
	}

	for (auto& vect : follow) {
		int ind = 0;
		for (int i = 1; i < vect.size(); i++) {
			if (vect[i].second == "follow") {
				ind = find_vector(follow, vect[i].first);
				if (ind != -1) {
					for (int j = 1; j < follow[ind].size(); j++) {
						if (find(vect, follow[ind][j].first) == -1)
							vect.push_back(follow[ind][j]);
					}
					vect.erase(vect.begin() + i);
					i--;
				}	
			}
		}
	}


	for (auto& vect : follow) {
		for (int i = 1; i < vect.size(); i++) {
			if (vect[i].first.front() == '<') {
				for (auto& first : firsts) {
					if (first.begin()->first == vect[i].first) {
						for (int k = 1; k < first.size(); k++) {
							if (find(vect, first[k].first) == -1 && first[k].first != "empty") {
								vect.push_back(pair<string, string>(first[k].first, ""));

							}
						}
						if (find(first, "empty") != -1) {
							for (auto& fol : follow) {
								if (fol[0].first == vect[i].first)
								{
									for (int j = 1; j < fol.size(); j++) {
										if (find(vect, fol[j].first) == -1)
											vect.push_back(fol[j]);
									}
									break;
								}
							}

						}
						vect.erase(vect.begin() + i);
						i--;
						break;
					}
				}
			}
		}
	}
	return follow;

}

int LevenshteinDistance(vector<string> &source,
	vector<string> &target) {
	if (source.size() > target.size()) {
		return LevenshteinDistance(target, source);
	}

	int min_size = source.size();
	int max_size = target.size();
	vector<int> lev_dist(min_size + 1);

	for (int i = 0; i <= min_size; ++i) {
		lev_dist[i] = i;
	}

	for (int j = 1; j <= max_size; ++j) {
		int previous_diagonal = lev_dist[0], previous_diagonal_save;
		++lev_dist[0];

		for (int i = 1; i <= min_size; ++i) {
			previous_diagonal_save = lev_dist[i];
			if (source[i - 1] == target[j - 1]) {
				lev_dist[i] = previous_diagonal;
			}
			else {
				lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
			}
			previous_diagonal = previous_diagonal_save;
		}
	}

	return lev_dist[min_size];
}

vector<int> keyroots(Node* root) {
	vector<int> keyroots;
	for (int i = 0; i < root->children.size(); i++) {
		int flag = 0;
		for (int j = i + 1; j < root->children.size(); j++) {
			if (root->children[j] == root->children[i]) {
				flag = 1;
			}
		}
		if (flag == 0) {
			keyroots.push_back(i + 1);
		}
	}

	return keyroots;
}

int** treedist(Node* l1, Node* l2, int i, int j, Node* root1, Node* root2) {

	int** forestdist = new int* [i + 1];
	for (int i = 0; i < i + 1; i++)
		forestdist[i] = new int[j + 1];

	int Delete = 1;
	int Insert = 1;
	int Relabel = 1;

	forestdist[0][0] = 0;
	for (int i1 = l1->children.size(); i1 <= i; i1++) {
		forestdist[i1][0] = forestdist[i1 - 1][0] + Delete;
	}
	for (int j1 = l2->children.size(); j1 <= j; j1++) {
		forestdist[0][j1] = forestdist[0][j1 - 1] + Insert;
	}
	for (int i1 = l1->children.size(); i1 <= i; i1++) {
		for (int j1 = l2->children.size(); j1 <= j; j1++) {
			int i_temp = (l1->children.size() > i1 - 1) ? 0 : i1 - 1;
			int j_temp = (l2->children.size() > j1 - 1) ? 0 : j1 - 1;
			if ((l1->children.size() == l1->children.size()) && (l2->children.size() == l2->children.size())) {

				int Cost = (root1->name == root2->name) ? 0 : Relabel;
				forestdist[i1][j1] = min(
					min(forestdist[i_temp][j1] + Delete, forestdist[i1][j_temp] + Insert),
					forestdist[i_temp][j_temp] + Cost);
			}
			else {
				int i1_temp = l1->children.size() - 1;
				int j1_temp = l2->children.size() - 1;

				int i_temp2 = (l1->children.size() > i1_temp) ? 0 : i1_temp;
				int j_temp2 = (l2->children.size() > j1_temp) ? 0 : j1_temp;

				forestdist[i1][j1] = min(
					min(forestdist[i_temp][j1] + Delete, forestdist[i1][j_temp] + Insert),
					forestdist[i_temp2][j_temp2]);
			}
		}
	}
	return forestdist;
}


int** ZhangShasha(Node* root1, Node* root2) {
	Node* l1 = root1->children.front();
	vector<int> keyroots1 = keyroots(root1);
	Node* l2 = root2->children.front();
	vector<int> keyroots2 = keyroots(root2);

	// space complexity of the algorithm
	int** TD = new int* [l1->children.size() + 1];
	for ( int i = 0; i < l1->children.size() + 1; i++)
		TD[i] = new int[l2->children.size() + 1];

	// solve subproblems
	for (int i1 = 1; i1 < keyroots1.size() + 1; i1++) {
		for (int j1 = 1; j1 < keyroots2.size() + 1; j1++) {
			int i = keyroots1[i1 - 1];
			int j = keyroots2[j1 - 1];
			TD = treedist(l1, l2, i, j, root1, root2);
		}
	}

	return TD;
}



vector<vector<string>> print_tree(Node* initial) {
	
		vector <vector<string>> output;
		output.push_back(vector<string>());
		output.back().push_back(initial->name + ";=" + to_string(initial->label) + "=" + to_string(initial->program_point[0]) + ";" + to_string(initial->program_point[1]));
		output.push_back(vector<string>());
		struct Node* current = new Node;
		current = initial->children[0];
		int pos = 0;
		int line = 0;
		int length_max = 0;
	
		while (1) {
			line++;
			int length = 0;
			int length_cur = 0;
			output[line].push_back(current->name+";="+ to_string(current->label)+"=" +to_string(current->program_point[0])+";"+ to_string(current->program_point[1]));
			output[line].push_back(" ");
			for (auto& elem : output[line]) {
				length_cur += elem.length();
			}
			if (length_cur > length_max)
				length_max = length_cur;
			for (int j = 0; j < line; j++) {
				length = 0;
				for(auto& elem : output[j]) {
					length += elem.length();
				}
				if (length < length_max) {
					for (int i = 0; i < length_max - length; i++) { 
						output[j].push_back(" ");
					} 
				}
			}
			if (current->children.empty()) {
				int start = line;
				if (current->parent->children.size() > 1) {
					start = line + 1;
				}
				else
					length_cur = length_max;
				for (int j = start; j < output.size(); j++) {
					length = 0;
					for (auto& elem : output[j]) {
						length += elem.length();
					}
					for (int i = 0; i < length_cur - length; i++)
					{
						output[j].push_back(" ");
					}
				}
				while (1) {
					if (current->next != 0) {
						current = current->next;
						pos++;
						line = line--;
						break;
					}
					else {
						if (current != current->parent->children.back()) {
							for (int i = 0; i < current->parent->children.size(); i++) {
								if (current->parent->children[i] == current) {
									current = current->parent->children[i+1];
									line--;
									break;
								}
							}	
							break;
						}
						else {
							current = current->parent;
							if (current == initial)
								return output;
							line--;
							continue;
						}					
					}
				}
			}
			else
				current = current->children.front();
			if (line == output.size() - 1) {
				output.push_back(vector<string>());
				if (output[line].front() == " " || output[line].front().front() != '<') {
					length = 0;
					for (int i = 0; i < output[line].size() - 2; i++) {
						length += output[line][i].length();
					}
					for (int i = 0; i < length; i++) {
						output.back().push_back(" ");
					}
				}	
			}
				
		}
	
		delete current;
				
	}

Pattern* anty_unity(Node* root1, Node* root2,set<string>& worktable) {

	
	Pattern* pattern = new Pattern();
	pattern->label = to_string(root1->label) + ";"+ to_string(root2->label) + ";";
	set<string>::iterator it = worktable.find( to_string(root1->label) + ";"  + to_string(root2->label) + ";");
	if (it == worktable.end()) {

		worktable.insert(to_string(root1->label) + ";" + to_string(root2->label) + ";");
	}

	if (root1->name != root2->name || root1->name == root2->name && root1->children.size() != root2->children.size()) {
		if (keyrots(root1).size() > 3 && keyrots(root2).size() >3) {
			int dist = ZhangSasha(root1, root2);
			int min_keyroots = (keyroots(root1).size() > keyroots(root2).size()) ? keyroots(root2).size() : keyroots(root1).size();
			if (dist < min_keyroots/2)
				pattern->name = "yes";
			else
				pattern->name = "no";
		}
		else
			pattern->name = "yes";
		return pattern;
	}
	else {
		if (root1->children.size() == root2->children.size() && root1->children.size() == 0) {
			pattern->name = root1->name;
			return pattern;
		}
		else {
			pattern->name = root1->name;
			int threshold = (root1->children.size() >= root2->children.size()) ? root2->children.size() : root1->children.size();
			for (int i = 0; i < threshold; i++) {
				Pattern* pattern_child = anty_unity(root1->children[i], root2->children[i], worktable);
				pattern->patterns.push_back(pattern_child);
			}
			return pattern;

		}
	}
	
}

//vector<tree*> build_table(vector<vector<string>>& grammar) {
//	vector<tree*> syntax_tree;
//	struct tree* current = new tree;
//
//	for (int i = 0; i < grammar.size(); i++) {
//
//		current = init_tree(grammar[i].front());
//		for (int j = 1; j < grammar[i].size(); j++) {
//			current->children.push_back(grammar[i][j]);
//		}
//		syntax_tree.push_back(current);
//	}
//
//	return syntax_tree;
//
//}

int main() {
	string line;
	ifstream myfile;
	string path;
	vector<string> grammar;
	vector<string> additional_grammar;
	cout << "Enter grammar description file path: ";
	while (grammar.size() == 0) {
		cin >> path;
		myfile.open(path);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				grammar.push_back(line);
			}
			myfile.close();
		}

		else cout << "File not found. Try again: ";
	}

	vector<vector<vector<string>>> gramm;
	vector<vector<vector<string>>> add_gramm;
	vector<string> tokens;
	ofstream fout("output.txt");
	if (fout.is_open()) {
		fout << "GRAMMAR" << endl;
		for (int i = 0; i < grammar.size(); i++) {

			if (grammar[i].front() == '=') {
				gramm.push_back(vector<vector<string>>());
				gramm.back().push_back(vector<string >());
				gramm.back().front().push_back(grammar[i]);
				continue;
			}

			fout << grammar[i];
			fout << endl;

			gramm.push_back(vector<vector<string>>());

			vector<vector<string>> right_side = split_rule(grammar[i]);

			string rule = "";
			fix_left_recursion(right_side, rule);

			if (rule != "") {
				grammar.insert(grammar.begin() + gramm.size(), rule);
				rule.erase(rule.find("::=")+3, rule.size()- rule.find("::=")-3);

				fout << endl;
				fout << "Production " << right_side.front().front() << " has left recursion. Fixed production:" << endl;
				fout << right_side.front().front() << "::=";
				for (int z = 1; z < right_side.size(); z++) {
					for (int k = 0; k < right_side[z].size(); k++) {
						fout << right_side[z][k];
					}
					if (z != right_side.size() - 1)
						fout << " | ";
				}
				fout << endl;
			}


			while (1) {
				fix_2_rule(right_side, rule);

				if (rule != "" && rule.find("::=") != rule.size() - 3) {

					grammar.insert(grammar.begin() + gramm.size(), rule);

					fout << endl;
					fout << "Production " << right_side.front().front() << " does not fulfill I grammatical rule. Applying left-factoring and rewriting production:" << endl;
					fout << endl;
					fout << right_side.front().front() + "::=";
					for (int z = 1; z < right_side.size(); z++) {
						for (int k = 0; k < right_side[z].size(); k++) {
							fout << right_side[z][k];
						}
						if (z != right_side.size() - 1)
							fout << " | ";
					}
					fout << endl;
					rule.erase(rule.find("::=") + 3, rule.size() - rule.find("::=") - 3);
				}
				else
				{
					gramm[i].insert(gramm[i].begin(), right_side.begin(), right_side.end());
					break;
				}
			}
			
		}

	

		for (int i = 0; i < gramm.size(); i++) {
			if (gramm[i].front().front().front() == '=') {
				add_gramm.insert(add_gramm.begin(), gramm.begin() + i + 1, gramm.end());
				gramm.erase(gramm.begin() + i, gramm.end());
				break;
			}
		}

		//for (auto& gram : gramm) {
		//	fout << gram[0].front() << "::=";
		//	for (int p = 1; p < gram.size(); p++) {
		//		for (auto& pipka : gram[p]) {
		//			fout << pipka;
		//		}
		//		if (gram[p] != gram.back())
		//			fout << " | ";
		//	}
		//	fout << endl;
		//}

		//fout << "==============================================================================================================================" << endl;
		//fout << "AADFDFDFFDFDFFDFFDFFD" << endl;

		//for (auto& add_gramm : add_gramm) {
		//	fout << add_gramm[0].front() << "::=";
		//	for (int p = 1; p < add_gramm.size(); p++) {
		//		for (auto& pipka : add_gramm[p]) {
		//			fout << pipka;
		//		}
		//		if (add_gramm[p] != add_gramm.back())
		//			fout << " | ";
		//	}
		//	fout << endl;
		//}

		vector<vector<pair<string, vector<string>>>> first = firsts(gramm);

		vector<vector<pair<string, string>>> follow = follows(gramm, first);

		vector<vector<pair<string, vector<string>>>> add_first = firsts(add_gramm);

		fout << "==============================================================================================================================" << endl;
		fout << "FIRSTS" << endl;
		for (int i = 0; i < first.size(); i++)
		{
			for (auto& it : first[i]) {
				fout << "(" << it.first << ", [";
				for (auto &elem : it.second) {
						fout << elem;
				}
				fout << "])";
			}
			fout << endl;
		}

		fout << "==============================================================================================================================" << endl;

		fout << "ADDITIONAL FIRSTS" << endl;
		for (int i = 0; i < add_first.size(); i++)
		{
			for (auto& it : add_first[i]) {
				fout << "(" << it.first << ", [";
				for (auto& elem : it.second) {
					fout << elem;
				}
				fout << "])";
			}
			fout << endl;
		}
		fout << "==============================================================================================================================" << endl;
		fout << "FOLLOWS" << endl;
		for (int i = 0; i < follow.size(); i++)
		{
			for (auto& it : follow[i]) {
				fout << "(" << it.first << "," << it.second << ")";
			}
			fout << endl;
		}

		for (auto& production : gramm) {
			for (auto& altenative : production) {
				int firsts_ind = find_vector(first, altenative[0]);
				int follow_ind = find_vector(follow, altenative[0]);

				if (firsts_ind != -1 && follow_ind != -1) {
					for (int i = 1; i < first[firsts_ind].size(); i++) {
						if (find(follow[follow_ind], first[firsts_ind][i].first) != -1) {
							if (find(first[firsts_ind], "empty") != -1) {
								fout << "Error. Production " << altenative[0] << " does not fulfull gramatical rule 2.";
								fout.close();
								return 0;
							}
						}
					}
				}

			}
		}

		fout << "==============================================================================================================================" << endl;

		path.clear();
		vector<vector<string>> inputs;
		for (int i = 1; i <= 2; i++) {
			inputs.push_back(vector<string>());
			cout << "Enter  file " << i << " path: ";
			while (inputs.back().size() == 0) {
				cin >> path;
				myfile.open(path);
				if (myfile.is_open())
				{
					while (getline(myfile, line)) {
						int pos = 0;
						while ((pos = line.find(' ')) != std::string::npos || (pos = line.find('\t')) != std::string::npos)
							line.erase(pos, 1);
						if ((pos = line.find("//")) != std::string::npos)
							line.erase(pos, line.size() - pos);
						inputs.back().push_back(line);
					}

					myfile.close();
				}

				else cout << "File not found. Try again: ";
			}
			path.clear();
		}

		vector<string> stack;
		vector<vector<string>> outputs;
		vector<Node*> roots;
		int ind = 0;
		int ind_1 = 0;

		stack.push_back("$");
		for (auto& input : inputs) {
			input.push_back("$");
			stack.push_back(gramm[0][0][0]);
			Node* root = init(gramm[0][0][0]);

			root->program_point[0] = 1;
			root->program_point[1] = 1;
			Node* current = root;
			roots.push_back(root);
			outputs.push_back(vector<string>());
			int point1 = current->program_point[0];
			int point2 = current->program_point[1];

			while (1) {
				if (stack.back().size() == 1 || stack.back().front() != '<' && stack.back().back() != '>') {
					if (input.front().find(stack.back()) == 0) {
						if (input.front() == "$") {
							fout << "String accepted" << endl;;
							break;
						}
						outputs.back().push_back(stack.back());
						input.front().erase(0, stack.back().size());
						current->program_point[0] = point1;
						current->program_point[1] = point2;
						point2++;
						if (input.front().size() == 0) {
							input.erase(input.begin());
							point1++;
							point2 = 1;
						}
						while (current->next == 0 && current->parent != 0) {
							current = current->parent;
						}
						current = current->next;
						stack.pop_back();
					}
					else {
						fout << "Error. Character " << stack.back() << " is not acceptable. Expression doesn't belong to grammar" << endl;
						fout.close();
						return 0;
					}
				}
				else {
					ind = find_vector(first, stack.back());
					if (ind != -1) {
						for (int i = 1; i < first[ind].size(); i++) {
							if (input.front().find(first[ind][i].first) == 0) {
								stack.pop_back();								
								for (int j = first[ind][i].second.size() - 1; j >= 0; j--) {
									Node* new_child = init(first[ind][i].second[j]);
									new_child->parent = current;
									new_child->program_point[0] = point1;
									if (!current->children.empty())
										new_child->next = current->children.front();
									else
										new_child->next = 0;
									current->children.insert(current->children.begin(), new_child);
									stack.push_back(first[ind][i].second[j]);
								}
								current = current->children.front();
								break;
							}
							if (i == first[ind].size() - 1) {
								int ind_2 = find_vector(follow, stack.back());
								if (find(follow[ind_2], string(1, input.front().front())) != -1) {
									ind_1 = find(first[ind], "empty");
									if (ind_1 != -1) {
										stack.pop_back();
										Node* new_child = init("empty");
										new_child->parent = current;
										new_child->next = 0;
										current->children.push_back(new_child);
										while (current->next == 0 && current->parent != 0) {
											current = current->parent;
										}
										if (current->parent != 0)
											current = current->next;
									}
									else {
										fout << "Error. Character " << stack.back() << " is not acceptable. Expression doesn't belong to grammar" << endl;
										fout.close();
										return 0;
									}
								}								
								else {
									for (int j = 1; j < first[ind].size(); j++) {
										if (first[ind][j].first.size() != 1 && first[ind][j].first.front() == '<') {
											stack.pop_back();
											for (int z = first[ind][j].second.size() - 1; z >= 0; z--) {
												Node* new_child = init(first[ind][j].second[z]);
												new_child->parent = current;
												new_child->program_point[0] = point1;
												if (!current->children.empty())
													new_child->next = current->children.front();
												else
												new_child->next = 0;
											current->children.insert(current->children.begin(), new_child);
											stack.push_back(first[ind][j].second[z]);
										}
										current = current->children.front();
										break;
									}
									if (j == first[ind].size() - 1) {
										fout << "Error. Character " << stack.back() << " is not acceptable. Expression doesn't belong to grammar" << endl;
										fout.close();
										return 0;
									}
								}
							}
						}
					}
					}
					else {
						ind = find_vector(follow, stack.back());
						if (ind != -1) {
							string name_buff = current->name;
							name_buff.erase(0, 1);
							name_buff.erase(name_buff.size() - 1, 1);
							for (int j = 0; j < follow[ind].size(); j++) {
								if (input.front().find(follow[ind][j].first) == 0)
									break;
								if (j == follow[ind].size() - 1) {
									input.front().erase(input.front().begin());
									j = 0;
								}								
							}
						Node* new_child = init(name_buff);
						new_child->parent = current;
						new_child->next = 0;
						new_child->program_point[0] = point1;
						new_child->program_point[1] = point2;
						point2++;
						current->children.push_back(new_child);
						while (current->next == 0 && current->parent != 0) {
							current = current->parent;
						}
						if (current->parent != 0)
							current = current->next;
						stack.pop_back();
						}
					}
				}
			}
		}
	
		vector<Node*> roots_ast;
		int lab = 1;
		for (int i = 0; i <= 1; i++) {
			Node* root_ast = init(roots[i]->name);
			root_ast->label = lab;
			roots_ast.push_back(root_ast);
			Node* current_ast = root_ast;
			Node *current = roots[i];
			lab++;

			while (1) {
				if (!current->children.empty()) {
					for (auto& single : current->children) {
						if (single->children.empty()) {
							if (current->children.size() != 1) {
								Node* block = init("<block"+to_string(current->children.size())+">");
								block->parent = current_ast;
								block->label = lab;
								lab++; 
								if (current_ast->children.size() != 0)
									current_ast->children.back()->next = block;
								current_ast->children.push_back(block);
								current_ast = block;
							}
							vector<Node*> child_buff;
							for (int z = current->children.size() - 1; z >= 0; z--) {
								Node* new_child = new Node();
								if (current->children.size() == 1 && current->children[z]->name.front() != '<' && current->children[z]->name.size()!=1 && current->children[z]->name != "empty") {
									string name = current->name;
									name.erase(0, 1);
									name.erase(name.size()-1, 1);
									new_child = init(name);
								}
								else
									new_child = init(current->children[z]->name);
								new_child->parent = current_ast;
								if (!child_buff.empty())
									new_child->next = child_buff.front();
								else
									new_child->next = 0;
								new_child->label = lab + z;
								new_child->program_point[0] = current->children[z]->program_point[0];
								new_child->program_point[1] = current->children[z]->program_point[1];
								child_buff.insert(child_buff.begin(), new_child);
							}
							lab = lab+child_buff.size();
							if (current_ast->children.empty())
								current_ast->children.insert(current_ast->children.begin(), child_buff.begin(), child_buff.end());
							else {
								current_ast->children.back()->next = child_buff.front();
								current_ast->children.insert(current_ast->children.end(), child_buff.begin(), child_buff.end());
							}
							if (current_ast->name.find("<block") != string::npos)
								current_ast->program_point[0] = current_ast->children.front()->program_point[0];
							current_ast = child_buff.front();
							break;


						}

					}
					current = current->children.front();

				}
				/*fout << current->name << endl;*/
			/*fout << endl;*/
				else {
					if (current->next != 0) {
						current = current->next;
						if (current_ast->next == 0)
							current_ast = current_ast->parent;
						else
							current_ast = current_ast->next;
					}
					else {
						if(current_ast->parent!=0)
							current_ast = current_ast->parent;
						if(current_ast->name.find("<block")!=string::npos)
							current_ast = current_ast->parent;
						while (current->next == 0 && current->parent != 0) {
							if(current_ast->parent!=0 && current_ast->parent->name.find("<block") != string::npos && current->parent->name == current_ast->parent->parent->name)
								current_ast = current_ast->parent;
							if (current_ast->parent != 0 && current->parent->name == current_ast->parent->name)
								if (current_ast->name != current_ast->parent->name) 
									current_ast = current_ast->parent;
							current = current->parent;
						}
						if (current->parent == 0 && current_ast->parent == 0)
							break;
						if (current->name == current_ast->name)
							current_ast = current_ast->next;
						current = current->next;
					}

				}

			}

		}

		
		for (int i = 0; i <= 1; i++) {
			Node* current = roots_ast[i];
			while (1) {				
				for (int j = 0; j < current->children.size(); j++) {
					if (current->children[j]->name == "empty") {
						current->children.erase(current->children.begin() + +j);
						j--;

						if (j < current->children.size() - 1 && j != -1)
							current->children[j]->next = current->children[j + 1];
						else {
							if (j == current->children.size() - 1 && j!=-1)
								current->children[j]->next = 0;
						}
					}			
				}
				if (!current->children.empty()) {
					current = current->children.front();
				}
					
				else {
					bool flag = false;
					while (current->next == 0) {
						if (current != current->parent->children.back()) {
							for (int z = 0; z < current->parent->children.size(); z++) {
								if (current->parent->children[z] == current) {
									current = current->parent->children[z + 1];
									flag = true;
									break;
								}
							}
						}
						else {
							current = current->parent;
						}	
						if (current->parent == 0)
							break;
					}
					if (current->parent == 0)
						break;
					else {
						if (flag == false)
							current = current->next;
						else
							flag = false;
					}
						
				}
			}
		}

		for (int i = 0; i <= 1; i++) {
			fout << i+1 <<"tree:" << endl;
			vector<vector<string>> output_tree = print_tree(roots_ast[i]);
			for (auto& line : output_tree) {
				for (string& production : line) {
					fout << production;
				}
				fout << endl;
			}
		}


		map<string, set<Pattern*>> patterns;
		set<string> worktable;
		set<string>::iterator it;
		Node* current1 = roots_ast.front();
		Node* current2 = roots_ast.back();
		while (1) {
			it = worktable.find( to_string(current1->label) + ";" + to_string(current2->label) + ";" );
			if (it == worktable.end()) {
				worktable.insert( to_string(current1->label) + ";" + to_string(current2->label) + ";" );
				if (current1->name == current2->name) {
					Pattern* buff_pattern = anty_unity(current1, current2, worktable);
					map<string, set<Pattern*>>::iterator it1 = patterns.find(current1->name);
					if (it1 == patterns.end()) 
						patterns.insert(pair<string, set<Pattern*>>(current1->name, set<Pattern*>()));
					patterns[current1->name].insert(buff_pattern);
				}
			}
			if (current2->next != 0)
				current2 = current2->next;
			else {
				if (current1->next != 0) {
					current1 = current1->next;
					current2 = current2->parent->children.front();
				}
				else {
					if (current1->parent == 0 && current2->parent == 0) {
						current1 = current1->children.front();
						current2 = current2->children.front();
					}
					else {
						current1 = current1->parent->children.front();
						current2 = current2->parent->children.front();
						while (1) {
							if (current1->children.size() != 0 && current1->children.size() == current2->children.size()) {
								current1 = current1->children.front();
								current2 = current2->children.front();
								break;
							}
							else {
								while (current1->next == 0 && current1->parent != 0 && current2->next == 0 && current2->parent != 0) {
									current1 = current1->parent;
									current2 = current2->parent;
								}
								if (current1->parent != 0 && current2->parent != 0) {
									current1 = current1->next;
									current2 = current2->next;
								}
								else
									break;
							}
						}
						if (current1->parent == 0 && current2->parent == 0)
							break;
		
					}

				}
			}

		}


		for (auto& elem : patterns) {
			if (elem.first == "no") {
				fout << "Plagiat not detected";
				fout.close();
				return 0;
			}
		}

		
		fout << "Plagiat detected";
		fout.close();
		return 0;
	}
}
