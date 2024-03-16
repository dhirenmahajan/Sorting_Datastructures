#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;


    int* fillingArr(int arr[],int n){
        srand(time(NULL));
        for(int i=0;i<n;i++){
            int num = rand()%(2*n);
            arr[i]=num;
        }
        return arr;
    }

    void bubbleSort(int arr[], int n)
    {
        int i, j;
        for (i = 0; i < n - 1; i++)
            for (j = 0; j < n - i - 1; j++)
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
    }

    void insertionSort(int arr[], int n){
        int i, key, j;
        for (i = 1; i < n; i++)
        {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    void merge(int array[], int const left, int const mid,
               int const right)
    {
        auto const subArrayOne = mid - left + 1;
        auto const subArrayTwo = right - mid;

        // Create temp arrays
        auto *leftArray = new int[subArrayOne],
             *rightArray = new int[subArrayTwo];

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (auto i = 0; i < subArrayOne; i++)
            leftArray[i] = array[left + i];
        for (auto j = 0; j < subArrayTwo; j++)
            rightArray[j] = array[mid + 1 + j];

        auto indexOfSubArrayOne
            = 0, // Initial index of first sub-array
            indexOfSubArrayTwo
            = 0; // Initial index of second sub-array
        int indexOfMergedArray
            = left; // Initial index of merged array

        // Merge the temp arrays back into array[left..right]
        while (indexOfSubArrayOne < subArrayOne
               && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne]
                <= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
        // Copy the remaining elements of
        // left[], if there are any
        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
        // Copy the remaining elements of
        // right[], if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
    void mergeSort(int array[], int const begin, int const end)
    {
        if (begin >= end)
            return; // Returns recursively

        auto mid = begin + (end - begin) / 2;
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);
        merge(array, begin, mid, end);
    }

    int partition(int arr[], int start, int end)
    {
        int pivot = arr[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] <= pivot)
                count++;
        }
        int pivotIndex = start + count;
        swap(arr[pivotIndex], arr[start]);
        int i = start, j = end;
        while (i < pivotIndex && j > pivotIndex){
            while (arr[i] <= pivot) {
                i++;
            }
            while (arr[j] > pivot) {
                j--;
            }
            if (i < pivotIndex && j > pivotIndex){
                swap(arr[i++], arr[j--]);
            }
    }
    return pivotIndex;
    }

    void quickSort(int arr[], int start, int end)
    {
        if (start >= end)
            return;
        int p = partition(arr, start, end);
        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }

    void heapify(int arr[], int N, int i)
    {
        // Initialize largest as root
        int largest = i;
        // left = 2*i + 1
        int l = 2 * i + 1;
        // right = 2*i + 2
        int r = 2 * i + 2;
        // If left child is larger than root
        if (l < N && arr[l] > arr[largest])
            largest = l;
        // If right child is larger than largest
        // so far
        if (r < N && arr[r] > arr[largest])
            largest = r;
        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);
            // Recursively heapify the affected
            // sub-tree
            heapify(arr, N, largest);
        }
    }

    // Main function to do heap sort
    void heapSort(int arr[], int N)
    {
        // Build heap (rearrange array)
        for (int i = N / 2 - 1; i >= 0; i--)
            heapify(arr, N, i);
        // One by one extract an element
        // from heap
        for (int i = N - 1; i > 0; i--) {
            // Move current root to end
            swap(arr[0], arr[i]);
            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    void countSort(int array[], int size) {
          // The size of count must be at least the (max+1) but
          // we cannot assign declare it as int count(max+1) in C++ as
          // it does not support dynamic memory allocation.
          // So, its size is provided statically.
          int output[10];
          int count[10];
          int max = array[0];

          // Find the largest element of the array
          for (int i = 1; i < size; i++) {
            if (array[i] > max)
              max = array[i];
          }

          // Initialize count array with all zeros.
          for (int i = 0; i <= max; ++i) {
            count[i] = 0;
          }

          // Store the count of each element
          for (int i = 0; i < size; i++) {
            count[array[i]]++;
          }

          // Store the cummulative count of each array
          for (int i = 1; i <= max; i++) {
            count[i] += count[i - 1];
          }

          // Find the index of each element of the original array in count array, and
          // place the elements in output array
          for (int i = size - 1; i >= 0; i--) {
            output[count[array[i]] - 1] = array[i];
            count[array[i]]--;
          }

          // Copy the sorted elements into original array
          for (int i = 0; i < size; i++) {
            array[i] = output[i];
          }
    }

    int getMax(int array[], int n) {
          int max = array[0];
          for (int i = 1; i < n; i++)
            if (array[i] > max)
              max = array[i];
          return max;
    }

// Using counting sort to sort the elements in the basis of significant places
    void countingSorttemp(int array[], int size, int place) {
      const int max = 10;
      int output[size];
      int count[max];

      for (int i = 0; i < max; ++i)
        count[i] = 0;

      // Calculate count of elements
      for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;

      // Calculate cumulative count
      for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

      // Place the elements in sorted order
      for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
      }

      for (int i = 0; i < size; i++)
        array[i] = output[i];
    }

    // Main function to implement radix sort
    void radixsort(int array[], int size) {
      // Get maximum element
      int max = getMax(array, size);

      // Apply counting sort to sort elements based on place value.
      for (int place = 1; max / place > 0; place *= 10)
        countingSorttemp(array, size, place);
    }



class Student
{
    private:
    string FirstName;
    string LastName;
    int MNum;
    Student* next;

    public:
    //constructor:
    Student()
    {
        FirstName = "";
        LastName = "";
        MNum = 0;
    }
    //overloaded constructor with parameters:
    Student(string fname,string lname, int mno)
    {
        FirstName = fname;
        LastName = lname;
        MNum = mno;
    }
    //returns the full name:
    string getName()
    {
        return FirstName+LastName;
    }
    //returns the MNumber:
    int getMNumber()
    {
        return MNum;
    }
    //returns the age:
    bool operator<(Student obj)
    {
        return (this->getMNumber()<obj.getMNumber());
    }
    bool operator>(Student obj)
    {
        return (this->getMNumber()>obj.getMNumber());
    }
    bool operator==(Student obj)
    {
        return (this->getMNumber()==obj.getMNumber());
    }
};


    //this function adds the new items from the input into the linked list:
//node is created:
struct Node
{
    Student data;
    Node* next;
};

//the linked list class contains all the important functions required to efficiently run this program:
class LinkedList
{
    private:
    Node* head;

    public:
    //constructor is used to initialize the head pointer to NULL:
    LinkedList()
    {
        head=NULL;
    }
    //this function adds the new items from the input into the linked list:
    void AddItem(Student item)
    {
        Node* newNode = new Node{};
        newNode->data = item;
        newNode->next = NULL;
        if(head==NULL)
        {
            head = newNode;
        }
        else
        {
            Node* temp=head;
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int size()
    {
        Node* temp = head;
        int x = 0;
        if(temp!=NULL)
        {
            while(temp!=NULL)
            {
                x=x+1;
                temp = temp->next;
            }
        }
        return x;
    }

    void SortandDisplay(int size){
        //Filling array with MNumber
        int arrMNum[size];
        Node *temp=head;
        int w=0;
        if(temp!=NULL){
            while(temp!=NULL){
                    arrMNum[w]=temp->data.getMNumber();
                    w++;
                    temp=temp->next;
            }
        }

        //Sorting by choice
        cout<<"\nLets starting sorting by MNumber";
        cout<<"\n\nEnter 1 to use bubble Sort algorithm \nEnter 2 to use Insertion Sort algorithm \nEnter 3 to use radix Sort algorithm\n";
        int choice;
        cin>>choice;
        if (choice==1){
            bubbleSort(arrMNum,size);
        }
        else if (choice==2){
            insertionSort(arrMNum,size);
        }
        else if (choice==3){
            radixsort(arrMNum,size);
        }
        cout<<"Successfully Sorted"<<endl<<endl;
        cout<<"Lets print the sorted list"<<endl<<endl;
        cout << endl << left << setw(20) << "MNUMBER" << setw(20) << "NAME" << endl;
        temp=head;
        for (int i=0;i<size;i++){
            temp=head;
            while(temp!=NULL){
                if(arrMNum[i]==temp->data.getMNumber()){
                    cout<<left<<setw(20)<<temp->data.getMNumber()<<setw(20)<<temp->data.getName()<<endl;
                    break;
                }
                temp=temp->next;
            }
        }
    }
};


int main()
{
        cout<<"HELLOOOO"<<endl;
        Node *head;

        int n=25000;
        int arr[n];
        int tempArray[n];
        srand(time(NULL));

        //Assigning random value
        for(int i=0;i<n;i++){
            int num = rand()%(2*n);
            arr[i]=num;
        }

        //temporary array
        tempArray[n]=arr[n];

        auto t1 = Clock::now();
        bubbleSort(arr,n);
        auto t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Bubble-Sort" << std::endl;

        tempArray[n]=arr[n];
        t1 = Clock::now();
        insertionSort(arr,n);
        t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Insertion-Sort" << std::endl;

        tempArray[n]=arr[n];
        t1 = Clock::now();
        radixsort(arr,n);
        t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Radix-sort" << std::endl;

        tempArray[n]=arr[n];
        t1 = Clock::now();
        heapSort(arr,n);
        t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Heap-sort" << std::endl;

        tempArray[n]=arr[n];
        t1 = Clock::now();
        //countSort(arr,n);
        t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Count-sort" << std::endl;

        tempArray[n]=arr[n];
        t1 = Clock::now();
        int x = sizeof(arr) / sizeof(arr[0]);
        quickSort(arr,0,x-1);
        t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Quick-sort" << std::endl;

        tempArray[n]=arr[n];
        t1 = Clock::now();
        int y = sizeof(arr) / sizeof(arr[0]);
        mergeSort(arr,0,y-1);
        t2 = Clock::now();
        cout << "Delta t2-t1: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<< " milliseconds for Merge-sort" << std::endl;


        //TASK3
        int iMNum;
        string ifname,ilname;
        LinkedList a;
        int o;
        //Adding Items to the Linked List
        cout<<"\n\nEnter the number of student data you want to add: ";
        cin>>o;

        for (int i=0;i<o;i++){
            cout<<"enter your First Name: ";
            cin>>ifname;
            cout<<"enter your Last Name: ";
            cin>>ilname;
            cout<<"enter your MNumber: M";
            cin>>iMNum;
            Student abc=Student(ifname,ilname,iMNum);
            a.AddItem(abc);

        }

        int size=a.size();
        int arrSorted[o];
        a.SortandDisplay(size);


    return 0;
}
