#include<iostream>
#include<cstdlib>
using namespace std;

#define MAX 5
#define MAX_ITEMS 10   // max items per order

class OrderDetails {
public:
    int id;
    string name;
    float price;
    string items[MAX_ITEMS];   // <-- fixed array for items
    int itemCount;             // <-- store number of items

    void input() {
        cout << "Enter Order ID:\n";
        cin >> id;

        cout << "Enter Order Name:\n";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Price:\n";
        cin >> price;

        // ---- Take multiple items ----
        cout << "How many items? (max 10)\n";
        cin >> itemCount;
        cin.ignore();

        if(itemCount > MAX_ITEMS) itemCount = MAX_ITEMS;

        for(int i = 0; i < itemCount; i++) {
            cout << "Enter item " << (i + 1) << ": ";
            getline(cin, items[i]);
        }
    }

    void display() {
        cout << "ID: " << id 
             << ", Name: " << name 
             << ", Price: $" << price << "\n";

        cout << "Items: ";
        if(itemCount == 0)
            cout << "None";
        else {
            for(int i = 0; i < itemCount; i++) {
                cout << items[i];
                if(i < itemCount - 1) cout << ", ";
            }
        }
        cout << "\n";
    }
};

class OrderQueue {
    OrderDetails priorityQueue[MAX];
    OrderDetails normalQueue[MAX];
    int frontP, rearP;
    int frontN, rearN;

public:
    OrderQueue() {
        frontP = rearP = -1;
        frontN = rearN = -1;
    }

    bool isPriority(int priority) {
        return priority >= 1 && priority <= 3;
    }

    void enqueue(OrderDetails o, int priority) {
        if (isPriority(priority)) {
            if (rearP == MAX - 1) {
                cout << "Priority Queue Overflow\n";
            } else {
                if (frontP == -1) frontP = 0;
                rearP++;
                priorityQueue[rearP] = o;
                cout << "Order " << o.id << " (" << o.name << ") enqueued to PRIORITY queue\n";
            }
        } else {
            if (rearN == MAX - 1) {
                cout << "Normal Queue Overflow\n";
            } else {
                if (frontN == -1) frontN = 0;
                rearN++;
                normalQueue[rearN] = o;
                cout << "Order " << o.id << " (" << o.name << ") enqueued to NORMAL queue\n";
            }
        }
    }

    void dequeue() {
        if (frontP != -1 && frontP <= rearP) {
            OrderDetails served = priorityQueue[frontP];
            frontP++;
            cout << "Order " << served.id << " (" << served.name << ") dequeued from PRIORITY queue\n";
            if (frontP > rearP) frontP = rearP = -1;
        }
        else if (frontN != -1 && frontN <= rearN) {
            OrderDetails served = normalQueue[frontN];
            frontN++;
            cout << "Order " << served.id << " (" << served.name << ") dequeued from NORMAL queue\n";
            if (frontN > rearN) frontN = rearN = -1;
        }
        else {
            cout << "No orders to serve\n";
        }
    }

    void display() {
        cout << "\n--- Priority Queue ---\n";
        if (frontP == -1 || frontP > rearP) {
            cout << "Queue is empty\n";
        } else {
            for (int i = frontP; i <= rearP; i++) {
                priorityQueue[i].display();
            }
        }

        cout << "--- Normal Queue ---\n";
        if (frontN == -1 || frontN > rearN) {
            cout << "No Orders Yet !!\n";
        } else {
            for (int i = frontN; i <= rearN; i++) {
                normalQueue[i].display();
            }
        }
    }
};

int main() {
    OrderQueue q;
    int choice, priority;
    OrderDetails o;

    cout << "====== Real-Time Order Queue Simulation ======\n";

    do {
        cout << "\n1. Add New Order\n2. Serve (Dequeue) Next Order\n3. View Current Status of Queue\n4. Exit\n";
        cout << "Enter your choice:\n";
        cin >> choice;

        switch (choice) {
            case 1:
                o.input();
                cout << "Enter Priority (1-3 = Urgent/Prepaid, 4+ = Normal):\n";
                cin >> priority;
                q.enqueue(o, priority);
                break;

            case 2:
                q.dequeue();
                break;

            case 3:
                q.display();
                break;

            case 4:
                exit(0);

            default:
                cout << "Invalid Choice\n";
        }
    } while (choice != 4);

    return 0;
}
