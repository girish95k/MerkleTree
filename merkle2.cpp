#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/*
	Action Points
		Write a class Merkle
		Write a class Node
		Improve the hash function
*/

using namespace std;

template <typename T>
class Merkle
{
	public:
	Merkle(initializer_list<T>);
	Merkle(int);
	Merkle();
	Merkle(const Merkle&);
	~Merkle();
	string make_merkle(T, int);
	private:
	string root;
	T elements;
	int size;
};

template <typename T>
Merkle<T>::Merkle(initializer_list<T> list)
{
	copy(list.begin(), list.end(), elements);
}

string hash_fun(string, string);

int count=0;

int main()
{
	static const string arr[] = {
		"Girish",
		"Krishnamurthy",
		"Pranav",
		"Singhania",
		"Vinitha",
		"Raj",
		"Jewy",
		"Sawn",
		"Kk",
		"Deng"};
	vector<string> sample_hashes(arr, arr + sizeof(arr)/sizeof(arr[0]));
	
	Merkle<vector<string>> m({
		"Girish",
		"Krishnamurthy",
		"Pranav",
		"Singhania",
		"Vinitha",
		"Raj",
		"Jewy",
		"Sawn",
		"Kk",
		"Deng"});
	
	//cout << "\nMerkle Root: " << make_merkle(sample_hashes) << endl;
}

template <typename T>
string Merkle<T>::make_merkle(T hash_vector)
{
	count+=1;
	if(hash_vector.size()==1)
	{
		//This is the Merkle Root
		return hash_vector[0];
	}
	
	//This vector stores the new set of branhces in that level to pass to the next level
	vector<string> new_hash_vector;
	
	cout << "\nNumber of branches in round " << count << " is " << hash_vector.size() << "\n";
	
	//Collects two elements from a level in each iteration
	for(int i=0; i<hash_vector.size()-1; i=i+2)
	{
		cout << "Elements to combine: " << hash_vector[i] << " and " << hash_vector[i+1];
		new_hash_vector.push_back(hash_fun(hash_vector[i], hash_vector[i+1]));
		cout << " resulting in " << new_hash_vector[new_hash_vector.size()-1] << "\n";
	}
	
	//In case there are an odd number of branches, hash the last branch with itself
	if((hash_vector.size()%2)==1)
	{
		cout<< "Elements to combine: " << hash_vector[hash_vector.size()-1] << " with itself resulting in ";
		new_hash_vector.push_back(hash_fun(hash_vector[hash_vector.size()-1], hash_vector[hash_vector.size()-1]));
		cout << new_hash_vector[new_hash_vector.size()-1] << "\n";
	}
	
	return make_merkle(new_hash_vector);
}

string hash_fun(string first, string second)
{
	hash<string> str_hash;
	stringstream ss;
	ss << str_hash(first+second);
	return ss.str();
}