#pragma once 

template<class K,class V>
struct BSTNode
{
	//KV
	K _key;
	V _value;

	BSTNode* _left;
	BSTNode* _right;

	BSTNode(const K& key,
			const V& value)
			: _key(key)
			, _value(value)
			, _left(NULL)
			, _right(NULL)
		{}
};

template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;

public:
	BSTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; // 搜索二叉树要求无重复关键码
			}
		}

		//此时不知道链在左子树_left还是右子树_right上，分情况
		if (parent->_key > key)
			parent->_left = new Node(key, value);
		else if (parent->_key < key)
			parent->_right = new Node(key, value);

		return true;
	}

	void Insert_R(const K& key, const V& value)
	{
		_Insert_R(_root, key, value);
	}

	Node* Find_R(const K& key)
	{
		Node* ret = _Find_R(_root, key);
		return ret;
	}

	Node* Find(const K& key)
	{
		if (_root == NULL)
			return NULL;

		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else // 找到返回
				return cur;
		}
		return false;
	}

	bool Rmove(const K& key)
	{
		// 无节点
		if (_root == NULL)
			return false;

		//一个节点
		else if (_root->_left == NULL && _root->_right == NULL)
		{
			if (_root->_key == key)
			{
      	delete _root;
				_root = NULL;
				return true;
			}
		}

		//多个节点
		else
		{
			Node* cur = _root;
			Node* parent = NULL; // 记录 cur 的父节点
			while (cur)
			{
				if (cur->_key > key) // 左子树上找
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)  // 右子树上找
				{
					parent = cur;
					cur = cur->_right;
				}
				else  // 找到要删除的节点
				{
					if (cur->_left == NULL) // 要删除的节点无左子树
					{
						if (parent == NULL)
						{
							_root = cur->_right;
							delete cur;
							cur = NULL;
							return true;
						}

						if (parent->_key < cur->_key)
						{
							parent->_right = cur->_right;
						}

						else if (parent->_key > cur->_key)
						{
							parent->_left = cur->_right;
						}
						delete cur;
						cur = NULL;
						return true;
					}

					else if (cur->_right == NULL) // 要删除的节点无右子树
					{
						if (parent == NULL)
						{
							_root = cur->_left;
							delete cur;
							cur = NULL;
							return true;
						}

						if (parent->_key > cur->_key)
						{
							parent->_left = cur->_left;
						}
						else if (parent->_key < cur->_key)
						{
							parent->_right = cur->_left;
						}

						delete cur;
						cur = NULL;
						return true;
					}

					else // 左右子树都不为空，两种情况
					{
						Node* firstLeft = cur->_right;

						if (firstLeft->_left == NULL)
						{
							swap(cur->_key, firstLeft->_key);
							swap(cur->_value, firstLeft->_value);
							cur->_right = firstLeft->_right;
							delete firstLeft;
							firstLeft = NULL;
							return true;
						}

						else
						{
							Node* tmp = firstLeft; //tmp用来找最左节点

							while (tmp->_left)
							{
								firstLeft = tmp;
								tmp = tmp->_left;
							}

							swap(cur->_key, tmp->_key);
							swap(cur->_value, tmp->_value);

							firstLeft->_left = tmp->_right;
							delete tmp;
							tmp = NULL;
							return true;
						}
					}
				}
			}
		}
	}

	void Rmove_R(const K& key)
	{
		_Remove_R(_root, key);
	}

	void Inoder()
	{
		_Inoder(_root);
		cout << endl;
	}

protected:

	void _Inoder(Node* root)
	{
		if (root == NULL)
			return;

		_Inoder(root->_left);
		cout << root->_key << " ";
		_Inoder(root->_right);
	}

	void _Insert_R(Node*& root,const K& key,const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return;
		}
		if (root->_key > key)
		{
			_Insert_R(root->_left, key, value);
		}
		else if (root->_key < key)
		{
			_Insert_R(root->_right, key, value);
		}
		else // 不能有重复的关键码，这里do nothing!
			return;
	}

	Node* _Find_R(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;

		if (root->_key > key)
		{
			return _Find_R(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Find_R(root->_right, key);
		}
		else  // 找到返回
			return root;
	}

	void _Remove_R(Node* root, const K& key)
	{
		if (root == NULL) //空节点
			return;

		if (root->_left == NULL && root->_right == NULL) // 一个节点，若为该删除节点则删除
		{
			if (root->_key == key)
			{
				delete root;
				root = NULL;
				return;
			}
			else
				return;  // 不是删除的节点，返回
		}

		//在左子树上递归找
		if (root->_key > key)
		{
			_Remove_R(root->_left, key);
		}

		//在右子树上递归找
		else if (root->_key < key)
		{
			_Remove_R(root->_right, key);
		}

		//找到该节点
		else
		{
			Node* del = NULL;

			//
			if (root->_left == NULL)
			{
				del = root;
				root = root->_right;
				delete del;
				del = NULL;
			}

			//
			else if (root->_right == NULL)
			{
				del = root;
				root = root->_left;
				delete del;
				del = NULL;
			}

			else
			{
				Node* firstLeft = root->_right;
				Node* tmp = firstLeft;

				//找最左节点
				while (tmp->_left)
				{
					firstLeft = tmp;
					tmp = tmp->_left;
				}

				//找到最左节点，保存，交换，删除
				swap(tmp->_key, root->_key);
				swap(tmp->_value, root->_value);
				del = root;
				root = tmp->_right;
				delete del; 
				del = NULL;
			}
		}
	}

protected:
	Node* _root;
};


void TestSearchBinaryTree()
{
	typedef BSTNode<int, int> Node;
	BSTree<int, int> bst;

	//非递归测试模块
	bst.Insert(5, 1);
	bst.Insert(1, 1);
	bst.Insert(8, 1);
	bst.Insert(3, 1);
	bst.Insert(6, 1);
	bst.Insert(2, 1);
	bst.Insert(9, 1);
	bst.Insert(5, 1);
	bst.Insert(7, 1);
	bst.Insert(4, 1);
	bst.Insert(0, 1);
	bst.Inoder();

	Node* ret = bst.Find(6);
	if (ret == NULL)
		cout << "NOT EXIST!" << endl;

	cout << "Find : " << ret->_key << endl;


	bst.Rmove(2);
	bst.Rmove(6);
	bst.Rmove(0);
	bst.Rmove(1);
	bst.Rmove(3);
	bst.Rmove(9);
	bst.Rmove(5);
	bst.Rmove(4);
	bst.Rmove(7);
	bst.Rmove(8);
	bst.Inoder();



	//递归测试模块
	bst.Insert_R(5, 1);
	bst.Insert_R(1, 1);
	bst.Insert_R(8, 1);
	bst.Insert_R(3, 1);
	bst.Insert_R(6, 1);
	bst.Insert_R(2, 1);
	bst.Insert_R(9, 1);
	bst.Insert_R(5, 1);
	bst.Insert_R(7, 1);
	bst.Insert_R(4, 1);
	bst.Insert_R(0, 1);
	bst.Inoder();

	Node* ret_R = bst.Find_R(5);
	if (ret_R == NULL)
		cout << "NOT EXIST!" << endl;

	cout << "Find : " << ret_R->_key << endl;


	bst.Rmove(2);
	bst.Rmove(6);
	bst.Rmove(0);
	bst.Rmove(1);
	bst.Rmove(3);
	bst.Rmove(9);
	bst.Rmove(5);
	bst.Rmove(4);
	bst.Rmove(7);
	bst.Rmove(8);
	bst.Inoder();

}
