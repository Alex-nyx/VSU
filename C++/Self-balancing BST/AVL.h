#pragma once

namespace AVL_tree
{
	struct avl_tree
	{
		int key;
		int value;

		int height = 0;

		avl_tree* left;
		avl_tree* right;

		avl_tree(int Key, int Value, avl_tree* left_ptr = nullptr, avl_tree* right_ptr = nullptr)
			:key{ Key }, value{ Value }, left{ left_ptr }, right{ right_ptr }
		{}
	};

	namespace impl
	{
		int avl_height(avl_tree* avl)
		{
			return avl ? avl->height : -1;
		}
		int avl_new_height(avl_tree* avl)
		{
			return 1 + (avl_height(avl->left) > avl_height(avl->right) ? avl_height(avl->left) : avl_height(avl->right));
		}
		int avl_balance_factor(avl_tree* avl)
		{
			return avl_height(avl->left) - avl_height(avl->right);
		}

		avl_tree* R_rotation(avl_tree* avl)
		{
			avl_tree* left = avl->left;

			avl->left = avl->left->right;
			left->right = avl;

			avl->height = avl_new_height(avl);
			left->height = avl_new_height(left);

			return left;
		}
		avl_tree* L_rotation(avl_tree* avl)
		{
			avl_tree* right = avl->right;

			avl->right = avl->right->left;
			right->left = avl;

			avl->height = avl_new_height(avl);
			right->height = avl_new_height(right);

			return right;
		}
		avl_tree* avl_rebalance(avl_tree* avl)
		{
			avl->height = avl_new_height(avl);
			
			if (avl_balance_factor(avl) == 2)
			{
				if (avl_balance_factor(avl->left) < 0)
				{
					avl->left = L_rotation(avl->left);
				}

				return R_rotation(avl);
			}
			if (avl_balance_factor(avl) == -2)
			{
				if (avl_balance_factor(avl->right) > 0)
				{
					avl->right = R_rotation(avl->right);
				}

				return L_rotation(avl);
			}

			return avl;
		}
		avl_tree* avl_find_min(avl_tree* avl)
		{
			if (avl->left == nullptr)
			{
				return avl;
			}
			else
			{
				return avl_find_min(avl->left);
			}
		}
		avl_tree* avl_remove_min(avl_tree* avl)
		{
			if (avl->left == nullptr)
			{
				return avl->right;
			}
			else
			{
				avl->left = avl_remove_min(avl->left);
				return avl_rebalance(avl);
			}

		}
	}

	avl_tree* avl_insert(avl_tree* avl, int Key, int Value)
	{
		if (avl == nullptr)
		{
			return new avl_tree(Key, Value);
		}

		else if (Key < avl->key)
		{
			avl->left = avl_insert(avl->left, Key, Value);
		}
		else if (Key > avl->key)
		{
			avl->right = avl_insert(avl->right, Key, Value);
		}

		return impl::avl_rebalance(avl);
	}

	avl_tree* avl_lookup(avl_tree* avl, int Key)
	{
		if (avl == nullptr)
		{
			return nullptr;
		}
		else if (avl->key == Key)
		{
			return avl;
		}
		else if (avl->key > Key)
		{
			return avl_lookup(avl->left, Key);
		}
		else if (avl->key < Key)
		{
			return avl_lookup(avl->right, Key);
		}
	}

	avl_tree* avl_remove(avl_tree* avl, int Key)
	{
		if (avl == nullptr)
		{
			return avl;
		}

		if (avl->key > Key)
		{
			avl->left = avl_remove(avl->left, Key);
		}
		else if (avl->key < Key)
		{
			avl->right = avl_remove(avl->right, Key);
		}
		else
		{
			avl_tree* left = avl->left;
			avl_tree* right = avl->right;

			delete avl;

			if (right == nullptr)
			{
				return left;
			}

			avl = impl::avl_find_min(right);
			avl->right = impl::avl_remove_min(right);
			avl->left = left;
			return impl::avl_rebalance(avl);
		}
		return impl::avl_rebalance(avl);
	}

	void preorder(avl_tree* avl, void (*visitor) (int))
	{
		if (avl == nullptr)
		{
			return;
		}

		visitor(avl->value);
		preorder(avl->left, visitor);
		preorder(avl->right, visitor);
	}
	void inorder(avl_tree* avl, void (*visitor) (int))
	{
		if (avl == nullptr)
		{
			return;
		}

		inorder(avl->left, visitor);
		visitor(avl->value);
		inorder(avl->right, visitor);
	}
	void postorder(avl_tree* avl, void (*visitor) (int))
	{
		if (avl == nullptr)
		{
			return;
		}

		postorder(avl->left, visitor);
		postorder(avl->right, visitor);
		visitor(avl->value);
	}

	void avl_free(avl_tree* avl)
	{
		if (avl == nullptr)
		{
			return;
		}

		avl_free(avl->left);
		avl_free(avl->right);

		delete avl;
	}

	int avl_value(avl_tree* avl)
	{
		return avl->value;
	}
	int avl_key(avl_tree* avl)
	{
		return avl->key;
	}
}