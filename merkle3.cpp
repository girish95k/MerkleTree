#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
class Merkle
{
	private:
	int count;
	int size;
	string root;
	T elements;
	
	public:
	Merkle()
	{
		size = 0;
		count = 0;
	}
	Merkle(int s)
	:size(s)
	{
		//TODO
		count = 0;
	}
	
	Merkle(T data)
	{
		count = 0;
		elements=data;
		root = make_merkle(elements);
	}
	
	//Copy Assignment
	Merkle& operator=(const Merkle& rhs)
	:root(rhs.root), ??
	{
		//Ok
	}
	Merkle& operator=(Merkle&& rhs);
	Merkle(const Merkle&);
	Merkle(Merkle&&);
	string make_merkle(T hash_data)
	{
		count+=1;
		if(hash_data.size()==1)
		{
			count = 0;
			//This is the Merkle Root
			return hash_data[0];
		}
		
		//This vector stores the new set of branhces in that level to pass to the next level
		vector<string> new_hash_data;
		
		cout << "\nNumber of branches in round " << count << " is " << hash_data.size() << "\n";
		
		//Collects two elements from a level in each iteration
		for(int i=0; i<hash_data.size()-1; i=i+2)
		{
			cout << "Elements to combine: " << hash_data[i] << " and " << hash_data[i+1];
			new_hash_data.push_back(make_hash(hash_data[i], hash_data[i+1]));
			cout << " resulting in " << new_hash_data[new_hash_data.size()-1] << "\n";
		}
		
		//In case there are an odd number of branches, hash the last branch with itself
		if((hash_data.size()%2)==1)
		{
			cout<< "Elements to combine: " << hash_data[hash_data.size()-1] << " with itself resulting in ";
			new_hash_data.push_back(make_hash(hash_data[hash_data.size()-1], hash_data[hash_data.size()-1]));
			cout << new_hash_data[new_hash_data.size()-1] << "\n";
		}
		
		return make_merkle(new_hash_data);
	}
	
	string make_hash(string first, string second)
	{
		hash<string> str_hash;
		stringstream ss;
		ss << str_hash(first+second);
		return ss.str();
	}
	
	string get_root()
	{
		return root;
	}
	
};


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
	
	Merkle<vector<string>> m(sample_hashes);
	
	cout << m.get_root();
	//Where you at NIgga?
}