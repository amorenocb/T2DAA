#include <bits/stdc++.h>

using namespace std;

#define FORs(i, n, s) for (int (i)=0; (i) < int (n); (i)+=s)
#define REVs(i, n, s) for (int (i)= (int) n; (i) >= 0; (i)-=s)

void stripAndTrim(string text){
	std::remove(text.begin(), text.end(), '.');
	std::remove(text.begin(), text.end(), ',');
	std::remove(text.begin(), text.end(), ';');
	std::replace(text.begin(), text.end(), '\n', ' ');
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	return;
}

void standarize(string text){
	while (text.length()%5){
		text.append("$");
	}
	return;
}

int getMax(vector<pair<string, int>> T, int index){
	int max = 0;
	// int i;
	FORs(i, T.size(), 1){
		if (max < (int) T[i].first[index]){
			max = (int) T[i].first[index];
		}
	}
	return max;
}

vector<int> countSort(vector<pair<string, int>> T, int index){
	// int i;
	int max = getMax(T, index);
	vector<int> out(max);
	FORs(i, T.size(), 1){
		out[(int) T[i].first[index]]++;
	}
	FORs(i, max, 1){
		if (i == 0) continue;
		out[i] += out[i-1];
	}
	return out;
}

void indexSort(vector<pair<string, int>> T, int index){
	int start=0;
	vector<pair<string, int>> out(T.size());
	vector<int> c_sort = countSort(T, index);
	FORs(i, T.size(), 1){
		if (((int) T[i].first[index]) == 0)
			out[start++]=T[i];
		else
			out[c_sort[((int) T[i].first[index])-1]++]=T[i];
	}
	out.swap(T);
}


void radixSort(vector<pair<string, int>> T, int size){
	// int index;
	REVs(index, size-1, 1){
		indexSort(T, index);
	}
}

// vector<pair<string, int>> merge(vector<pair<string, int>> T1, vector<pair<string, int>> T2){
// 	vector<int> out;
// 	vector<string>::iterator it1 = T1.begin();
// 	vector<string>::iterator it2 = T2.begin();
// 	while (it1 != T1.end() && it2 != T2.end()){
// 		if (*it1.first < *it2.first){
// 			out.push_back(*it1);
// 			++it1;
// 		}
// 		else{
// 			out.push_back(*it2);
// 			++it2;
// 		}
// 	}
// 	return out;
// }

vector<char> getRanks(vector<pair<string, int>> T){
	vector<char> out(T.size());
	string prev;
	// int i;
	char rank=1;
	FORs(i, T.size(), 1){
		if (prev.compare(T[i].first) == 0){
			out[T[i].second]=rank;
		}
		else{
			out[T[i].second]=rank++;
		}
		prev = T[i].first;
	}
	return out;
}

vector<pair<char, int>> setRanks(vector<pair<string, int>> T, vector<char> Ranks){
	vector<pair<char, int>> out(T.size());
	// int i;
	FORs(i, T.size(), 1){
		out[i] = make_pair(Ranks[T[i].second], T[i].second);
	}
	return out;
}

string buildSub(vector<pair<char, int>> S1, vector<pair<char, int>> S2){
	string aux;
	// int i;
	vector<pair<char, int>>::iterator it1 = S1.begin();
	vector<pair<char, int>>::iterator it2 = S2.begin();
	aux += (*it1).first;
	++it1;
	while (it1 != S1.end()){
		aux += (*it1).first;
		++it1;
	}
	while (it2 != S2.end()){
		aux += (*it2).first;
		++it2;
	}
	return aux;
}

vector<pair<char, int>> merge(vector<pair<char, int>> S1, vector<pair<char, int>> S2){
	// int i;
	string text = buildSub(S1, S2);
	int l = text.length();
	vector<pair<char, int>> S(l);
	standarize(text);
	vector<pair<string, int>> Tall;
	FORs(i, l, 1) Tall.push_back(make_pair(text.substr(i,2), i));
	radixSort(Tall, 2);
	FORs(i, S1.size(), 1) S[Tall[i].second]=S1[i];
	FORs(i, S2.size(), 1) S[Tall[S1.size()+i].second]=S2[i];
	return S;
}

vector<pair<char, int>> getSuffTable(vector<pair<char, int>> STab, vector<pair<char, int>> STc, vector<char> Ranks){
	vector<pair<char, int>> out;
	int a,b;
	vector<pair<char, int>>::iterator it1 = STab.begin();
	vector<pair<char, int>>::iterator it2 = STc.begin();
	while (it1 != STab.end() && it2 != STc.end()){
		if ((*it1).first < (*it2).first){
			out.push_back(*it1);
			++it1;
		}
		else if ((*it1).first > (*it2).first){
			out.push_back(*it2);
			++it2;
		}
		else {
			a = (*it1).second;
			b = (*it2).second;
			while (Ranks[a] == Ranks[b]){
				++a;
				++b;
			}
			if (Ranks[a] < Ranks[b]){
				out.push_back(*it1);
				++it1;
			}
			else {
				out.push_back(*it2);
				++it2;
			}
			out.push_back(*it2);
			++it2;
		}
	}
	return out;
}

vector<int> getSA(vector<pair<char, int>> ST){
	vector<int> SA(ST.size());
	// int i;
	FORs(i, ST.size(), 1){
		SA[ST[i].second] = i;
	}
	return SA;
}

vector<int> build(string text){
	// int i;
	int l = text.length();
	stripAndTrim(text);
	standarize(text);
	vector<pair<string, int>> Tall, Ta, Tb, Tc, Tab;
	vector<char> Ranks;
	vector<pair<char, int>> STa, STb, STab, STc, ST;
	vector<int> SA;
	FORs(i, l, 3){
		Ta.push_back(make_pair(text.substr(i,3), i));
		Tb.push_back(make_pair(text.substr(i+1,3), i+1));
		Tc.push_back(make_pair(text.substr(i+2,3), i+2));
		Tall.push_back(make_pair(text.substr(i,3), i));
		Tall.push_back(make_pair(text.substr(i+1,3), i+1));
		Tall.push_back(make_pair(text.substr(i+2,3), i+2));
	}
	radixSort(Tall, 3);
	Ranks = getRanks(Tall);
	STa = setRanks(Ta, Ranks);
	STb = setRanks(Tb, Ranks);
	STab = merge(STa, STb);
	STc = setRanks(Tc, Ranks);
	ST = getSuffTable(STab, STc, Ranks);
	SA = getSA(ST);
	return SA;
}

int check(string test, vector<int> SA, string text, int index){
	FORs(i, test.length(), 1){
		if (test[i] != text[SA[index+i]]) return -1;
	}
	return index;
}

int search(string test, vector<int> SA, string text){
	int ini, fin, mid;
	ini = 0;
	fin = (int) SA.size();
	while (ini != fin){
		mid = (ini+fin)/2;
		if (test[0] < text[SA[mid]]){
			fin = mid;
		}
		else if (test[0] > text[SA[mid]]){
			ini = mid+1;
		}
		else{
			return check(text, SA, text, mid);
		}
	}
	return -1;
}

string parse(string file){

	ifstream t(file);
	stringstream buffer;
	buffer << t.rdbuf();

	return buffer.str();
}

int main(){
	
	int testsAmmount;
	string test;
	string file;

	cout << "Ingrese archivo de prueba: ";
	cin >> file;

	string text = parse(file);
	vector<int> SA = build(text);

	cout << "Ingrese número de tests: ";
	cin >> testsAmmount;

	FORs(i, testsAmmount, 1){
		cout << "Ingrese substring: ";
		cin >> test;
		cout << (search(test, SA, text) == true ? "SI" : "NO");
	}


	return 0;
}