#include <bits/stdc++.h>

using namespace std;

#define FORs(i, n, s) for (int (i)=0; (i) < int (n); (i)+=s)
#define REVs(i, n, s) for (int (i)= (int) n; (i) >= 0; (i)-=s)

/* Removes voals variations that are not used in english. */
string correctVoals(string text){
	std::remove(text.begin(), text.end(), (char) 50081);
	std::remove(text.begin(), text.end(), (char) 50084);
	std::remove(text.begin(), text.end(), (char) 50085);
	std::remove(text.begin(), text.end(), (char) 50049);
	std::remove(text.begin(), text.end(), (char) 50052);
	std::remove(text.begin(), text.end(), (char) 50053);
	std::remove(text.begin(), text.end(), (char) 50089);
	std::remove(text.begin(), text.end(), (char) 50090);
	std::remove(text.begin(), text.end(), (char) 50091);
	std::remove(text.begin(), text.end(), (char) 50057);
	std::remove(text.begin(), text.end(), (char) 50058);
	std::remove(text.begin(), text.end(), (char) 50059);
	std::remove(text.begin(), text.end(), (char) 50095);
	std::remove(text.begin(), text.end(), (char) 50093);
	std::remove(text.begin(), text.end(), (char) 50061);
	std::remove(text.begin(), text.end(), (char) 50063);
	std::remove(text.begin(), text.end(), (char) 50099);
	std::remove(text.begin(), text.end(), (char) 50102);
	std::remove(text.begin(), text.end(), (char) 50104);
	std::remove(text.begin(), text.end(), (char) 50067);
	std::remove(text.begin(), text.end(), (char) 50070);
	std::remove(text.begin(), text.end(), (char) 50072);
	std::remove(text.begin(), text.end(), (char) 50106);
	std::remove(text.begin(), text.end(), (char) 50108);
	std::remove(text.begin(), text.end(), (char) 50074);
	std::remove(text.begin(), text.end(), (char) 50076);
	return text;
}

/* Removes special characters. */
string stripAndTrim(string text){
	std::remove(text.begin(), text.end(), '{');
	std::remove(text.begin(), text.end(), '}');
	std::remove(text.begin(), text.end(), '[');
	std::remove(text.begin(), text.end(), ']');
	std::remove(text.begin(), text.end(), '`');
	std::remove(text.begin(), text.end(), '\\');
	std::remove(text.begin(), text.end(), '~');
	std::replace(text.begin(), text.end(), '.', ' ');
	std::replace(text.begin(), text.end(), ',', ' ');
	std::replace(text.begin(), text.end(), ';', ' ');
	std::replace(text.begin(), text.end(), ':', ' ');
	std::replace(text.begin(), text.end(), '-', ' ');
	std::replace(text.begin(), text.end(), '_', ' ');
	std::replace(text.begin(), text.end(), '+', ' ');
	std::replace(text.begin(), text.end(), '*', ' ');
	std::replace(text.begin(), text.end(), '=', ' ');
	std::replace(text.begin(), text.end(), '?', ' ');
	std::replace(text.begin(), text.end(), '!', ' ');
	std::replace(text.begin(), text.end(), (char) 49825, ' ');
	std::replace(text.begin(), text.end(), (char) 49855, ' ');
	std::replace(text.begin(), text.end(), '\'', ' ');
	std::replace(text.begin(), text.end(), '\"', ' ');
	std::replace(text.begin(), text.end(), '\t', ' ');
	std::replace(text.begin(), text.end(), '\n', ' ');
	text = correctVoals(text);
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

/* Adds as many $ as necessary to have a viable string for the build. */
string standarize(string text){
	while (text.length()%5){
		text.append("$");
	}
	return text;
}

/* Auxiliary method to get the size of a Counting Sort Array. */
unsigned char getMax(vector<pair<string, int>> T, int index){
	unsigned char max = 0;
	FORs(i, T.size(), 1){
		if (max < (unsigned char) T[i].first[index]){
			max = (unsigned char) T[i].first[index];
		}
	}
	return max;
}

/* Organizes an array by storing the ammount of times a value appears */
vector<int> countSort(vector<pair<string, int>> T, int index){
	int max = getMax(T, index);
	vector<int> out(max, 0);
	/* Counts aparitions */
	FORs(i, T.size(), 1){
		out[(int) T[i].first[index]]++;
	}
	/* Sets the values' index on the original array sorted. */
	FORs(i, max, 1){
		if (i == 0) continue;
		out[i] += out[i-1];
	}
	return out;
}

/* Sorts an array according to the index specified */
void indexSort(vector<pair<string, int>> T, int index){
	int start=0;
	vector<pair<string, int>> out(T.size());
	vector<int> c_sort = countSort(T, index);
	FORs(i, T.size(), 1){
		// cout << i << " " << T[i].first << " " << index << " AAAAA\n";
		if (((unsigned char) T[i].first[index]) == 0){
			out[start++]=T[i];
		}
		else {
			// cout << (unsigned char) T[i].first[index] - 1 << '\n';
			out[c_sort[(unsigned char) T[i].first[index] - 1]++]=T[i];
		}
	}
	out.swap(T);
}

/* Sorts an array by organizing by its indexes. */
void radixSort(vector<pair<string, int>> T, int size){
	REVs(index, size-1, 1){
		indexSort(T, index);
	}
}

/* Gives a rank depending on which index is in. */
vector<unsigned char> getRanks(vector<pair<string, int>> T){
	vector<unsigned char> out(T.size());
	string prev;
	unsigned char rank=1;
	FORs(i, T.size(), 1){
		if (prev.compare(T[i].first) == 0){
			out[T[i].second]=rank;
		}
		else{
			out[T[i].second]=rank++;
		}
		prev = T[i].first;
	}
	cout << rank;
	return out;
}

/* According to a universal ranking array, sets the ranks of a subset. */
vector<pair<unsigned char, int>> setRanks(vector<pair<string, int>> T, vector<unsigned char> Ranks){
	vector<pair<unsigned char, int>> out(T.size());
	FORs(i, T.size(), 1){
		out[i] = make_pair(Ranks[T[i].second], T[i].second);
	}
	return out;
}

/* Concatenates two unsigned char vectors. */
string buildSub(vector<pair<unsigned char, int>> S1, vector<pair<unsigned char, int>> S2){
	string aux;
	FORs(i, S1.size(), 1){
		aux+=S1[i].first;
	}
	FORs(i, S2.size(), 1){
		aux+=S2[i].first;
	}
	return aux;
}

/* Merges two Suffix Arrays */
vector<pair<unsigned char, int>> merge(vector<pair<unsigned char, int>> S1, vector<pair<unsigned char, int>> S2){
	string text = buildSub(S1, S2);
	int l = text.length();
	vector<pair<unsigned char, int>> S(l);
	standarize(text);
	vector<pair<string, int>> Tall;
	FORs(i, l, 1) Tall.push_back(make_pair(text.substr(i,2), i));
	radixSort(Tall, 2);
	FORs(i, S1.size(), 1) S[Tall[i].second]=S1[i];
	FORs(i, S2.size(), 1) S[Tall[S1.size()+i].second]=S2[i];
	return S;
}

/* Merges two Suffix Arrays of different size. */
vector<pair<unsigned char, int>> getSuffTable(vector<pair<unsigned char, int>> STab, vector<pair<unsigned char, int>> STc, vector<unsigned char> Ranks){
	vector<pair<unsigned char, int>> out;
	int a,b;
	vector<pair<unsigned char, int>>::iterator it1 = STab.begin();
	vector<pair<unsigned char, int>>::iterator it2 = STc.begin();
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

/* Translate an auxiliary representation of a Suffix Array to a Suffix Array. */
vector<int> getSA(vector<pair<unsigned char, int>> ST){
	vector<int> SA(ST.size());
	FORs(i, ST.size(), 1){
		SA[ST[i].second] = i;
	}
	return SA;
}

/* Builds a Suffix Array from a string. */
vector<int> build(string text){
	int l = text.length();
	text = stripAndTrim(text);
	text = standarize(text);
	vector<pair<string, int>> Tall, Ta, Tb, Tc, Tab;
	vector<unsigned char> Ranks;
	vector<pair<unsigned char, int>> STa, STb, STab, STc, ST;
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

/* Verifies a substring is found inside another string. */
int check(string test, vector<int> SA, string text, int index){
	FORs(i, test.length(), 1){
		if (test[i] != text[SA[index+i]]) return -1;
	}
	return index;
}

/* Searches across a Suffix Array for a string. */
int search(string test, vector<int> SA, string text, int begin, int end){
	int ini, fin, mid;
	ini = begin;
	fin = end;
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

/* Returns the ammount of aparitions a substring has on a string, by using its Suffix Array */
int getAmmount(string test, vector<int> SA, string text, int index){
	int a = search(test, SA, text, 0, index);
	int b = search(text, SA, text, index, (int) SA.size());
	if (a != b) return b-a;
	else return 1;
}

/* Returns a string concatenation of a file */
string parse(string file){

	ifstream t(file);
	stringstream buffer;
	buffer << t.rdbuf();

	return buffer.str();
}

/* Runs a test on all files with random substrings. */
void fulltest(){

	int result, ammount;
	int size, a, b;
	clock_t begin, end;
	string test;
	string text;

	FORs(i, 7, 1){
		text = parse(to_string(i+15)+".txt");
		begin = clock();
		vector<int> SA = build(text);
		end = clock();
		cout << "Elapsed building time: " << double(end - begin) / CLOCKS_PER_SEC << '\n';
		size = text.length();
		FORs(i, (size/10), 1){
			a = rand()%size;
			b = rand()%(size-a);
			test = text.substr(a, b);
			begin = clock();
			result = search(test, SA, text, 0, (int) SA.size());
			end = clock();
			if (result != -1){
				begin = clock();
				ammount = getAmmount(test, SA, text, result);
				end = clock();
				cout << ammount << " Ocurrencies were found.\n";
				cout << "Elapsed searching time: " << double(end - begin) / CLOCKS_PER_SEC << '\n';
			}
			else{
				cout << "Not found\n";
				cout << "Elapsed searching time: " << double(end - begin) / CLOCKS_PER_SEC << '\n';
			}
		}
	}
}

int main(){
	
	int testsAmmount;
	int result, ammount;
	string test;
	string file;
	clock_t begin, end;

	cout << "Enter test file: ";
	cin >> file;

	if (file.compare("full test")){
		fulltest();
		return 0;
		}

	string text = parse(file);
	// string text = parse("15.txt");
	begin = clock();
	vector<int> SA = build(text);
	end = clock();
	cout << "Elapsed building time: " << double(end - begin) / CLOCKS_PER_SEC << '\n';

	cout << "Enter number of tests: ";
	cin >> testsAmmount;

	FORs(i, testsAmmount, 1){
		cout << "Enter test substring: ";
		cin >> test;
		result = search(test, SA, text, 0, (int) SA.size());
		if (result != -1){
			begin = clock();
			ammount = getAmmount(test, SA, text, result);
			end = clock();
			cout << ammount << " Ocurrencies were found.\n";
			cout << "Elapsed searching time: " << double(end - begin) / CLOCKS_PER_SEC << '\n';
		}
		else{
			cout << "Not found\n";
			cout << "Elapsed searching time: " << double(end - begin) / CLOCKS_PER_SEC << '\n';
		}
	}

	return 0;
}