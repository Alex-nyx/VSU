#pragma once
#include <string>
#include <fstream>

struct bs_tree
{
	std::string str;

	bs_tree* left = nullptr;
	bs_tree* right = nullptr;

	bs_tree(std::string str_, bs_tree* left_ = nullptr, bs_tree* right_ = nullptr)
		:str{ str_ } , left{ left_ }, right{ right_ }
	{}
};

bs_tree* bst_insert(std::string s, bs_tree* tree)
{
	if (tree == nullptr)
	{
		return new bs_tree{ s };
	}

	if (s < tree->str)
	{
		tree->left = bst_insert(s, tree->left);
	}
	else
	{
		tree->right = bst_insert(s, tree->right);
	}
	return tree;
}

void bst_free(bs_tree* &tree)
{
	if (tree == nullptr)
	{
		return;
	}

	bst_free(tree->left);
	bst_free(tree->right);

	delete tree;
	tree = nullptr;
}

bs_tree* bst_find(std::string s, bs_tree* tree)
{
	if (tree == nullptr || s == tree->str)
	{
		return tree;
	}

	if (s < tree->str)
	{
		return bst_find(s, tree->left);
	}
	else
	{
		return bst_find(s, tree->right);
	}
}

bs_tree* create_from_file(std::string file_name)
{
	std::ifstream ifs{ file_name };
	std::string word;
	bs_tree* tree = nullptr;
	while (ifs >> word)
	{
		tree = bst_insert(word, tree);
	}

	return tree;
}

void bst_traverse(bs_tree* tree, void (*visitor)(std::string))
{
	if (tree == nullptr)
	{
		return;
	}
	
	bst_traverse(tree->left, visitor);
	visitor(tree->str);
	bst_traverse(tree->right, visitor);
}

bool bst_at(std::string s, bs_tree* tree)
{
	if (bst_find(s, tree) == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}
