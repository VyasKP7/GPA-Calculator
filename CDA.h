/*
						Circular dynamic array
			Name: Vyas Padmanabhan					CWID: 11903258
*/
#ifndef FILE_FOO_SEEN
#define FILE_FOO_SEEN
#include <stdlib.h>
using namespace std;
template <typename T>
class CDA {  //Class for the dynamic circular array.
private:
	int s;   //size of the array.
	int c;  //capacity of the array.
	bool ordered;  //Whether sorted or not.

	T ErrorT;  //Empty elmtype. returns this for errors.

	T * circArray;  //dynamic circular array. (points to the element at 0 position - not necessarily the front.)
	int front;   // Stores index of front.

   // --------------------------------------------------------------------------------------------------------------------
	void checkOrdered() {           //Checks if the Array is sorted. For add functon. Utility for Add functions.
		if (ordered == false)
			return ;

		for (int i = 1; i < s; i++) {
			if (circArray[((front + i - 1) % c )] > circArray[(front + i) % c]) {
				ordered = false;
				break;
			}
		}
   }
	// --------------------------------------------------------------------------------------------------------------------


	void checkOrdered2() {			//Checks if the Array is sorted. For add functon. Utility for delete functions.
		if (ordered == true)
			return;
		for (int i = 1; i < s; i++)
		{
			if (circArray[((front + i - 1) % c)] > circArray[(front + i) % c])  //check if still false.
				return;
		}
			ordered = true; //if no flags remain, then it is ordered.
	}



   // --------------------------------------------------------------------------------------
	void resize() {     //function to resize the array. used to increase capacity
		T *temp = new T[c * 2];
		for (int i = 0; i < s; i++) {
			temp[i] = circArray[(front + i) % c];
		}
		delete[]circArray;
		circArray = temp;
		front = 0;
		c = c * 2;
	}
    //----------------------------------------------------------------------------------------------------------------------


	void reduceSize() {  //half the current size. Used to reduce capacity.

		T *temp = new T[c / 2];
		for (int i = 0; i < s; i++) {
			temp[i] = circArray[(front + i) % c];
		}
		delete[] circArray;
		circArray = temp;
		front = 0;

		c = c / 2;
		if (c == 0)
			c = 1;
	}

	//----------------------------------------------------------------------------------------------------------------------
	int BinaryS(int l, int r, T t) {		//utility function for binary search
		if (r >= l) {
			int mid = l + (r - l) / 2;
			if (circArray[(front + mid) % c] == t)
				return mid;
			if (circArray[(front + mid) % c] > t)
				return BinaryS(l, mid - 1, t);
			return BinaryS(mid + 1, r, t);
		}
		return -1;
	}

	//-----------------------------------------------------------------------------------------------------------------------


	void jsw_swap(T* a, T* b)		//swaps two values.
	{
		T c = *a;
		*a = *b;
		*b= c;
	}

	//---------------------------------------------------------------------------------------------------------------------------
	void jsw_insertion(T a[], int n)          //performs insertion, used in quick sort after threshold.
	{
		int i;

		for (i = 1; i < n; i++)
		{
			int j;
			T save = a[(front + i) % c];

			for (j = i; j >= 1 && a[(front+j - 1)%c] > save; j--)
			{
				a[(front+j)%c] = a[(front+j - 1)%c];
			}

			a[(front+j)%c] = save;
		}
	}

	//----------------------------------------------------------------------------------------------------------------------
	int jsw_partition(T a[], int first, int last)          //partition algorithm used in quicksort
	{
		int pivot, mid = (first + last) / 2;

		/* Largest of two */
		pivot = a[(front+first)%c] > a[(front+mid)%c] ? first : mid;

		/* Smallest of remaining */
		if (a[(front+pivot)%c] > a[(front+last)%c])
		{
			pivot = last;
		}

		jsw_swap(&a[(front+pivot)%c], &a[(front+first)%c]);
		pivot = first;

		while (first < last)
		{
			if (a[(front+first)%c] <= a[(front+last)%c])
			{
				jsw_swap(&a[(front+pivot)%c], &a[(front+first)%c]);
				pivot++;
			}

			++first;
		}

		jsw_swap(&a[(front+pivot)%c], &a[(front+last)%c]);

		return pivot;
	}
	//----------------------------------------------------------------------------------------------------------------------

	void jsw_quicksort_r(T a[], int first, int last){       //quicksort using threshold = 215.

		int Threshold = 215;
		if (last-first>Threshold)
		{
			int pivot = jsw_partition(a, first, last);

			jsw_quicksort_r(a, first, pivot - 1);
			jsw_quicksort_r(a, pivot + 1, last);
		}
	}
	//----------------------------------------------------------------------------------------------------------------------
	int partition(T arr[], int, int);			 //partition used in select.
	T kthsmallest(T arr[], int, int, int);       //used to find the element to return in select.
	//------------------------------------------------------------------------------------------------------------

public:

	CDA() {				//default constructor which is empty and has a capacity of 1.
		s = 0;
		c = 1;
		ordered = false;
		circArray = new T[c];
		front = 0;   //points to nothing since the array is empty.
	}

	CDA& operator=(const CDA &Circ) {       //copy assignment operator. performs a deep copy.

		if (&Circ == this)
			return *this;
		this->s = Circ.s;
		this->c = Circ.c;
		this->ErrorT = Circ.ErrorT;
		this->ordered = Circ.ordered;
		this->front = Circ.front;

		//deep copy.

		T *temp = new T[c];
		for (int i = 0; i < c; i++) {
			temp[i] = Circ.circArray[i];	 //copy all of it.
		}
		this->circArray = temp;
	}

	CDA(const CDA &Circ) {				//copy constructor. performs a deep copy.
		s = Circ.s;
		c = Circ.c;
		ErrorT = Circ.ErrorT;
		ordered = Circ.ordered;
		front = Circ.front;

		//deep copy.

		T *temp = new T[c];
		for (int i = 0; i < c; i++) {
			temp[i] = Circ.circArray[i];
		}
		circArray = temp;

	}
	CDA(int s1) {		 //constructor which specifies size.
		s = s1;
		c = s1;
		ordered = false;
		circArray = new T[c];
		front = 0;     //points to nothing since the array is empty.
	}

	~CDA() {      //destructor that deletes all dynamically allocated memory.
		delete[]circArray;
	}

	T& operator[](int i) {      //returns value at index "i" if within the size.
		if (i < 0 || i >= s) {
			std::cout << "Error, the specified index is out of range.\n";
			return ErrorT;  // allows you to return a useless value without an out of bounds error.
		}

		return circArray[(front+i)%c];
	}

	int Length() {			//returns size of the array.
		return s;
	}
	int Capacity() {		//returns capacity of the array.
		return c;
	}
	bool Ordered() {		//returns boolean that represents if the array is ordered.
		return ordered;
	}

	void Clear() {          //Empties the array.

		front = 0;
		s = 0;
		c = 1;
		ordered = false;
		delete[]circArray;
		circArray = new T[1];

	}
	void AddEnd(T v);          //Adds the element at the end, similar to push_back()
	void AddFront(T v);		   //Adds the element at the front, similar to push_front()
	void DelEnd();			   //Deletes the element at the end, similar to pop_back()
	void DelFront();		   //Deletes the element at the front, similar to pop_front()
	void InsertionSort();	   //Performs insertionsort on the array.
	void QuickSort();		   //Performs quicksort on the array.
	T Select(int k);		   //Returns Kth smallest using quickselect.
	void CountingSort(int);    //Performs CountingSort...only works with integer array.

	int Search(T t) {             //Searches for the element
		if (ordered == true) {		//binary search
			return BinaryS(0, s-1, t);
		}
		//Linear Search.
		for (int i = 0; i < s; i++) {
			if (circArray[(front + i) % c] == t)
				return i;
		}
		return -1;

	}


	void print() {			  //Utility function that prints the array in order.
		for (int i = 0; i < s; i++)
			std::cout << circArray[(front+i)%c] << " ";
		std:: cout << std::endl;
	}
};

template<typename T>
void CDA<T>::DelFront(){		//If not empty, will delete the element in front, Will reduce capacity and change ordered flag if necessary.

	if (s == 0) {
		std::cout << "Cannot delete from an empty array.\n";
		return;
	}

	if (s == 1) {
		ordered = false;
	}

	front = (front + 1) % c; //front is the next one in the list.
	s--;	//reduce size by 1.

	if ((float)s <= (float)c / 4.0) {   //if less than or equal to 25%, then reduce capacity to half.
		reduceSize();
	}
	checkOrdered2();

	if (s == 1)
		ordered = true;

}

template<typename T>
void CDA<T>::DelEnd(){		//If not empty, will delete the element at the end, Will reduce capacity and change ordered flag if necessary.
	if (s == 0) {
		std::cout << "Cannot delete from an empty array.\n";
		return;
	}
	if (s == 1) {
		ordered = false;
	}

	s--; //reduce size by 1.
	if ((float)s <= (float)c / 4.0) {   //if less than or equal to 25%, then reduce capacity to half.
		reduceSize();
	}
	checkOrdered2();
	if (s == 1)
		ordered = true;
}
template <typename T>
void CDA<T>::AddFront(T v) {		//adds element to the front of the array. Changes ordered flag and resizes the array if needed.
	if (s == 0) {
		ordered = true;
		circArray[s] = v;
		s++;
		front = 0;
		return;
	}
	if (s == c) {
		resize();
	}

	if (front == 0) {
		circArray[c - 1] = v;
		s++;
		front = c - 1;
	}
	else {
		circArray[front%c - 1] = v;
		s++;
		front = front % c - 1;
	}
	checkOrdered();
}

template<typename T>
void CDA<T>::AddEnd(T v){		//adds element to the end of the array. Changes ordered flag and resizes the array if needed.

	if (s == 0) {         //checks if array is currently empty, then sets ordered to true.And new element to front.
		ordered = true;
		circArray[s] = v;
		s++;
		front = 0;

		return;
	}

	if (s == c) {   //if array is full then resizes it.
		resize();
	}
	circArray[(front+s)%c] = v;
	s++;
	//Element has been added. Check if ordered is still true.
	checkOrdered();
}

template<typename T>
void CDA<T>::InsertionSort(){          //performs insertion sort on the array.

	int i,j;
	T key;
	for (i = 1; i < s; i++)
	{
		key = circArray[(front+i)%c];
		j = i - 1;
		while (j >= 0 && circArray[(front+j)%c] > key)
		{
			circArray[(front+j + 1)%c] = circArray[(front+j)%c];
			j = j - 1;
		}
		circArray[(front+j + 1)%c] = key;
	}
	ordered = true;
}

template<typename T>
void CDA<T>::QuickSort(){			 //performs quick sort on the array.
	jsw_quicksort_r(circArray, 0, s-1); //calls the private quicksort algorithm.
	jsw_insertion(circArray, s);        //insertion sort after the threshold.
	ordered = true;
}
template<typename T>
void CDA<T>::CountingSort(int m){          //Performs Counting sort on the integer array.
	int* B = new int[s];
	int f = m + 1;
	int* C = new int[m+1]; //0....m storage
	for (int i = 0; i <f; i++) //initialise to 0
		C[i] = 0;
	for (int i = 0; i < s; i++) //go through the array and count.
		C[circArray[(front + i) % c]]++;
	int* C1 = new int[m+1]; //Determines the order.
	C1[0] = 0;
	for (int i = 1; i < f; i++)  //decide order.
		C1[i] = C1[i - 1] + C[i - 1];
	for (int i = 0; i < s; i++) {
		B[C1[circArray[(front + i) % c]]] = circArray[(front + i) % c];
		C1[circArray[(front + i) % c]]++;
	}
	//B is sorted.
	delete []C1;  //dont need this anymore.
	delete []C;   //dont need this.
	delete []circArray;
	c = s;
	circArray = B;
	front = 0;
	ordered = true;
}

template<typename T>
int CDA<T>::partition(T a[], int first, int last)           //Partition used in Select().
{

	int pivot = first + rand() % (last-first+1);  //random pivot.
	/* Smallest of remaining */
	if (a[(front + pivot) % c] > a[(front + last) % c])
	{
		pivot = last;
	}

	jsw_swap(&a[(front + pivot) % c], &a[(front + first) % c]);
	pivot = first;

	while (first < last)
	{
		if (a[(front + first) % c] <= a[(front + last) % c])
		{
			jsw_swap(&a[(front + pivot) % c], &a[(front + first) % c]);
			pivot++;
		}

		++first;
	}

	jsw_swap(&a[(front + pivot) % c], &a[(front + last) % c]);

	return pivot;
}

template<typename T>
T CDA<T>::kthsmallest(T arr[], int l, int r, int k)		 //Main Algorithm used in Select().
{
	// If k is smaller than number of
	// elements in array

	if (k > 0 && k <= r - l + 1) {

		// Partition the array around last
		// element and get position of pivot
		// element in sorted array

		int index = partition(arr, l, r);

		// If position is same as k
		if (index - l == k - 1)
			return arr[(front+index)%c];

		// If position is more, recur
		// for left subarray
		if (index - l > k - 1)
			return kthsmallest(arr, l, index - 1, k);

		// Else recur for right subarray
		return kthsmallest(arr, index + 1, r, k - index + l - 1);
	}

	// If k is more than number of
	// elements in array 
	return ErrorT;
}

template<typename T>
T CDA<T>::Select(int k)			//Function that returns Kth smallest element using quickselect if array is not sorted.
{
	if (ordered == true) {//if sorted
		//std::cout <<"In Ordered\n";
		return circArray[(front + k - 1) % c];
	}
	//create new array for sorting.
	T *arr= new T[c];
	for (int i = 0; i < c; i++)
		arr[i] = circArray[i];
	T ans = kthsmallest(arr, 0, s - 1, k);
	delete[]arr;
	return ans;
}

#endif /* !FILE_FOO_SEEN */
