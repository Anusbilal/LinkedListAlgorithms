#include <iostream>
#include <stdlib.h>
using namespace std;

struct Record
{
    int rollNo;
    float CGPA;
    Record *next;
    int index;
};

void sortedInsert(Record **head)
{
    // *head ke pass head ke next ka address ha

    // Record type ka ek pointer create kia ha ptr ke name se isme sare data ayenge
    Record *ptr = (Record *)malloc(sizeof(Record));
    cout << "Enter Roll no of the Student : ";
    cin >> ptr->rollNo;
    cout << "Enter CGPA of Student : ";
    cin >> ptr->CGPA;

    // check kr rahein hain ke head ke next null ha ya nhi agr nhi ha tu ptr ka jo data aya ha wo head ma chal jayenga then  dosre data ane pr ye false hoga!
    // this if is for 1st node
    if (*head == NULL)
    {
        ptr->next = NULL;
        ptr->index = 0;
        // jo head phele null ko point kr rha tha ab wo new Record ptr ko point kr rha ha!
        *head = ptr;

        // uncomment below line to check both pointer address or u can check roll no they both are same!

        // cout << ptr << endl;
        // cout << (*head);
        return;
    }

    Record *curr = *head;
    // this if is for 1st node roll no < 2nd node and so on...basically for inserting at the begining

    // check kr rhein hain ke new record ptr ma jo roll no ha wo phele wale head ke roll no se kam ha ya nhi...sort keliye
    if (ptr->rollNo < (*head)->rollNo)
    {
        ptr->next = *head;
        ptr->index = 0;
        *head = ptr;

        // agr value kam dal rhein hain 1st node ke roll no se tu curr ka index bahr ayega!
        while (curr != NULL)
        {
            curr->index++;
            curr = curr->next;
        }
        return;
    }

    // this  is for 1st node roll no > 2nd node and so on...basically for inserting at the last
    Record *prev = *head;
    curr = prev->next;

    while (curr != NULL)
    {

        if (ptr->rollNo < curr->rollNo)
        {
            ptr->next = curr;
            ptr->index = (prev->index) + 1;
            prev->next = ptr;
            while (curr != NULL)
            {
                curr->index++;
                curr = curr->next;
            }
            return;
        }
        cout << prev->next << " " << curr->next;
        prev = prev->next;
        curr = curr->next;
    }
    if (curr == NULL)
    {

        ptr->next = NULL;
        ptr->index = (prev->index) + 1;
        // ye line humara head ke next ma address daal rha ha jo bhi new node ata ha uska
        prev->next = ptr;
    }
}

void search(Record *head)
{
    if (head == NULL)
    {
        cout << "List is Empty" << endl;
        return;
    }
    int toSearch;
    cout << "Enter Roll no you want to Search : ";
    cin >> toSearch;
    Record *curr = head;
    while (curr != NULL)
    {
        if (curr->rollNo == toSearch)
        {
            cout << "CGPA of the student is " << curr->CGPA << endl;
            return;
        }
        curr = curr->next;
    }
    if (curr == NULL)
    {
        cout << "Roll no not Found in the List" << endl;
    }
}

void print(Record *head)
{
    if (head == NULL)
    {
        cout << "List is Empty" << endl;
        return;
    }
    Record *curr = head;
    while (curr != NULL)
    {
        cout << "CGPA of Roll no " << curr->rollNo << " is " << curr->CGPA << " and the index of Node is " << curr->index << endl;
        curr = curr->next;
    }
}

void deleteElement(Record **head)
{
    if (*head == NULL)
    {
        cout << "List is Empty " << endl;
        return;
    }
    int toDelete;
    cout << "Enter Roll no of Student which you want to Delete : ";
    cin >> toDelete;
    Record *curr = *head;
    if (toDelete == curr->rollNo)
    {
        *head = (*head)->next;
        free(curr);
        curr = *head;
        while (curr != NULL)
        {
            curr->index--;
            curr = curr->next;
        }
        cout << "Deleted successfully  " << endl;
        return;
    }
    Record *prev = *head;
    curr = prev->next;
    while (curr != NULL)
    {
        if (curr->rollNo == toDelete)
        {
            prev->next = curr->next;
            free(curr);
            cout << "Deleted successfully  " << endl;
            break;
        }
        prev = prev->next;
        curr = curr->next;
    }
    if (curr == NULL)
    {
        cout << "Roll no Not found in the List " << endl;
    }
    else
    {
        prev = prev->next;
        while (prev != NULL)
        {
            prev->index--;
            prev = prev->next;
        }
    }
}

void deleteList(Record **head)
{
    if (*head == NULL)
    {
        cout << "List is empty " << endl;
        return;
    }
    Record *curr = *head;
    while (*head != NULL)
    {
        *head = (*head)->next;
        free(curr);
        curr = *head;
    }
    cout << "Whole List Deleted " << endl;
}

int count(Record *head)
{
    int count = 0;
    Record *curr = head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

int main()
{
    Record *head = NULL;
    int n;
    do
    {
        cout << "Enter 1 to Insert data " << endl
             << "Enter 2 to search data " << endl
             << "Enter 3 to print all Records" << endl
             << "Enter 4 to Delete a Record " << endl
             << "Enter 5 to Delete whole List " << endl
             << "Enter 6 to print total no of Nodes " << endl
             << "Enter 7 to Exit" << endl;
        cin >> n;
        if (n == 1)
        {

            sortedInsert(&head);
        }
        else if (n == 2)
        {
            search(head);
        }
        else if (n == 3)
        {
            print(head);
        }
        else if (n == 4)
        {
            deleteElement(&head);
        }
        else if (n == 5)
        {
            deleteList(&head);
        }
        else if (n == 6)
        {
            cout << "Total no of Nodes are " << count(head) << endl;
        }
    } while (n != 7);
}