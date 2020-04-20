#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left, *right;
};

struct compare
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

void encode(Node* root, string code, unordered_map<char, string> &huffmanCode){
    if(root == NULL) return;

    //Leaf Node
    if(!root->left && !root->right) huffmanCode[root->ch] = code;
    encode(root->left, code+"0", huffmanCode);
    encode(root->right, code+"1", huffmanCode);
}

void decode(Node* root, int &index, string code){
    if(root==NULL) return;
    //Leaf Node
    if(!root->left && !root->right){
        cout << root -> ch;
        return;
    }
    index++;
    if(code[index] == '0') decode(root->left, index, code);
    else decode(root->right, index, code);
}

void huffman(string text){
    //Count frequency of each character
    unordered_map<char, int> freq;
    for(char ch : text){
        freq[ch]++;
    }

    //Create a min Heap of the freq of the characters in the freq map
    priority_queue<Node*, vector<Node*>, compare> pq;


	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	cout << "Original String: " << text << endl;
    cout << "Frequency Count of each character" << endl;
    for (auto pair: freq) {
		cout << pair.first << " : " << pair.second << endl;
	}

    //Create a binary tree(Huffman Tree) of the nodes and the sum of left and right nodes
    while(pq.size() != 1){
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left -> freq + right -> freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    string encodedString = "";
    for(char ch:text){
        encodedString += huffmanCode[ch];
    }

    cout << "Huffman Encoded String: " << encodedString << endl;
    cout << "Huffman Codes" << endl;
    for (auto pair: huffmanCode) {
		cout << pair.first << " : " << pair.second << endl;
	}

	//Decode
	//We can create a reverse hashmap for the huffman code but it will have
	//same time complexity as traversing the huffman tree but it will have the
	//additional space of the reverse hashmap
	int index = -1;
	cout << "Decoded string: ";
    while(1){
        decode(root, index, encodedString);
        if(index == encodedString.size()-1){
            break;
        }
    }
}

int main(){
    string inputText = "aabbbcccc";
    huffman(inputText);
    return 0;

}
