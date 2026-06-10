template <typename T> struct queueNode {
    T val;
    queueNode *next;

    queueNode() : val(0), next(nullptr) {};
    queueNode(T x) : val(x), next(nullptr) {};
    queueNode(T x, queueNode *next) : val(x), next(next) {};
};
template <typename T> class Queue {
    queueNode<T> *head = nullptr;
    queueNode<T> *tail = nullptr;
    int length = 0;

  public:
    void enqueue(T val) {
        queueNode<T> *temp = new queueNode<T>(val);
        if (!length) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
        length++;
    }
    T dequeue() {
        T res = head->val;
        queueNode<T> *toDelete = head;
        head = head->next;
        length--;
        delete toDelete;
        return res;
    }
    T peek() { return head->val; }
    int size() { return length; }
};
