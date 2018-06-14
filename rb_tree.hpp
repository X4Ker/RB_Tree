#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>

template <typename T>
class tree_t
{
private:
	enum {RED, BLACK, DOUBLE_BLACK};
	
    struct node_t {
        node_t * left;
        node_t * right;
        node_t * parent;
        short color;
        T value;
    };
    
    node_t leaves {nullptr, nullptr, nullptr, BLACK, 0};
private:
    node_t * root_;
    void print(std::ostream & stream, node_t * p, unsigned int i=0) const;
    void del (T value, node_t * ptr, node_t * p = 0);
    void delete_(node_t * ptr);
    
    void balance (node_t * ptr);
    void rotate_right(node_t * ptr);
    void rotate_left(node_t * ptr);
    
    void fix_delete(node_t * &node);
    node_t * del(node_t * &root, T data);
    node_t * find_min_value(node_t * &node);
public:
    tree_t ();
	tree_t( tree_t const & ) = delete;
	tree_t & operator=( tree_t const & ) = delete;
    ~tree_t ();
    
    void insert(T value);
    bool find(T value) const;
    void print(std::ostream & stream) const;
    void del(T data);
};

template <typename T>
tree_t<T>::tree_t () {
	root_ = nullptr;
}

template <typename T>
void tree_t<T>::delete_(node_t * ptr) {
	if (ptr->right != &leaves) {
		delete_(ptr->right);
	}
	if (ptr->left != &leaves) {
		delete_(ptr->left);
	}

	delete ptr;
}

template <typename T>
tree_t<T>::~tree_t () {
	
	if (root_) {
		delete_(root_);
	}
}	

template <typename T>
void tree_t<T>::insert(T value) {
	
	if (!root_) {
		root_ = new node_t;
		
		root_->value = value;
		root_->color = BLACK;
		
		root_->parent = nullptr;
		root_->left = &leaves;
		root_->right = &leaves;
		return;
	}
	else {
		node_t * ptr = root_;
	
		while ( ptr ) {
		
			if (value > ptr->value) {
				if (ptr->right != &leaves) {
					ptr = ptr->right;
				}
				else {
					ptr->right = new node_t;
					
					ptr->right->parent = ptr;
					ptr = ptr->right;
					
					ptr->value = value;
					ptr->color = RED;
					
					ptr->right = &leaves;
					ptr->left = &leaves;
					break;
				}
			}
			else {
				if (value < ptr->value) {
					if (ptr->left != &leaves) {
						ptr = ptr->left;
					}
					else {
						ptr->left = new node_t;
						
						ptr->left->parent = ptr;
						ptr = ptr->left;
						
						ptr->value = value;
						ptr->color = RED;
						ptr->right = &leaves;
						ptr->left = &leaves;
						break;
					}
				}
				else break;
			}
		}
		balance (ptr);
	}
}

template <typename T>
void tree_t<T>::rotate_left(node_t * ptr) {
    node_t * right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root_ = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

template <typename T>
void tree_t<T>::rotate_right(node_t * ptr) {
    node_t * left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root_ = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

template <typename T>
void tree_t<T>::balance (node_t * ptr) {
	node_t * parent = nullptr;
    node_t * grandparent = nullptr;
    while (ptr != root_ && ptr->color == RED && ptr->parent->color == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            node_t * uncle = grandparent->right;
            if (uncle->color == RED) {
                uncle->color = BLACK;
                parent->color = BLACK;
                grandparent->color = RED;
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotate_left(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotate_right(grandparent);
                std::swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            node_t * uncle = grandparent->left;
            if (uncle->color == RED) {
                uncle->color = BLACK;
                parent->color = BLACK;
                grandparent->color = RED;
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotate_right(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotate_left(grandparent);
                std::swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    root_->color = BLACK;
}

template <typename T>
bool tree_t<T>::find(T value) const {
	
	node_t * ptr = root_;
	
	while ( ptr != &leaves) {
		if (value == ptr->value) {
			return true;
		}
		else {
			if (value < ptr->value) {
				ptr = ptr->left;
			}
			else {
				ptr = ptr->right;
			}
		}
	}
	
	return false;
}

/*template<int txt = 7, int bg = 0>
std::ostream& color(std::ostream &text) {
	using namespace std;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
    return text;
}*/

template <typename T>
void tree_t<T>::print(std::ostream & stream, node_t * ptr, unsigned int i) const {
	
	if ( ptr == &leaves ) {
		return;
	}
	
	if (ptr->right != &leaves) {
		i++;
		print(stream, ptr->right, i);
		i--;
	}
	
	for (unsigned int j=0; j<=i; j++) {
		stream << "----";
	}
	
	if (ptr->color) {
		stream /*<< color<7, 2>*/ << ptr->value /*<< color<7, 0>*/ << std::endl;
	}
	else {
		stream /*<< color<12, 0>*/ << ptr->value /*<< color<7, 0>*/ << std::endl; 
	}
	
	
	if (ptr->left != &leaves) {
		i++;
		print(stream, ptr->left, i);
		i--;
	}
}

template <typename T>
void tree_t<T>::print(std::ostream & stream) const{
	print(stream, root_);
}

template <typename T>
void tree_t<T>::fix_delete(node_t * &node) {
    if (node == nullptr)
        return;

    if (node == root_) {
    	delete node;
        root_ = nullptr;
        return;
    }
    
    if (node->color == RED || node->left->color == RED || node->right->color == RED) {
        node_t * child = (node->left != nullptr ? node->left : node->right);
		
        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            child->color = BLACK;
            delete node;
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            child->color = BLACK;
            delete node;
        }
    } else {
        node_t * sibling = nullptr;
        node_t * parent = nullptr;
        node_t * ptr = node;
        ptr->color = DOUBLE_BLACK;
        while (ptr != root_ && ptr->color == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotate_left(parent);
                } else {
                    if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                        sibling->color = RED;
                        if(parent->color == RED)
                            parent->color = BLACK;
                        else
                            parent->color = DOUBLE_BLACK;
                        ptr = parent;
                    } else {
                        if (sibling->right->color == BLACK) {
                            sibling->left->color = BLACK;
                            sibling->color = RED;
                            rotate_right(sibling);
                            sibling = parent->right;
                        }
                        sibling->color = parent->color;
                        parent->color = BLACK;
                        sibling->right->color = BLACK;
                        rotate_left(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotate_right(parent);
                } else {
                    if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                        sibling->color = RED;
                        if (parent->color == RED)
                            parent->color = BLACK;
                        else
                            parent->color = DOUBLE_BLACK;
                        ptr = parent;
                    } else {
                        if (sibling->left->color == BLACK) {
                            sibling->right->color = BLACK;
                            sibling->color = RED;
                            rotate_left(sibling);
                            sibling = parent->left;
                        }
                        sibling->color = parent->color;
                        parent->color = BLACK;
                        sibling->left->color = BLACK;
                        rotate_right(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = &leaves;
        else
            node->parent->right = &leaves;
        delete node;
        root_->color = BLACK;
    }
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::find_min_value(node_t * &node) {

    node_t * ptr = node;

    while (ptr->left != &leaves)
        ptr = ptr->left;

    return ptr;
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::del(node_t * &root, T data) {
    if (root == &leaves)
        return root;

    if (data < root->value)
        return del(root->left, data);

    if (data > root->value)
        return del(root->right, data);

    if (root->left == &leaves || root->right == &leaves)
        return root;

    node_t * temp = find_min_value(root->right);
        
    root->value = temp->value;
    
    return del(root->right, temp->value);
}

template <typename T>
void tree_t<T>::del(T data) {
    node_t * node = del(root_, data);
    fix_delete(node);
}

template <typename T>
void action (tree_t<T> & tree, std::string string, std::ostream & stream_o = std::cout ){
	
	std::istringstream stream_i(string);
	char op;
	stream_i >> op;
	
	switch (op) {
		case '+': {
			T value;
			stream_i >> value;
			
			tree.insert(value);
			break;
		}
		case '?': {
			T value;
			stream_i >> value;
			
			if (tree.find(value)) {
				stream_o << "true";
			}
			else stream_o << "false";
			break;
		}
		case '-': {
			T value;
			stream_i >> value;
			
			tree.del(value);
			break;
		}
		case '=': {
			tree.print(stream_o);
			break;
		}
		default: {
			throw std::invalid_argument("Error");
			break;
		}
	}
}
