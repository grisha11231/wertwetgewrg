#include <iostream>
#include <string>

using namespace std;

struct node {

	// for storing symbol
	string sym;

	// for storing probability or frequency
	float pro;
	int arr[20];
	int top;
} p[20];

typedef struct node node;

// function to find shannon code
void shannon(int l, int h, node p[])
{
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l > h) {
		if (l == h || l > h)
			return;
		p[h].arr[++(p[h].top)] = 0;
		p[l].arr[++(p[l].top)] = 1;
		return;
	}
	else {
		for (i = l; i <= h - 1; i++)
			pack1 = pack1 + p[i].pro;
		pack2 = pack2 + p[h].pro;
		diff1 = pack1 - pack2;
		if (diff1 < 0)
			diff1 = diff1 * -1;
		j = 2;
		while (j != h - l + 1) {
			k = h - j;
			pack1 = pack2 = 0;
			for (i = l; i <= k; i++)
				pack1 = pack1 + p[i].pro;
			for (i = h; i > k; i--)
				pack2 = pack2 + p[i].pro;
			diff2 = pack1 - pack2;
			if (diff2 < 0)
				diff2 = diff2 * -1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = l; i <= k; i++)
			p[i].arr[++(p[i].top)] = 1;
		for (i = k + 1; i <= h; i++)
			p[i].arr[++(p[i].top)] = 0;

		// Invoke shannon function
		shannon(l, k, p);
		shannon(k + 1, h, p);
	}
}

// Function to sort the symbols
// based on their probability or frequency
void sortByProbability(int n, node p[])
{
	int i, j;
	node temp;
	for (j = 1; j <= n - 1; j++) {
		for (i = 0; i < n - 1; i++) {
			if ((p[i].pro) > (p[i + 1].pro)) {
				temp.pro = p[i].pro;
				temp.sym = p[i].sym;

				p[i].pro = p[i + 1].pro;
				p[i].sym = p[i + 1].sym;

				p[i + 1].pro = temp.pro;
				p[i + 1].sym = temp.sym;
			}
		}
	}
}

// function to display shannon codes
void display(int n, node p[])
{
	int i, j;
	cout << "\n\n\n\tSymbol\tProbability\tCode";
	for (i = n - 1; i >= 0; i--) {
		cout << "\n\t" << p[i].sym << "\t\t" << p[i].pro << "\t";
		for (j = 0; j <= p[i].top; j++)
			cout << p[i].arr[j];
	}
}



//////////////////////////////////////////////////////





#define MAX_TREE_HT 50

struct MinHNode {
	unsigned freq;
	char item;
	struct MinHNode* left, * right;
};

struct MinH {
	unsigned size;
	unsigned capacity;
	struct MinHNode** array;
};

// Creating Huffman tree node
struct MinHNode* newNode(char item, unsigned freq) {
	struct MinHNode* temp = (struct MinHNode*)malloc(sizeof(struct MinHNode));

	temp->left = temp->right = NULL;
	temp->item = item;
	temp->freq = freq;

	return temp;
}

// Create min heap using given capacity
struct MinH* createMinH(unsigned capacity) {
	struct MinH* minHeap = (struct MinH*)malloc(sizeof(struct MinH));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHNode**)malloc(minHeap->capacity * sizeof(struct MinHNode*));
	return minHeap;
}

// Print the array
void printArray(int arr[], int n) {
	int i;
	for (i = 0; i < n; ++i)
		cout << arr[i];

	cout << "\n";
}

// Swap function
void swapMinHNode(struct MinHNode** a, struct MinHNode** b) {
	struct MinHNode* t = *a;
	*a = *b;
	*b = t;
}

// Heapify
void minHeapify(struct MinH* minHeap, int idx) {
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHNode(&minHeap->array[smallest],
			&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// Check if size if 1
int checkSizeOne(struct MinH* minHeap) {
	return (minHeap->size == 1);
}

// Extract the min
struct MinHNode* extractMin(struct MinH* minHeap) {
	struct MinHNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// Insertion
void insertMinHeap(struct MinH* minHeap, struct MinHNode* minHeapNode) {
	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

// BUild min heap
void buildMinHeap(struct MinH* minHeap) {
	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

int isLeaf(struct MinHNode* root) {
	return !(root->left) && !(root->right);
}

struct MinH* createAndBuildMinHeap(char item[], int freq[], int size) {
	struct MinH* minHeap = createMinH(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(item[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

struct MinHNode* buildHfTree(char item[], int freq[], int size) {
	struct MinHNode* left, * right, * top;
	struct MinH* minHeap = createAndBuildMinHeap(item, freq, size);

	while (!checkSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}
void printHCodes(struct MinHNode* root, int arr[], int top) {
	if (root->left) {
		arr[top] = 0;
		printHCodes(root->left, arr, top + 1);
	}

	if (root->right) {
		arr[top] = 1;
		printHCodes(root->right, arr, top + 1);
	}
	if (isLeaf(root)) {
		cout << root->item << "  | ";
		printArray(arr, top);
	}
}

// Wrapper function
void HuffmanCodes(char item[], int freq[], int size) {
	struct MinHNode* root = buildHfTree(item, freq, size);

	int arr[MAX_TREE_HT], top = 0;

	printHCodes(root, arr, top);
}

int main() {

	cout << "\t\t\t\t######Shannon###### \n\n" << endl;
	
	int n, i, j;
	float total = 0;
	string ch;
	node temp;
	
	// Input number of symbols
	cout << "Enter number of symbols\t: ";
	n = 5;
	cout << n << endl;
	
	// Input symbols
	for (i = 0; i < n; i++) {
		cout << "Enter symbol " << i + 1 << " : ";
		ch = (char)(65 + i);
		cout << ch << endl;
	
		// Insert the symbol to node
		p[i].sym += ch;
	}
	
	// Input probability of symbols
	float x[] = { 0.22, 0.28, 0.15, 0.30, 0.05 };
	for (i = 0; i < n; i++) {
		cout << "\nEnter probability of " << p[i].sym << " : ";
		cout << x[i] << endl;
	
		// Insert the value to node
		p[i].pro = x[i];
		total = total + p[i].pro;
	
		// checking max probability
		if (total > 1) {
			cout << "Invalid. Enter new values";
			total = total - p[i].pro;
			i--;
		}
	}
	
	p[i].pro = 1 - total;
	
	// Sorting the symbols based on
	// their probability or frequency
	sortByProbability(n, p);
	
	for (i = 0; i < n; i++)
		p[i].top = -1;
	
	// Find the shannon code
	shannon(0, n - 1, p);
	
	// Display the codes
	display(n, p);


	cout << endl;
	cout << "\n\n\n\t\t\t\t######Huffman###### \n\n" << endl;


	char arr[] = { 'A', 'B', 'C', 'D' };
	int freq[] = { 5, 1, 6, 3 };


	for (int i = 0; i < 4; i++) {
		cout << "frequency " << arr[i] << " = " << freq[i] << endl;
	}

	int size = sizeof(arr) / sizeof(arr[0]);

	cout << "Char | Huffman code ";
	cout << "\n----------------------\n";
	HuffmanCodes(arr, freq, size);


	return 0;
}
