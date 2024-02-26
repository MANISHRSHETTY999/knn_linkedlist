#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define numFeatures 2
#define MAX_NODES 100

// Node structure 
struct Node
{
  double data[numFeatures]; // Array to store data point 
  int label; // Label for data point
  struct Node* next; // Pointer to next node
};

// Function to insert a new node at the end of the linked list
struct Node* insertNode(struct Node* head, double data[], int label)
{
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  if (newNode == NULL) 
  {
    printf("Memory allocation failed.\n");
    exit(1);
  }
  for(int i = 0; i < numFeatures; i++) 
  {
    newNode->data[i] = data[i]; 
  }
  newNode->label = label;
  newNode->next = NULL;
  if (head == NULL) 
  {
    return newNode;
  }
  struct Node* temp = head;
  while (temp->next != NULL) 
  {
    temp = temp->next;
  }
  temp->next = newNode;
  return head;
}

// Function to calculate Euclidean distance between two points
double calculateDistance(double point1[], double point2[]) 
{
  double distance = 0;
  for (int i = 0; i < numFeatures; i++) 
  {
    distance += pow((point1[i] - point2[i]), 2);
  }
  return sqrt(distance);
}

// Function to compare double values for sorting
int compare(const void* a, const void* b) 
{
  double x = *((double*)a);
  double y = *((double*)b);
  if (x < y) return -1;
  if (x > y) return 1;
  return 0;
}

// Function to find K nearest neighbors
void findKNN(struct Node* head, double queryPoint[], int K) 
{
  int count = 0;
  struct Node* curr = head;
  
  // Array for distances of nodes
  double dist[MAX_NODES];
  
  // Calculate distance of each node from query point
  while (curr != NULL) 
  {
    dist[count] = calculateDistance(queryPoint, curr->data);
    curr = curr->next;
    count++;
  }
  
  // Sort distances and pick top K nodes
  qsort(dist, count, sizeof(dist[0]), compare);
  
  // Print labels of K nearest nodes
  curr = head;
  for (int i = 0; i < K && curr != NULL; i++) 
  {
    while (curr != NULL && calculateDistance(queryPoint, curr->data) != dist[i]) 
    {
      curr = curr->next;
    }
    if (curr != NULL) 
    {
      printf("%d\n", curr->label);
      curr = head;
    }
  }
}
int main() 
{
  // Build linked list of nodes
  struct Node* head = NULL; 
  head = insertNode(head, (double[]){1.0, 2.0}, 1);
  head = insertNode(head, (double[]){1.5, 2.2}, 1);  
  head = insertNode(head, (double[]){3.2, 5.1}, 0);
  
  double query[2];
  printf("enter the query points");
  scanf("%lf%lf",&query[0],&query[1]);
  findKNN(head, query, 3);

  return 0;
}

