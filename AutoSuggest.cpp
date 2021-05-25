#include "bits/stdc++.h"
using namespace std;

// {A-Z a-z ' - _}
const int Character_Set_Size = 52 + 3; // 3 extra  for ' -  _
int index_corresponding_to_character(char x)
{
	if ('a' <= x && x <= 'z')return x - 'a';
	if ('A' <= x && x <= 'Z') return x - 'A' + 26;
	if (x == '\'')return Character_Set_Size - 1;
	if (x == '-')return Character_Set_Size - 2;
	return Character_Set_Size - 3; // for _
}
char character_corresponding_to_index(int x)
{
	if (0 <= x && x <= 25)return x + 'a';
	if (26 <= x && x <= 51)return x - 26 + 'A';
	if (x == Character_Set_Size - 1)return '\'';
	if (x == Character_Set_Size - 2)return '-';
	return '_';
}
struct Trie_Node
{
	bool terminal;
	Trie_Node *child[Character_Set_Size];
};

Trie_Node* init()
{
	Trie_Node* node = new Trie_Node;
	node->terminal = false;
	for (int i = 0; i < Character_Set_Size; ++i)
	{
		node->child[i] = nullptr;
	}
	return node;
}

void insert_word(Trie_Node*root, string word)
{
	Trie_Node*temp = root;
	for (int i = 0; word[i]; ++i)
	{
		// node doesn't exist
		int index = index_corresponding_to_character(word[i]);
		if (temp->child[index] == nullptr)
		{
			temp->child[index] = init();
		}
		temp = temp->child[index];
		if (word[i + 1] == '\0')
		{
			temp->terminal = true;
		}
	}
}


void get_All_Strings(Trie_Node*curr_node, string &curr_word, bool &Completed)
{
	// curr_node is a complete word , so a perfect suggestion
	if (curr_node->terminal)Completed = true, cout << curr_word << "\n";
	for (int i = 0; i < Character_Set_Size; ++i)
	{
		// node doesn't exist
		if (curr_node->child[i] == nullptr)continue;
		char ch = character_corresponding_to_index(i);
		curr_word.push_back(ch);
		get_All_Strings(curr_node->child[i], curr_word, Completed);
		curr_word.pop_back();
	}
}
void AutoComplete(Trie_Node*root, string prefix, bool Suggestions_found = false)
{
	Trie_Node* temp = root;
	string curr_word = "";
	// Traverse till the branch with word same as prefix , and then get all complete words in every branch.
	for (int i = 0; prefix[i]; ++i)
	{
		// edge to i'th character doesn't exist ,  so no suggestions
		if (temp->child[index_corresponding_to_character(prefix[i])] == nullptr)
		{
			insert_word(root, prefix);
			cout << "Sorry !!!   No Suggestions Found. \n";
			return;
		}
		curr_word.push_back(prefix[i]);
		int index = index_corresponding_to_character(prefix[i]);
		temp = temp->child[index];
	}
	bool Completed = false;
	get_All_Strings(temp, curr_word, Completed);
	Suggestions_found |= Completed;
	// Prefix exists  in trie but no further suggestions available.
	if (!Suggestions_found)insert_word(root, prefix), cout << "Sorry !!!   No Suggestions Found. \n";
}


int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(nullptr);

	Trie_Node* root = init();
	ifstream file ("words.txt");
	string s;
	while (getline(file, s))
	{
		insert_word(root, s);
	}

	cout << "Option 1 :  Insert word in Dictionary\n";
	cout << "Option 2 :  Try AutoComplete Feature\n";
	cout << "Option 3 :  Exit\n";
	int option = 0;
	while (1)
	{
		cin >> option;
		if (option == 1)
		{
			string word;
			cin >> word;
			insert_word(root, word);
			cout << "Added\n";
		}
		else if (option == 2)
		{
			string word;
			cin >> word;
			AutoComplete(root, word);
		}
		else if (option == 3)
		{
			cout << "Thank You !\n";
			exit(0);
		}
		else
		{
			cout << "Invalid Choice \n Please Try Again!\n";
		}
	}

	return 0;
}
