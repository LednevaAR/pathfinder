#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

int count(string s) {
  	int c = 0;
  	for (int i = 0; i < s.size(); i++)
    		if (s[i] == ')') c++;
			return c;
}

int main(int argc, char* argv[]) {
	string s0, s, s1, st, ss;
	int n = 0;
	map <int, string> mp;
	map <string, int> mp1;
	s0 = argv[1];
	s = s0.substr(s0.rfind(" ") + 1);
	ifstream file(s.c_str());
	s = s0.substr(s0.rfind(" ") + 1, s0.rfind("/") - s0.rfind(" "));
	ss = s;
	s += ".redgraph";
	s += s0.substr(s0.find(".markmain") + 9);
	ofstream f(s.c_str());
	s1 = argv[2];
	s = s1.substr(s1.rfind(" ") + 1);
	ifstream file1(s.c_str());
	
	while (getline(file, st)) {
		if ((st.find("Node") != -1) && (st.find("->") == -1)) {
			s1 = st.substr(st.find("Node"), st.find_first_of(" :") - st.find("Node"));
			if (mp1.find(s1) == mp1.end()) {	
				mp.insert(make_pair(n, s1));
				mp1.insert(make_pair(s1, n));
				n += 1;
			}
		}
	}
	
	getline(file1, st);
	int k = count(st);
	int b[k], e[k], i = 0;
	while (st.find("(") != -1) {
		b[i] = atoi((st.substr(st.find("(") + 1, st.find(",") - st.find("(") - 1)).c_str());
		s = st.substr(st.find(",") + 1);
		e[i] = atoi((s.substr(s.find(",") + 1, s.find(")") - s.find(",") - 1)).c_str());
		i += 1;
		st = st.substr(st.find(")") + 1);
	}
	
	file.clear();
	file.seekg(0);

	while (getline(file, st)) {
		for (i = 0; i < k; i++) {
			if ((st.find(mp[b[i]]) != -1) && (st.find(mp[e[i]]) != -1)) {
				st = st.substr(0, st.size() - 1);
				st += " [color = \"red\"];";
			}
		}
		f << st << endl;
	}
	
	s = s0.substr(s0.find(".markmain") + 9);
	system(("dot -Tpng " + ss + ".redgraph" + s + " -o " + ss + "redmarkout" + s.substr(0, s.size() - 4) + ".png").c_str());
	remove((ss + ".redgraph" + s).c_str());
	file1.close();
	file.close();
	f.close();
	return 0;
}