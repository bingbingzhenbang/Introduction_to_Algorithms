#include <queue>
#include <memory>
#include <iostream>

using namespace std;

struct CodeNode
{
	char m_code;
	int m_frequency;
	CodeNode* m_parent;
	shared_ptr<CodeNode> m_left;
	shared_ptr<CodeNode> m_right;
	CodeNode(char code, int frequency)
		: m_code(code), m_frequency(frequency), m_parent(0), m_left(0), m_right(0){}
};

typedef shared_ptr<CodeNode> CodeNodePtr;

struct CodeNodeCompare
{
	bool operator()(CodeNodePtr &left, CodeNodePtr &right)
	{
		return left->m_frequency > right->m_frequency;
	}
};

CodeNodePtr Huffman(vector<CodeNodePtr> &nodes)
{
	if (nodes.empty())
		return 0;
	priority_queue<CodeNodePtr, vector<CodeNodePtr>, CodeNodeCompare> Q(nodes.begin(), nodes.end());
	while (Q.size() > 1)
	{
		CodeNodePtr x = Q.top();
		Q.pop();
		CodeNodePtr y = Q.top();
		Q.pop();
		CodeNodePtr z = CodeNodePtr(new CodeNode(0, x->m_frequency + y->m_frequency));
		z->m_left = x;
		z->m_right = y;
		x->m_parent = z.get();
		y->m_parent = z.get();
		Q.push(z);
	}
	CodeNodePtr z = Q.top();
	Q.pop();
	return z;
}

void testHuffmanCodes()
{
	vector<char> codes = { 'a', 'b', 'c', 'd', 'e', 'f' };
	vector<int> frequencies = { 45, 13, 12, 16, 9, 5 };
	//vector<char> codes = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	//vector<int> frequencies = { 1, 1, 2, 3, 5, 8, 13, 21 };
	int size = codes.size();
	vector<CodeNodePtr> nodes;
	for (int i = 0; i < size; ++i)
		nodes.push_back(CodeNodePtr(new CodeNode(codes[i], frequencies[i])));

	CodeNodePtr root = Huffman(nodes);
	for (int i = 0; i < size; ++i)
	{
		CodeNodePtr codenode = nodes[i];
		vector<int> code;
		CodeNode *q = codenode.get();
		CodeNode *p = q->m_parent;
		while (p != 0)
		{
			if (q == p->m_left.get())
				code.push_back(0);
			else
				code.push_back(1);
			q = p;
			p = p->m_parent;
		}
		cout << codenode->m_code << " : ";
		for (auto itr = code.rbegin(); itr != code.rend(); ++itr)
			cout << *itr << " ";
		cout << endl;
	}
}