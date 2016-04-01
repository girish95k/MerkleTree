#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string merkle(vector<string>);
string hash_fun(string, string);

int count=0;

int main()
{
	static const string arr[] = {
		"aa",
		"bb",
		"cc",
		"dd",
		"ee",
		"11",
		"22",
		"33",
		"44",
		"55"};
	vector<string> sample_hashes(arr, arr + sizeof(arr)/sizeof(arr[0]));
	
	cout << "Merkle Root: " << merkle(sample_hashes) << endl;
}

string merkle(vector<string> hash_vector)
{
	count+=1;
	if(hash_vector.size()==1)
	{
		//This is the Merkle Root
		return hash_vector[0];
	}
	
	vector<string> new_hash_vector;
	
	cout << "\nNumber of branches in round " << count << " is " << hash_vector.size() << "\n";
	
	for(int i=0; i<hash_vector.size()-1; i=i+2)
	{
		cout << "Elements to combine: " << hash_vector[i] << " and " << hash_vector[i+1];
		new_hash_vector.push_back(hash_fun(hash_vector[i], hash_vector[i+1]));
		cout << " resulting in " << new_hash_vector[new_hash_vector.size()-1] << "\n";
	}
	
	if((hash_vector.size()%2)==1)
	{
		cout<< "Elements to combine: " << hash_vector[hash_vector.size()-1] << " with itself resulting in ";
		new_hash_vector.push_back(hash_fun(hash_vector[hash_vector.size()-1], hash_vector[hash_vector.size()-1]));
		cout << new_hash_vector[new_hash_vector.size()-1] << "\n";
	}
	
	return merkle(new_hash_vector);
}
string hash_fun(string first, string second)
{
	hash<string> str_hash;
	stringstream ss;
	ss << str_hash(first+second);
	return ss.str();
}