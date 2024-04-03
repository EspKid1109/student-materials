#include <vector>
#include <queue>

// TreeNode class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {

	template <typename T>
	class TreeNode {
		T data;
		std::vector<TreeNode*> children;

	public:
		TreeNode();
		TreeNode(T element);
		const T& getData() const;
		size_t getChildCount() const;
		TreeNode* getChild(size_t index);
		TreeNode* getChild(size_t index) const;
		void addChild(TreeNode* child);
		TreeNode* removeChild(size_t index);
		void breadthFirstTraverse(void (*dataFunction)(const T)) const;
		void preOrderTraverse(void (*dataFunction)(const T)) const;
		void postOrderTraverse(void (*dataFunction)(const T)) const;
	};

	template <typename T>
	TreeNode<T>::TreeNode() {}

	template <typename T>
	TreeNode<T>::TreeNode(T element) {
		this->data = element;
	}

	template <typename T>
	const T& TreeNode<T>::getData() const {
		return this->data;
	}

	template <typename T>
	size_t TreeNode<T>::getChildCount() const {
		return this->children.size();
	}

	template <typename T>
	TreeNode<T>* TreeNode<T>::getChild(size_t index) {
		if (this->children.size() < index) {
			return nullptr;
		}
		return this->children[index];
	}

	template <typename T>
	TreeNode<T>* TreeNode<T>::getChild(size_t index) const {
		if (this->children.size() < index) {
			return nullptr;
		}
		return this->children[index];
	}

	template <typename T>
	void TreeNode<T>::addChild(TreeNode* child) {
		if (child != nullptr) {
			this->children.push_back(child);
		}
	}

	template <typename T>
	TreeNode<T>* TreeNode<T>::removeChild(size_t index) {
		if (this->children.size() < index) {
			return nullptr;
		}
		TreeNode* temp = this->children[index];
		this->children.erase(this->children.begin() + index);
		return temp;
	}

	template <typename T>
	void TreeNode<T>::breadthFirstTraverse(void (*dataFunction)(const T)) const {
		std::queue<TreeNode*> q;
		dataFunction(this->getData());
		for (int i = 0; i < this->children.size(); i++) {
			q.push(this->children[i]);
		}

		while (!q.empty()) {
			TreeNode* temp = q.front();
			q.pop();
			dataFunction(temp->getData());
			for (int i = 0; i < temp->children.size(); i++) {
				q.push(temp->children[i]);
			}
		}
	}

	template <typename T>
	void TreeNode<T>::preOrderTraverse(void (*dataFunction)(const T)) const {
		dataFunction(this->getData());
		for (int i = 0; i < this->children.size(); i++) {
			this->children[i]->preOrderTraverse(dataFunction);
		}
	}

	template <typename T>
	void TreeNode<T>::postOrderTraverse(void (*dataFunction)(const T)) const {
		for (int i = 0; i < this->children.size(); i++) {
			this->children[i]->postOrderTraverse(dataFunction);
		}
		dataFunction(this->getData());
	}

}}  // namespace ufl_cap4053::fundamentals
