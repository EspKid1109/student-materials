

// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 {
	namespace fundamentals {
		template <typename T>
		class LinkedList {
			struct Node {
				T data;
				Node* prev = nullptr;
				Node* next = nullptr;
			};
			Node* head = nullptr;
			Node* tail = nullptr;
			int numNodes = 0;
		public:
			class Iterator {
			private:
				Node* iter = nullptr;

			public:
				Iterator(Node* elem) {
					this->iter = elem;
				}
				T operator*() {
					return iter->data;
				}
				Iterator& operator++() {
					iter = iter->next;
					return *this;
				}
				bool operator==(Iterator const& rhs) {
					return this->iter == rhs.iter;
				}
				bool operator!=(Iterator const& rhs) {
					return this->iter != rhs.iter;
				}
			};
			public:
				LinkedList();
				~LinkedList();
				Iterator begin() const;
				Iterator end() const;
				bool isEmpty() const;
				T getFront() const;
				T getBack() const;
				void enqueue(T element);
				void dequeue();
				void pop();
				void clear();
				bool contains(T element) const;
				bool remove(T element);
		};

		// Linked List Functions ******************************************************************
		template <typename T>
		LinkedList<T>::LinkedList() {
			head = nullptr;
			tail = nullptr;
			numNodes = 0;
		}

		template <typename T>
		LinkedList<T>::~LinkedList() {
			clear();
		}

		template <typename T>
		LinkedList<T>::Iterator LinkedList<T>::begin() const {
			return Iterator(this->head);
		}
		template <typename T>
		LinkedList<T>::Iterator LinkedList<T>::end() const {
			return Iterator(nullptr); //this->tail->next
		}
		template <typename T>
		bool LinkedList<T>::isEmpty() const {
			return !(head);
		}
		template <typename T>
		T LinkedList<T>::getFront() const {
			return head->data;
		}
		template <typename T>
		T LinkedList<T>::getBack() const {
			return tail->data;
		}
		template <typename T>
		void LinkedList<T>::enqueue(T element) {
			if (numNodes == 0) { //no head node implies no tail node either
				Node* newNode = new Node();
				newNode->data = element;
				head = newNode;
				tail = newNode;
				this->numNodes++;
			}
			else { //Head exists, just edit tail
				Node* newNode = new Node();
				newNode->data = element;
				newNode->prev = tail;
				tail->next = newNode;
				tail = newNode;
				this->numNodes++;
			}
		}
		template <typename T>
		void LinkedList<T>::dequeue() {
			if (head != nullptr) { //No head, do NOTHING
				if (numNodes == 1) { //Only one element, delete node and set both to nullptr
					this->tail = nullptr;
					delete head;
					this->head = nullptr;
					numNodes--;
				}
				else { // Just taking one off of a list
					Node* temp = this->head;
					this->head = this->head->next;
					delete temp;
					this->head->prev = nullptr;
					numNodes--;
				}
			}
		}
		template <typename T>
		void LinkedList<T>::pop() {
			if (!tail) { //No tail, do NOTHING
				return;
			}
			else if (numNodes == 1) { //Only one element, delete node and set both to nullptr
				this->tail = nullptr;
				delete head;
				this->head = nullptr;
				numNodes--;
			}
			else { // Just taking one off of a list
				Node* temp = tail;
				this->tail = this->tail->prev;
				delete temp;
				this->tail->next = nullptr;
				numNodes--;
			}
		}
		template <typename T>
		void LinkedList<T>::clear() {
			while (this->numNodes != 0) {
				this->dequeue();
			}
		}
		template <typename T>
		bool LinkedList<T>::contains(T element) const {
			bool found = false;
			if (head != nullptr) {
				Node* temp = this->head;
				for (int i = 0; i < this->numNodes; i++) {
					if (temp->data == element) {
						found = true;
						break;
					}
					temp = temp->next;
				}
			}
			return found;
		}
		template <typename T>
		bool LinkedList<T>::remove(T element) {
			if (this->head != nullptr) {
				Node* temp = this->head;
				bool found = false;
				if (head == tail && temp->data == element) { // only one element in list/ check head first
					delete temp;
					head = nullptr;
					tail = nullptr;
					found = true;
					numNodes--;
					return found;
				}
				else {
					if (temp->data == element) { //remove head from long list and set new startpoint
						head = temp->next;
						delete temp;
						found = true;
						numNodes--;
						return found;
					}
					else {
						temp = temp->next;
						for (int i = 1; i < this->numNodes; i++) { // multiple items in list
							if (temp->data == element) {
								temp->prev->next = temp->next;
								if (temp->next != nullptr) {
									temp->next->prev = temp->prev;
								}
								delete temp;
								found = true;
								numNodes--;
								return found;
							}
							temp = temp->next;
						}
					}
				}
				return found;
			}
		}

	
	}
}  // namespace ufl_cap4053::fundamentals
