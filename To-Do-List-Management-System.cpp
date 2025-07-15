#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Node
{

public:
    int id;
    string desc;
    int pri;
    time_t c_timestamp;
    time_t m_timestamp;
    bool status;
    Node *next;
    Node *prev;

    Node(string desc_, int pri_)
    {
        status = false;
        next = nullptr;
        prev = nullptr;
        desc = desc_;
        pri = pri_;
        time(&c_timestamp);
        time(&m_timestamp);
    }

    void DisplayNode()
    {
        string status_ = (status) ? "Complete" : "Uncompleted";
        cout << "Task ID: " << this->id << endl;
        cout << "Task description: " << this->desc << endl;
        cout << "Task priority: " << this->pri << endl;
        cout << "Task Status: " << status_ << endl;
        cout << "Creation timestamp: " << ctime(&c_timestamp);
        cout << "Last Modified: " << ctime(&m_timestamp);
    }

    ~Node()
    {
        next = nullptr;
        prev = nullptr;
        delete next;
        delete prev;
    }
};

class DoublyLinkedList
{

protected:
    Node *head;
    Node *tail;
    static int id;
    static int C_index;
    char type;

public:
    int count;
    int C_id;
    void AddTask(string desc, int lvl, int pos)
    {

        Node *Task = nullptr;

        if (type == 'u')
        {
            Task = new Node(desc, lvl);
            Task->id = id++;
        }
        else if (type == 'c')
        {
            Task = new Node(desc, lvl);
            Task->id = C_id;
            Task->status = true;
            time(&Task->m_timestamp);
        }

        if (head == nullptr && pos == 1)
        {
            head = Task;
            tail = Task;
            count++;
        }
        else if (head == nullptr && pos != 1)
        {
            cout << "You can only add the task at 1st position as list is empty" << endl;
            return;
        }
        else
        {
            if (pos > count + 1)
            {
                cout << "You can only add at last position " << count + 1 << " or below , returning..." << endl;
                return;
            }
            else if (pos <= 0)
            {
                cout << "Position should be greater than 0 , returning..." << endl;
                return;
            }
            int c = 0;
            bool flag = false;
            Node *curr = head;
            Node *back = nullptr;

            while (curr != nullptr && c < pos - 1)
            {

                back = curr;
                curr = curr->next;
                c++;
            }

            if (curr == head)
            {

                Task->next = head;
                head->prev = Task;
                head = Task;
                count++;
            }
            else
            {

                Task->next = curr;
                if (curr != NULL)
                {
                    curr->prev = Task;
                }
                else
                {
                    tail = Task;
                }
                back->next = Task;
                Task->prev = back;
                count++;
            }
        }
        if(type=='u')
        cout << "Task inserted successfully" << endl;
        else if(type=='c')
        cout<<"Task Marked as complete"<<endl;
    }

    void RemoveTask(int key)
    {

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *curr = head;
        Node *back = nullptr;
        bool flag = false;
        while (curr != NULL && !flag)
        {

            if (curr->id == key)
            {
                flag = true;
            }
            else
            {
                back = curr;
                curr = curr->next;
            }
        }

        if (flag)
        {

            if (curr == head)
            {   
                head = curr->next;
                if(head!=nullptr)
                head->prev = nullptr;
                if(curr!=nullptr)
                curr->next = nullptr;
                delete curr;
                count--;
            }
            else if (curr == tail)
            {
                tail = back;
                if(tail!=nullptr)
                tail->next = nullptr;
                delete curr;
                count--;
            }
            else
            {
                back->next = curr->next;
                curr->next->prev = back;
                delete curr;
                count--;
            }
            cout << "Removed Task successfully" << endl;
        }
        else
        {
            cout << "Id not found..." << endl;
        }
    }

    void ViewingTask(char n, int ip)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        if (ip == 2)
        {
            SortBypriority();
        }
        else if (ip == 3)
        {
            SortByTime();
        }

        if (type == 'u')
        {
            cout << "//////////////////Uncompleted Tasks//////////////////" << endl;
        }
        else if (type == 'c')
        {
            cout << "//////////////////Completed Tasks//////////////////" << endl;
        }
        if (n == 'A' || n == 'a')
        {
            Node *curr = head;
            while (curr != NULL)
            {

                curr->DisplayNode();
                cout << endl;
                cout << endl;
                curr = curr->next;
            }
        }
        else if (n == 'D' || n == 'd')
        {
            Node *curr = tail;
            while (curr != NULL)
            {

                curr->DisplayNode();
                cout << endl;
                cout << endl;
                curr = curr->prev;
            }
        }
    }

    int getlength()
    {
        Node *curr = head;
        int len = 0;
        while (curr != nullptr)
        {
            len++;
            curr = curr->next;
        }
        return len;
    }

    void SortBypriority()
    {
        Node *currNode = head;
        int len = getlength();
        int itr = 0;
        bool swapped;

        while (itr < len)
        {
            Node *traverseNode = head;
            Node *prevNode = head;
            swapped = false;

            while (traverseNode->next)
            {
                Node *ptr = traverseNode->next;
                if (traverseNode->pri > ptr->pri)
                {
                    swapped = true;
                    if (traverseNode == head)
                    {
                        traverseNode->next = ptr->next;
                        ptr->next = traverseNode;
                        prevNode = ptr;
                        head = prevNode;
                    }
                    else
                    {
                        traverseNode->next = ptr->next;
                        ptr->next = traverseNode;
                        prevNode->next = ptr;
                        prevNode = ptr;
                    }
                    continue;
                }
                prevNode = traverseNode;
                traverseNode = traverseNode->next;
            }
            if (!swapped)
            {
                break;
            }

            ++itr;
        }
    }

    void SortByTime()
    {
        Node *currNode = head;
        int len = getlength();
        int itr = 0;
        bool swapped;

        while (itr < len)
        {
            Node *traverseNode = head;
            Node *prevNode = head;
            swapped = false;

            while (traverseNode->next)
            {
                Node *ptr = traverseNode->next;
                if (traverseNode->m_timestamp > ptr->m_timestamp)
                {
                    swapped = true;
                    if (traverseNode == head)
                    {
                        traverseNode->next = ptr->next;
                        ptr->next = traverseNode;
                        prevNode = ptr;
                        head = prevNode;
                    }
                    else
                    {
                        traverseNode->next = ptr->next;
                        ptr->next = traverseNode;
                        prevNode->next = ptr;
                        prevNode = ptr;
                    }
                    continue;
                }
                prevNode = traverseNode;
                traverseNode = traverseNode->next;
            }
            if (!swapped)
            {
                break;
            }

            ++itr;
        }
    }

    virtual void MarkingTask(int) {}

    void EditTask(int key, string desc_, int pri_)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *curr = head;
        bool flag = false;
        while (curr != NULL && !flag)
        {

            if (curr->id == key)
            {
                flag = true;
            }
            else
            {
                curr = curr->next;
            }
        }

        if (flag)
        {
            curr->desc = desc_;
            curr->pri = pri_;
            cout << "Task edited successfully" << endl;
            time(&curr->m_timestamp);
        }
        else
        {
            cout << "Invalid ID" << endl;
        }
    }

    void ClearList()
    {
        if (head == nullptr)
        {
            cout << "List is already empty" << endl;
            return;
        }
        Node *curr = nullptr;

        while (head != NULL)
        {

            curr = head;
            head = head->next;
            delete curr;
        }
        cout << "All tasks cleared" << endl;
    }

    void MovingTasks(int key, char a)
    {

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *curr = head;
        Node *back = NULL;
        bool flag = false;

        while (curr != NULL && !flag)
        {

            if ((a == 'd' || a == 'D') && curr->id == key)
            {
                flag = true;
            }
            else if ((a == 'u' || a == 'U') && back != NULL && back->id == key)
            {
                flag = true;
            }
            else
            {
                back = curr;
                curr = curr->next;
            }
        }
        if (flag)
        {

            if (curr == head)
            {
                cout << "Task cannot be moved down , it is at first position" << endl;
                return;
            }
            else if (curr == NULL)
            {
                cout << "Task cannot be moved up , it is at last position" << endl;
                return;
            }
            else
            {
                if (back == head)
                {
                    head = curr;
                }
                if (curr == tail)
                {
                    tail = back;
                }
                Node *t1 = back->prev;
                Node *t2 = curr->next;
                if (t1 != NULL)
                    t1->next = curr;
                curr->prev = t1;
                back->next = t2;
                if (t2 != NULL)
                    t2->prev = back;
                curr->next = back;
                back->prev = curr;
                time(&curr->m_timestamp);
                cout << "Task moved successfully" << endl;
            }
        }

        else
        {
            if (back == tail)
            {
                cout << "Task cannot be moved up , it is at last position" << endl;
            }
            else
            {
                cout << "Invalid ID..." << endl;
            }
        }
    }

    void FilterTasks(int priority)
    {
        bool flag = false;
        cout << "Tasks with given priority: ";
        if (head != nullptr)
        {
            Node *curr = head;
            while (curr != nullptr)
            {
                if (curr->pri == priority)
                {
                    cout << endl;
                    curr->DisplayNode();
                    flag = true;
                }
                curr = curr->next;
            }
        }
        else
        {
            cout << "Tasks List is empty" << endl;
        }
        if (!flag)
        {
            cout << "none!" << endl;
        }
    }

    void SearchTasks(string str)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *curr = head;
        bool flag = false;
        cout << "Tasks that contains the given keyword: " << endl;
        while (curr != nullptr)
        {
            if (curr->desc.find(str) != string::npos)
            {
                cout << endl;
                curr->DisplayNode();
                flag = true;
            }
            curr = curr->next;
        }
        if (!flag)
        {
            cout << "none!" << endl;
        }
    }
};

int DoublyLinkedList::id = 1;
int DoublyLinkedList::C_index = 1;

class CompletedList : public DoublyLinkedList
{

public:
    CompletedList()
    {
        type = 'c';
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
};

class UncompletedList : public DoublyLinkedList
{

private:
    DoublyLinkedList *Clist;

public:
    UncompletedList()
    {
        Clist = nullptr;
        type = 'u';
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    UncompletedList(DoublyLinkedList *&C)
    {
        Clist = C;
        type = 'u';
        head = nullptr;
        tail = nullptr;
    }

    void MarkingTask(int key)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *curr = head;
        Node *back = NULL;
        bool flag = false;
        while (curr != NULL && !flag)
        {

            if (curr->id == key)
            {
                flag = true;
            }
            else
            {
                back = curr;
                curr = curr->next;
            }
        }
        if (flag)
        {
            curr->status = true;
            if (curr == head)
            {
                head = head->next;
                if (head != nullptr)
                    head->prev = nullptr;
                if (curr != nullptr)
                    curr->next = nullptr;
            }
            else if (curr == tail)
            {   
                tail = back;
                if(tail!=nullptr)
                tail->next = nullptr;
            }
            else
            {
                back->next = curr->next;
                curr->next->prev = back;
            }
            Clist->C_id = curr->id;
            Clist->AddTask(curr->desc, curr->pri, Clist->C_index++);
        }
        else
        {
            cout << "Invalid ID" << endl;
        }
    }
};

int main()
{
    DoublyLinkedList *CList = new CompletedList;
    DoublyLinkedList *UList = new UncompletedList(CList);

    cout << endl
         << endl;
    cout << "\t\t ///////////////////23L-0860//////////////////////" << endl;
    cout << "\t\t /////////////TASK MANAGEMENT SYSTEM//////////////"<<endl;
    cout<<"-------------------------------------------------------------------------------------------"<<endl;
    int input = 0;
    do
    {
        cout << endl
             << endl;
        cout << "Enter 1 to add a task in the list" << endl;
        cout << "Enter 2 to remove a task from the list" << endl;
        cout << "Enter 3 to edit a task in the list" << endl;
        cout << "Enter 4 to view the list" << endl;
        cout << "Enter 5 to move a task in the list" << endl;
        cout << "Enter 6 to mark the task a complete" << endl;
        cout << "Enter 7 to filter the list by priority" << endl;
        cout << "Enter 8 to search tasks by keywords" << endl;
        cout << "Enter 9 to clear the list" << endl
             << endl;
        cout << "Enter -99 to exit" << endl
             << endl;
        cout << "Your input: ";
        cin >> input;
        cin.ignore();
        cout<<endl<<endl;
        if (input == 1)
        {
            string desc;
            int pri = 0;
            int pos = 0;
            cout << "Enter the description of the task: ";
            getline(cin, desc);
            cout << "Enter task priority: ";
            cin >> pri;
            cin.ignore();
            cout << "Enter task position in the list: ";
            cin >> pos;
            cin.ignore();
            cout << endl;
            UList->AddTask(desc, pri, pos);
        }
        else if (input == 2)
        {
            int i = 0;
            cout << "Enter 1 to remove from the uncompleted list" << endl;
            cout << "Enter 2 to remove from the completed list" << endl;
            cout << "Your input: ";
            cin >> i;
            cin.ignore();
            if (i != 1 && i != 2)
            {
                cout << "invalid input";
            }
            else
            {
                int id = 0;
                cout << "Enter the id of the task: ";
                cin >> id;
                cin.ignore();
                cout << endl;
                if (i == 1)
                    UList->RemoveTask(id);
                else if (i == 2)
                    CList->RemoveTask(id);
            }
        }
        else if (input == 3)
        {
            string desc;
            int pri = 0, id = 0;
            cout << "Enter the id of the task: ";
            cin >> id;
            cin.ignore();
            cout << "Enter the new description of the task: ";
            getline(cin, desc);
            cout << "Enter its new priority: ";
            cin >> pri;
            cin.ignore();
            cout << endl;
            UList->EditTask(id, desc, pri);
        }
        else if (input == 4)
        {
            int in = 0, i = 0;
            char ch;
            cout << "Enter 1 to display the list" << endl;
            cout << "Enter 2 to sort the list by priority and display" << endl;
            cout << "Enter 3 to sort the list by time and display" << endl;
            cout << "Your choice: ";
            cin >> in;
            cin.ignore();
            if (in != 1 && in != 2 && in != 3)
            {
                cout << "invalid input";
            }
            else
            {
                cout << endl;
                cout << "Enter 'a' or 'A' to view in ascending order" << endl;
                cout << "Enter 'd' or 'D' to view in ascending order" << endl;
                cout << "Your choice: ";
                cin >> ch;
                if (ch != 'a' && ch != 'A' && ch != 'd' && ch != 'D')
                {
                    cout << "Invalid choice" << endl;
                }
                else
                {
                    cout << endl;
                    cout << "Enter 1 to view the uncompleted list" << endl;
                    cout << "Enter 2 to view the completed list" << endl;
                    cout << "Your input: ";
                    cin >> i;
                    cin.ignore();
                    if (i == 1)
                    {
                        UList->ViewingTask(ch, in);
                    }
                    else if (i == 2)
                    {
                        CList->ViewingTask(ch, in);
                    }
                    else
                    {
                        cout << "Invalid input" << endl;
                    }
                }
            }
        }
        else if (input == 5)
        {
            int id = 0;
            char ch;
            cout << "Enter id of the task you want to move: ";
            cin >> id;
            cin.ignore();
            cout << "Enter 'U or u' to move up and 'D or d' to move down in the list: ";
            cin >> ch;
            if (ch != 'u' && ch != 'U' && ch != 'd' && ch != 'D')
            {
                cout << "Invalid choice" << endl;
            }
            else
            {
                UList->MovingTasks(id, ch);
            }
        }
        else if (input == 6)
        {
            int id = 0;
            cout << "Enter id of the task you want to mark as complete: ";
            cin >> id;
            cin.ignore();

            UList->MarkingTask(id);
        }
        else if (input == 7)
        {
            int pri = 0, i = 0;
            cout << "Enter the priority: ";
            cin >> pri;
            cin.ignore();

            cout << "Enter 1 to filter the uncompleted list" << endl;
            cout << "Enter 2 to filter the completed list" << endl;
            cout << "Your input: ";
            cin >> i;
            cin.ignore();

            if (i == 1)
            {
                UList->FilterTasks(pri);
            }
            else if (i == 2)
            {
                CList->FilterTasks(pri);
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }
        else if (input == 8)
        {
            int i = 0;
            string keyword;
            cout << "Enter the keyword: ";
            getline(cin, keyword);
            cout << endl;
            cout << "Enter 1 to search the uncompleted list" << endl;
            cout << "Enter 2 to search the completed list" << endl;
            cout << "Your input: ";
            cin >> i;
            cin.ignore();
            cout << endl;
            if (i == 1)
            {
                UList->SearchTasks(keyword);
            }
            else if (i == 2)
            {
                CList->SearchTasks(keyword);
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }
        else if (input == 9)
        {
            int i = 0;
            cout << "Enter 1 to clear the uncompleted list" << endl;
            cout << "Enter 2 to clear the completed list" << endl;
            cout << "Your input: ";
            cin >> i;
            cin.ignore();
            cout << endl;
            if (i == 1)
            {
                UList->ClearList();
            }
            else if (i == 2)
            {
                CList->ClearList();
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }
        else if (input == -99)
        {
            cout << "Exiting...." << endl;
        }
        else
        {
            cout << "Invalid Input" << endl;
        }

    } while (input != -99);

    return 0;
}