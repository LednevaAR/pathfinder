#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
	std::random_device prng;
	std::string s0, s, st, s1, s2, ss;
	int numv, numr, n = 0;
	map <string, int> mp;
	//vector <string> tags;
	//tags = {"a", "b", ""};
	map <string, string> marknode;
	vector <string> nodes;
	s0 = argv[1];
	s = s0.substr(s0.rfind(" ") + 1);
	ifstream file (s.c_str());
	s = s0.substr(s0.rfind(" ") + 1, s0.rfind("/") - s0.rfind(" "));
	ss = s;
	s += "graph";
	s += s0.substr(s0.find(".main") + 5, s0.rfind(".") - s0.find(".main") - 5);
	ofstream f(s.c_str());
	numr = 0;
	numv = 0;
	srand(time(NULL));
	while (getline(file, st)) {
		if (st.find("->") != -1) numr += 1;
		else if (st.find("Node") != -1) {
			s1 = st.substr(st.find("Node"), st.find_first_of(" :") - st.find("Node"));
			nodes.push_back(s1);
			if (mp.find(s1) == mp.end()) {	
				mp.insert(make_pair(s1, n));
				if (st.find("{<s0>T|<s1>F}") != -1) {
					marknode.insert(make_pair(s1, "if"));
				} else if (st.find(" = phi ") != -1) {
					marknode.insert(make_pair(s1, "phi"));
				} else if (st.find("ret ") != -1) {
					marknode.insert(make_pair(s1, "return"));
				} else if (st.find("BEGIN") != -1) {
					marknode.insert(make_pair(s1, "begin"));
				} else if (st.find("END") != -1) {
					marknode.insert(make_pair(s1, "end"));
				} else if ((st.find("@") != -1) && (st.find("@.") == -1)) {
					marknode.insert(make_pair(s1, "function"));
				} else if ((st.find("%struct") != -1) && (st.find("getelementptr") != -1)) {
					marknode.insert(make_pair(s1, "struct"));
				} else if ((st.find("getelementptr") != -1) && ((st.substr(0, st.find("br label"))).rfind(",") > (st.substr(0, st.find("br label"))).rfind("%"))) {//переписать
					marknode.insert(make_pair(s1, "address"));
				} else if (st.find("getelementptr") != -1) {
					marknode.insert(make_pair(s1, "mod_address"));
				} else if (st.find("alloca") != -1) {
					marknode.insert(make_pair(s1, "alloca"));
				} else if (st.find("store") != -1) {
					marknode.insert(make_pair(s1, "store"));
				} else if (st.find("load") != -1) {
					marknode.insert(make_pair(s1, "load"));
				} else if (st.find("loop") != -1) {
					marknode.insert(make_pair(s1, "loop"));
				} else if (st.find("sext") != -1) {
					marknode.insert(make_pair(s1, "sext"));
				} else
					marknode.insert(make_pair(s1, ""));
				n += 1;
			}
		}
		std::sort(nodes.begin(), nodes.end());
    		nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());
	}
	//s = s0.substr(s.rfind("/") + 1);
	file.clear();
	file.seekg(0);
	numv = nodes.size();
	f << "1" << endl;
	s = s0.substr(s0.find(".main") + 5, s0.rfind(".") - s0.find(".main") - 5);
	ifstream f1((ss + argv[2]).c_str());
	while (getline(f1, st)) {
		f << st << endl;
	}
	f1.close();
	ofstream f2((ss + ".markmain" + s + ".dot").c_str());
	f << endl;
	f << numv << " " << numr << endl;
	for (int i = 0; i < nodes.size(); i++) f << nodes[i] << " ";
	f << endl;
	//std::uniform_int_distribution<int> dist(1, nodes.size());
	while (getline(file, st)) {
		if (st.find("->") != -1) {
			s1 = st.substr(st.find("Node"), st.find_first_of(": ") - st.find("Node"));
			s2 = st.substr(st.rfind("Node"), st.find_first_of(" ;[", st.rfind("Node")) - st.rfind("Node"));
			if (marknode[s1] == "loop") {
				s = "o";
				marknode[s2] = "loopfirst";
			}
		}
	}
	file.clear();
	file.seekg(0);
	while (getline(file, st)) {
		if (st.find("->") != -1) {
			s1 = st.substr(st.find("Node"), st.find_first_of(": ") - st.find("Node"));
			s2 = st.substr(st.rfind("Node"), st.find_first_of(" ;[", st.rfind("Node")) - st.rfind("Node"));
			if ((marknode[s1] == "address") && (marknode[s2] == "mod_address")) {
				s = "d";
			} else if (marknode[s1] == "loopfirst") {
				s = "p";
			} else if ((marknode[s1] == "mod_address") && (marknode[s2] == "address")) {
				s = "q";
			} else if (marknode[s1] == "function") {
				s = "e";
			} else if ((marknode[s1] == "mod_address") && (marknode[s2] == "store")) {
				s = "f";
			} else if ((marknode[s1] == "mod_address") && (marknode[s2] == "load")) {
				s = "n";
			//} else if ((marknode[s1] == "address") && (marknode[s2] == "store")) {
			} else if ((marknode[s1] == "sext") && (marknode[s2] == "mod_address")) {
				s = "u";
			} else if ((marknode[s1] == "address") && (marknode[s2] == "load")) {
				s = "t";
			} else if ((marknode[s1] == "phi") && (marknode[s2] == "phi")) {
				s = "h";
			} else if ((marknode[s1] == "phi") && (marknode[s2] == "if")) {
				s = "i";
			} else if (marknode[s1] == "struct") {
				s = "j";
			} else if ((marknode[s1] == "if") && (marknode[s2] == "struct")) {
				s = "l";
			} else if (marknode[s1] == "if") {
				s = "k";
			} else if (marknode[s1] == "loop") {
				s = "o";
			} else if (marknode[s2] == "function") {
				s = "a";
			} else if ((marknode[s1] == "return") && (marknode[s2] == "end")) {
				s = "m";
			} else if (marknode[s2] == "phi") {
				s = "b";
			} else if (marknode[s2] == "if") {
				s = "c";
			} else if (marknode[s1] == "phi") {
				s = "g";
			} else if ((marknode[s1] == "load") && (marknode[s2] == "sext")) {
				s = "r";
			} else if ((marknode[s2] == "sext") && (marknode[s1] == "mod_address")) {
				s = "s";
			} else {
				s = "z";
			}
			f << mp[s1] << " " << mp[s2] << " " << s << endl;
			//f << mp[s1] << " " << mp[s2] << " " << tags[dist(prng) % 3] << endl;
			st = st.substr(0, st.find("Node")) + s1 + " -> " + s2 + " [label=\"" + s + "\"];";

		}
		f2 << st << endl;
	}
	f.close();
	f2.close();
	file.close();
	s = s0.substr(s0.find(".main") + 5, s0.rfind(".") - s0.find(".main") - 5);
	system(("dot -Tpng " + ss + ".markmain" + s + ".dot -o " + ss + "markoutfile" + s + ".png").c_str());//визуализация графа с разметкой
	remove("transl_to_core");
}