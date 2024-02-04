#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <unistd.h>
#include <stack>
using namespace std;

template <typename T>
class Queue
{
private:
    static const int Q_SIZE = 5;
    T arr[Q_SIZE];
    int front;
    int rear;
    size_t size;

public:
    Queue() : front(-1), rear(-1), size(0) {}

    bool isEmpty() const
    {
        return front == -1;
    }

    bool isFull() const
    {
        return (rear + 1) % Q_SIZE == front;
    }

    void enqueue(const T& value)
    {
        if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            if (isFull())
            {
                dequeue();
            }

            rear = (rear + 1) % Q_SIZE;
        }

        arr[rear] = value;
        size++;
    }


    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty! Cannot Dequeue From An Empty Queue!" << endl;
            return;
        }

        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % Q_SIZE;
        }

        size--;
    }

    T& topElement()
    {
        if (!isEmpty())
        {
            return arr[front];
        }

        static T DefaultValue;
        return DefaultValue;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        for(int i = front; i != rear;  i = (i + 1) % Q_SIZE)
        {
            arr[i].print();
        }

        arr[rear].print();
    }

    T& search(const T& value)
    {
        for (int i = front; i != rear; i = (i + 1) % Q_SIZE)
        {
            if (arr[i] == value)
            {
                return arr[i];
            }
        }

        static T DefaultValue;
        return DefaultValue;
    }

    void deleting(const T& value)
    {
        if (isEmpty())
        {
            cout << "Queue is empty! Cannot delete from an empty queue!" << endl;
            return;
        }

        Queue<T> temp;

        while (!isEmpty())
        {
            T x = topElement();
            dequeue();

            if (x != value)
            {
                temp.enqueue(x);
            }
        }

        while (!temp.isEmpty())
        {
            T y = temp.topElement();
            temp.dequeue();
            enqueue(y);
        }
    }

};

struct activity
{
    bool like;
    bool comment;
    string commentContent;
    bool post;
    string postContent;
    time_t now;
    char now_str[9];
    int id;

    activity(): like(0), comment(0), post(0), commentContent("Unknown"), postContent("Unknown")
    {
        now = time(0);
        struct tm* now_tm = std::localtime(&now);
        std::strftime(now_str, 9, "%H:%M:%S", now_tm);
    }

    void set(int i)
    {
        char choice;
        cout << "[1]. Like   [2]. Comment   [3]. Post" << endl;
        cin >> choice;
        id = i;

        switch(choice)
        {
        case '1':
        {
            like = 1;
            break;
        }

        case '2':
        {
            comment = 1;
            cout << "Enter Comment Content: ";
            cin.ignore();
            getline(cin, commentContent);
            break;
        }

        case '3':
        {
            post = 1;
            cout << "Enter post Content: ";
            cin.ignore();
            getline(cin, postContent);
            break;
        }

        default:
            cout << "INVALID INPUT!" << endl;
            system("pause");
        }

    }

    bool operator==(const activity& other)
    {
        return (id == other.id);
    }

    bool operator!=(const activity& other)
    {
        return (id != other.id);
    }

    void print()
    {
        cout << "Activity ID -> " << id << " :- " << endl;
        if(like == true)
        {
            cout << "The User Liked A Post" << " At " << now_str << endl;
        }
        else if (post == true)
        {
            cout << "The User Added A Post\"" << postContent << "\"" << " At " << now_str << endl;
        }
        else
        {
            cout << "The User Commented On A Post\"" << commentContent << "\"" << " At " << now_str << endl;
        }
    }
};

unsigned int hashing(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

class node
{
public:
    int key;    // User ID
    Queue<activity> Q;
    unsigned int hashValue;
    int height;
    node* left;
    node* right;
    int likesCounter;
    int commentCounter;
    int postCounter;
    node(int x)
    {
        key = x;
        hashValue = hashing(x);
        height = 1;
        left = right = nullptr;
        likesCounter = commentCounter = postCounter = 0;
    }
};

template <typename T>
class AVL
{
public:
    node* root = nullptr;
    int n = 0;

    void insert(const T& x)
    {
        root = insertUtil(root, x);
    }

    void remove(T x)
    {
        root = removeUtil(root, x);
    }

    node* search(T x)
    {
        return searchUtil(root,x);
    }

    void inorder()
    {
        inorderUtil(root);
    }

    void counterInorder(node* head)
    {
        if(head == nullptr) return;
        counterInorder(head->left);
        cout << "For User Whose ID is -> " << head->key << " :- " << endl;
        cout << "User's Likes -> " << head -> likesCounter << endl;
        cout << "User's Comments -> " << head -> commentCounter << endl;
        cout << "User's Posts -> " << head -> postCounter << endl;
        cout << "---------------------------" << endl;
        counterInorder(head->right);
    }

    node* activeUser()
    {
        node* current = root;
        node* mostActive = root;
        int maxCounter = 0;

        stack<node*> s;

        s.push(current);

        while (!s.empty())
        {
            current = s.top();
            s.pop();

            int currentCounter = current->likesCounter + current->commentCounter + current->postCounter;

            if (currentCounter > maxCounter)
            {
                mostActive = current;
                maxCounter = currentCounter;
            }

            if (current->right)
                s.push(current->right);

            if (current->left)
                s.push(current->left);
        }

        return mostActive;
    }

private:
    int height(node* head) const
    {
        if(head == nullptr) return 0;
        return head->height;
    }

    node* rightRotation(node* head)
    {
        node* newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node* leftRotation(node* head)
    {
        node* newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    void inorderUtil(node* head)
    {
        if(head == nullptr) return;
        inorderUtil(head->left);
        cout << "For User Whose ID is -> " << head->key << " :- " << endl;
        head->Q.display();
        cout << "---------------------------" << endl;
        inorderUtil(head->right);
    }

    node* insertUtil(node* head, T x)
    {
        if(head == nullptr)
        {
            n++;
            node* temp = new node(x);
            return temp;
        }

        unsigned int hx = hashing(x);
        unsigned int hkey = head->hashValue;

        if(hx < hkey) head->left = insertUtil(head->left, x);
        else if(hx > hkey) head->right = insertUtil(head->right, x);
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal > 1)
        {
            if(hashing(x) < head->left->hashValue)
            {
                return rightRotation(head);
            }
            else
            {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if(bal < -1)
        {
            if(hashing(x) > head->right->hashValue)
            {
                return leftRotation(head);
            }
            else
            {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }

        return head;
    }

    node* removeUtil(node* head, T x)
    {
        if(head == nullptr) return nullptr;

        unsigned int hx = hashing(x);
        unsigned int hkey = head->hashValue;

        if(hx < hkey)
        {
            head->left = removeUtil(head->left, x);
        }
        else if(hx > hkey)
        {
            head->right = removeUtil(head->right, x);
        }
        else
        {
            if(head->right == nullptr)
            {
                node* l = head->left;
                delete(head);
                head = l;
            }
            else if(head->left == nullptr)
            {
                node* r = head->right;
                delete(head);
                head = r;
            }
            else
            {
                node* r = head->right;
                while(r->left != nullptr) r = r->left;
                head->key = r->key;
                head->hashValue = r->hashValue;
                head->right = removeUtil(head->right, r->key);
            }
        }

        if(head == nullptr) return head;
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal > 1)
        {
            if(height(head->left) >= height(head->right))
            {
                return rightRotation(head);
            }
            else
            {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if(bal < -1)
        {
            if(height(head->right) >= height(head->left))
            {
                return leftRotation(head);
            }
            else
            {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }

        return head;
    }

    node* searchUtil(node * head, T x)
    {
        if(head == nullptr) return nullptr;

        unsigned int hx = hashing(x);
        unsigned int hkey = head->hashValue;

        if(hx == hkey)
        {
            if (head->key == x)
            {
                return head;
            }
            else
            {
                return nullptr;
            }
        }
        else if(hx < hkey)
        {
            return searchUtil(head->left, x);
        }
        else if(hx > hkey)
        {
            return searchUtil(head->right, x);
        }
    }
};

class ActivityTracker
{
private:
    AVL<int> user_t;
    int activityCounter;

public:

    ActivityTracker(): activityCounter(0) {}

    void addActivity()
    {
        system("cls");
        system("color 7");

        char choice1;
        do
        {
            system("cls");
            cout << "[1]. Existing User   [2]. New User   [0]. Return To Main Menu" << endl;
            cin >> choice1;
            activityCounter++;

            switch(choice1)
            {

            case '1':
            {
                int id;
                cout << "Enter Existing User ID: ";
                cin >> id;

                node* result = user_t.search(id);

                if(result != nullptr)
                {
                    cout << "\nUSER FOUND!" << endl;
                    activity newActivity;
                    newActivity.set(activityCounter);
                    result -> Q.enqueue(newActivity);

                    if(newActivity.like == 1)
                        result -> likesCounter++;
                    else if(newActivity.comment == 1)
                        result -> commentCounter++;
                    else
                        result -> postCounter++;

                }
                else
                {
                    cout << "USER NOT FOUND!" << endl;
                    activityCounter--;
                    system("pause");
                }

                break;
            }

            case '2':
            {
                cout << "The ID Of The New User -> " << user_t.n + 1 << endl;
                activity newActivity;
                newActivity.set(activityCounter);

                if(newActivity.like == 0 && newActivity.comment == 0 && newActivity.post == 0)
                {
                    activityCounter--;
                    break;
                }

                user_t.insert(user_t.n + 1);
                node* result = user_t.search(user_t.n);
                result->Q.enqueue(newActivity);
                if(newActivity.like == 1)
                    result -> likesCounter++;
                else if(newActivity.comment == 1)
                    result -> commentCounter++;
                else
                    result -> postCounter++;
                break;
            }

            case '0':
                break;

            default:
                cout << "Error Input!" << endl;
                sleep(2);
            }
        }
        while(choice1 != '0');

        system("cls");
    }

    void removeActivity()
    {
        system("cls");
        system("color 7");

        char choice1;
        do
        {
            cout << "[1]. Enter Existing User ID   [0]. Return To Main Menu" << endl;
            cin >> choice1;

            switch(choice1)
            {

            case '1':
            {
                int id;
                cout << "Enter Existing User ID: ";
                cin >> id;

                node* result = user_t.search(id);

                cout << "[List of Activities For This User]:- " << endl;
                result -> Q.display();

                cout << "Enter Activity ID You Want To delete: ";
                cin >> id;

                activity intended;
                intended.id = id;
                result -> Q.deleting(intended);
                break;
            }

            case '0':
                break;

            default:
                cout << "Error Input!" << endl;
                sleep(2);

            }
        }
        while(choice1 != '0');


        system("pause");
        system("cls");
    }

    void searchForUser()
    {
        system("cls");
        system("color 7");

        int id;
        cout << "Enter User ID: ";
        cin >> id;

        node* result = user_t.search(id);

        if(result != nullptr)
        {
            cout << "User Exists!" << endl;
            result->Q.display();
        }
        else
        {
            cout << "User Was Not Found!" << endl;
        }

        system("pause");
        system("cls");
    }

    void displayAll()
    {
        system("cls");
        system("color 7");

        user_t.inorder();

        system("pause");
        system("cls");
    }

    void Statistics()
    {
        system("cls");
        system("color 7");

        node* result = user_t.activeUser();
        cout << "The Most Active User's ID is -> " << result -> key << "\n\n";

        user_t.counterInorder(user_t.root);

        system("pause");
        system("cls");

    }
};

int main()
{
    ActivityTracker act;

    char ch;
    do
    {
        system("cls");
        system("color 0A");

        cout << "\t\t\t------------------------------------" << endl;
        cout << "\t\t\t|--  RECENT ACTIVITY TRACKER   ----|" << endl;
        cout << "\t\t\t------------------------------------" << endl;
        cout << "\t\t\t[1] Add An Activity" << endl;
        cout << "\t\t\t[2] Remove An Activity" << endl;
        cout << "\t\t\t[3] Search For A User" << endl;
        cout << "\t\t\t[4] Display Users And Their Recent Activity" << endl;
        cout << "\t\t\t[5] Statistics" << endl;
        cout << "\t\t\t[0] Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> ch;

        switch(ch)
        {
        case '1':
            act.addActivity();
            break;

        case '2':
            act.removeActivity();
            break;

        case '3':
            act.searchForUser();
            break;

        case '4':
            act.displayAll();
            break;

        case '5':
            act.Statistics();
            break;

        case '0':
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            sleep(2);
        }
    }
    while(ch != '0');

    cout << "\t\t\t\tTHANK YOU!\n";
    return 0;
}
