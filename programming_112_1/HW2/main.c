#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define int long long

struct Node
{
  int value;
  struct Node *next;
} typedef Node;

struct NodeList
{
  char *name; // 名字長度最多10個字，且命名規則與C語言變數命名規則一樣
  struct Node *head;
  struct NodeList *next;
} typedef NodeList;

void parameterError(int n)
{
  printf("ParameterError : The command should have %d parameter\n", n);
}

void rangeError()
{
  printf("RangeError : The length must less then or equal to 10\n");
}

void rangeError2()
{
  printf("RangeError : Out of INT range (-2,147,483,648 to 2,147,483,647)\n");
}

void typeError(char *c)
{
  printf("TypeError : It should be '%s'\n", c);
}

void appendList(NodeList **head, char *name)
{
  NodeList *newList = (NodeList *)malloc(sizeof(NodeList));
  newList->name = (char *)calloc(11, sizeof(char));
  strcpy(newList->name, name);
  newList->head = NULL;
  newList->next = NULL;

  if (*head == NULL)
  {
    *head = newList;
    printf("appendList_SUCC\n");
    return;
  }

  newList->next = *head;
  *head = newList;
  printf("appendList_SUCC\n");
}

void deleteList(NodeList **head, char *name)
{
  NodeList *current = *head;
  NodeList *prev = NULL;

  if (*head == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }
  if (strcmp((*head)->name, name) == 0)
  {
    (*head) = (*head)->next;
    printf("deleteList_SUCC\n");
    return;
  }
  else
  {
    while (current != NULL && strcmp(current->name, name) != 0)
    {
      prev = current;
      current = current->next;
    }

    if (current == NULL)
    {
      printf("NameError : %s does not exist\n", name);
      return;
    }

    if (prev != NULL)
    {
      prev->next = current->next;
    }
  }

  Node *node = current->head;
  while (node != NULL)
  {
    Node *temp = node;
    node = node->next;
    free(temp);
  }

  free(current);
  printf("deleteList_SUCC\n");
}

void nameList(NodeList **head, char *name, char *newName)
{
  NodeList *current = *head;
  while (current != NULL)
  {
    if (strcmp(current->name, name) == 0)
    {
      current->name = newName;
      printf("nameList_SUCC\n");
      return;
    }
    current = current->next;
  }
  printf("NameError : %s does not exist\n", name);
}

struct Node *swap(struct Node *ptr1, struct Node *ptr2)
{
  struct Node *tmp = ptr2->next;
  ptr2->next = ptr1;
  ptr1->next = tmp;
  return ptr2;
}

/* Function to sort the list */
void bubbleSort(struct Node **head, int count)
{
  struct Node **h;
  int i, j, swapped;

  for (i = 0; i <= count; i++)
  {

    h = head;
    swapped = 0;

    for (j = 0; j < count - i - 1; j++)
    {

      struct Node *p1 = *h;
      struct Node *p2 = p1->next;

      if (p1->value > p2->value)
      {

        /* update the link after swapping */
        *h = swap(p1, p2);
        swapped = 1;
      }

      h = &(*h)->next;
    }

    /* break if the loop ended without any swap */
    if (swapped == 0)
      break;
  }
}

void sort(NodeList *head, char *name)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  int count = 0;
  Node *temp = currentList->head;
  while (temp)
  {
    count++;
    temp = temp->next;
  }

  bubbleSort(&(currentList->head), count);

  printf("sort_SUCC\n");
}

void merge(NodeList **head, char target[], char data[])
{
  NodeList *targetList = NULL, *dataList = NULL, *current = *head;

  while (current != NULL)
  {
    if (strcmp(current->name, target) == 0)
    {
      targetList = current;
    }
    if (strcmp(current->name, data) == 0)
    {
      dataList = current;
    }
    current = current->next;
  }

  if (targetList == NULL || dataList == NULL)
  {
    if (targetList == NULL)
      printf("NameError : %s does not exist\n", target);
    else
      printf("NameError : %s does not exist\n", data);
    return;
  }

  Node *currentNode = targetList->head;
  if (currentNode == NULL)
  {
    targetList->head = dataList->head;
  }
  else
  {
    while (currentNode->next != NULL)
    {
      currentNode = currentNode->next;
    }
    currentNode->next = dataList->head;
  }

  // Remove data list
  deleteList(head, data);

  printf("merge_SUCC\n");
}

void reverse(NodeList *head, char *name)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  Node *prev = NULL, *current = currentList->head, *next = NULL;
  while (current != NULL)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  currentList->head = prev;

  printf("reverse_SUCC\n");
}

void print(NodeList *head, char *name)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  Node *currentNode = currentList->head;
  while (currentNode != NULL)
  {
    printf("%d ", currentNode->value);
    currentNode = currentNode->next;
  }
  printf("\n");
}

void append(NodeList *head, char *name, int data)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = data;
  newNode->next = NULL;

  if (currentList->head == NULL)
  {
    currentList->head = newNode;
  }
  else
  {
    Node *currentNode = currentList->head;
    while (currentNode->next != NULL)
    {
      currentNode = currentNode->next;
    }
    currentNode->next = newNode;
  }
  printf("append_SUCC\n");
}

void update(NodeList *head, char *name, int target, int data)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  Node *currentNode = currentList->head;
  while (currentNode != NULL && currentNode->value != target)
  {
    currentNode = currentNode->next;
  }

  if (currentNode != NULL)
  {
    currentNode->value = data;
    printf("update_SUCC\n");
  }
  else
  {
    printf("ValueError : %d does not exist\n", target);
  }
}

void insert(NodeList *head, char *name, int target, int data)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = data;

  if (currentList->head == NULL || currentList->head->value == target)
  {
    newNode->next = currentList->head;
    currentList->head = newNode;
  }
  else
  {
    Node *currentNode = currentList->head;
    while (currentNode->next != NULL && currentNode->next->value != target)
    {
      currentNode = currentNode->next;
    }
    if (currentNode->next == NULL)
    {
      printf("ValueError : %d does not exist\n", target);
      return;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
  }
  printf("insert_SUCC\n");
}

void delete(NodeList *head, char name[], int target)
{
  NodeList *currentList = head;
  while (currentList != NULL && strcmp(currentList->name, name) != 0)
  {
    currentList = currentList->next;
  }

  if (currentList == NULL)
  {
    printf("NameError : %s does not exist\n", name);
    return;
  }

  Node *currentNode = currentList->head;
  Node *prevNode = NULL;

  while (currentNode != NULL && currentNode->value != target)
  {
    prevNode = currentNode;
    currentNode = currentNode->next;
  }

  if (currentNode == NULL)
  {
    printf("ValueError : %d does not exist\n", target);
    return;
  }

  if (prevNode == NULL)
  {
    currentList->head = currentNode->next;
  }
  else
  {
    prevNode->next = currentNode->next;
  }
  free(currentNode);
  printf("delete_SUCC\n");
}

signed main()
{
  NodeList *ListHead = NULL;
  char command[1001];
  const char delim[] = " \n\t\r";
  int instruction = 0;
  clock_t start = clock();
  while (fgets(command, 1001, stdin) != NULL)
  {
    instruction++;
    char *token = strtok(command, delim);
    // appendList name
    if (strcmp(token, "appendList") == 0)
    {
      // get the parameter and check parameter number
      char *name = strtok(NULL, delim);

      if (name == NULL)
      {
        parameterError(1);
        continue;
      }

      if (strlen(name) > 10)
      {
        rangeError();
        continue;
      }

      if (strtok(NULL, delim) != NULL)
      {
        while (name)
        {
          name = strtok(NULL, delim);
        }
        parameterError(1);
        continue;
      }

      appendList(&ListHead, name);
    }
    // deleteList name
    else if (strcmp(token, "deleteList") == 0)
    {
      // get the parameter and check parameter number
      char *name = strtok(NULL, delim);
      if (strlen(name) > 10)
      {
        rangeError();
        continue;
      }

      if (strtok(NULL, delim) != NULL)
      {
        while (name)
        {
          name = strtok(NULL, delim);
        }
        parameterError(1);
        continue;
      }

      // check parameter type and range

      deleteList(&ListHead, name);
    }
    // nameList name newName
    else if (strcmp(token, "nameList") == 0)
    {
      // get the parameter and check parameter number
      char *name;
      char *newName;
      char *extra;
      name = strtok(NULL, delim);
      newName = strtok(NULL, delim);
      extra = strtok(NULL, delim);
      if (name == NULL || newName == NULL || extra != NULL)
      {
        parameterError(2);
        continue;
      }

      if (strlen(name) > 10 || strlen(newName) > 10)
      {
        rangeError();
        continue;
      }
      // check parameter type and range

      nameList(&ListHead, name, newName);
    }
    // sort name
    else if (strcmp(token, "sort") == 0)
    {
      // get the parameter and check parameter number
      char *name;
      char *extra;
      name = strtok(NULL, delim);
      extra = strtok(NULL, delim);
      // check parameter type and range
      if (name == NULL || extra != NULL)
      {
        parameterError(1);
        continue;
        ;
      }
      if (strlen(name) > 10)
      {
        rangeError();
        continue;
      }
      sort(ListHead, name);
    }
    // merge targetName dataName
    else if (strcmp(token, "merge") == 0)
    {
      // get the parameter and check parameter number
      char *targetName;
      char *dataName;
      char *extra;
      targetName = strtok(NULL, delim);
      dataName = strtok(NULL, delim);
      extra = strtok(NULL, delim);
      // check parameter type and range
      if (targetName == NULL || dataName == NULL || extra != NULL)
      {
        parameterError(2);
        continue;
      }

      if (strlen(targetName) > 10 || strlen(dataName) > 10)
      {
        rangeError();
        continue;
      }

      merge(&ListHead, targetName, dataName);
    }
    // reverse name
    else if (strcmp(token, "reverse") == 0)
    {
      // get the parameter and check parameter number
      char *name;
      char *extra;
      name = strtok(NULL, delim);
      extra = strtok(NULL, delim);
      // check parameter type and range
      if (name == NULL || extra != NULL)
      {
        parameterError(1);
        continue;
      }
      if (strlen(name) > 10)
      {
        rangeError();
        continue;
      }
      reverse(ListHead, name);
    }
    // print name
    else if (strcmp(token, "print") == 0)
    {
      // get the parameter and check parameter number
      char *name;
      char *extra;
      name = strtok(NULL, delim);
      extra = strtok(NULL, delim);
      // check parameter type and range
      if (name == NULL || extra != NULL)
      {
        parameterError(1);
        continue;
      }
      if (strlen(name) > 10)
      {
        rangeError();
        continue;
      }
      print(ListHead, name);
    }
    // append name data
    else if (strcmp(token, "append") == 0)
    {
      // get the parameter and check parameter number
      char *name, *datastring, *extra;
      int data = 0;
      name = strtok(NULL, delim);
      datastring = strtok(NULL, delim);
      extra = strtok(NULL, delim);

      if (name == NULL || datastring == NULL || extra != NULL)
      {
        parameterError(2);
        continue;
      }

      if (strlen(name) > 10)
      {
        rangeError();
        continue;
      }

      int flag = 0, carry = 0;

      int length = strlen(datastring), index = 1;
      for (int i = length - 1; i >= 0; i--)
      {
        if (datastring[i] - '0' > 9 || datastring[i] - '0' < 0)
        {
          if (i == 0 && datastring[i] == '-')
          {
            carry = 1;
            break;
          }
          flag = 1;
          break;
        }
        data += index * (datastring[i] - '0');
        index *= 10;
      }

      if (flag)
      {
        typeError("int");
        continue;
      }
      if (strlen(datastring) > 10)
      {
        rangeError2();
        continue;
      }
      // check parameter type and range
      if (carry = 1)
        data = -data;
      append(ListHead, name, data);
    }
    // update name target data
    else if (strcmp(token, "update") == 0)
    {
      // get the parameter and check parameter number
      char *name, *datastring, *extra;
      int target = 0;
      int data = 0;

      name = strtok(NULL, delim);
      datastring = strtok(NULL, delim);

      if (name == NULL || datastring == NULL)
      {
        parameterError(3);
        continue;
      }

      int flag = 0, flag1 = 0, carry = 0;

      int length = strlen(datastring), index = 1;

      if (length > 10)
        flag1 = 1;
      for (int i = length - 1; i >= 0; i--)
      {
        if (i == 0 && datastring[i] == '-')
        {
          carry = 1;
          break;
        }
        if (datastring[i] - '0' > 9 || datastring[i] - '0' < 0)
        {
          flag = 1;
          break;
        }
        target += index * (datastring[i] - '0');
        index *= 10;
      }

      if (carry = 1)
        target = -target;

      datastring = strtok(NULL, delim);
      extra = strtok(NULL, delim);

      if (datastring == NULL || extra != NULL)
      {
        parameterError(3);
        continue;
      }

      length = strlen(datastring), index = 1;
      if (length > 10)
        flag1 = 1;
      for (int i = length - 1; i >= 0; i--)
      {
        if (datastring[i] - '0' > 9 || datastring[i] - '0' < 0)
        {
          if (i == 0 && datastring[i] == '-')
          {
            carry = 1;
            break;
          }
          flag = 1;
          break;
        }
        data += index * (datastring[i] - '0');
        index *= 10;
      }
      if (carry)
        data = -data;
      if (flag)
      {
        typeError("int");
        continue;
      }

      if (flag1)
      {
        rangeError2();
        continue;
      }
      // check parameter type and range

      update(ListHead, name, target, data);
    }
    // insert name target data
    else if (strcmp(token, "insert") == 0)
    {
      // get the parameter and check parameter number
      char *name, *datastring, *extra;
      int target = 0;
      int data = 0;

      int flag = 0, flag1 = 0;

      name = strtok(NULL, delim);
      datastring = strtok(NULL, delim);

      if (name == NULL || datastring == NULL)
      {
        parameterError(3);
        continue;
      }

      int length = strlen(datastring), index = 1, carry = 0;

      if (length > 10)
        flag1 = 1;
      for (int i = length - 1; i >= 0; i--)
      {
        if (datastring[i] - '0' > 9 || datastring[i] - '0' < 0)
        {
          if (i == 0 && datastring[i] == '-')
          {
            carry = 1;
            break;
          }
          flag = 1;
          break;
        }
        target += index * (datastring[i] - '0');
        index *= 10;
      }

      if (carry)
        target = -target;
      datastring = strtok(NULL, delim);
      extra = strtok(NULL, delim);

      if (name == NULL || extra != NULL)
      {
        parameterError(3);
        continue;
      }

      length = strlen(datastring), index = 1;

      if (length > 10)
        flag1 = 1;

      for (int i = length - 1; i >= 0; i--)
      {
        if (datastring[i] - '0' > 9 || datastring[i] - '0' < 0)
        {
          if (i == 0 && datastring[i] == '-')
          {
            carry = 1;
            break;
          }
          flag = 1;
          break;
        }
        data += index * (datastring[i] - '0');
        index *= 10;
      }

      if (carry)
        data = -data;

      if (flag)
      {
        typeError("int");
        continue;
      }

      if (flag1)
      {
        rangeError2();
        continue;
      }
      // check parameter type and range

      insert(ListHead, name, target, data);
    }
    // delete name target
    else if (strcmp(token, "delete") == 0)
    {
      // get the parameter and check parameter number
      char *name, *datastring, *extra;
      int target = 0;

      name = strtok(NULL, delim);
      datastring = strtok(NULL, delim);
      extra = strtok(NULL, delim);

      if (name == NULL || datastring == NULL || extra != NULL)
      {
        parameterError(2);
        continue;
      }
      int flag = 0, flag1 = 0, carry = 0;
      int length = strlen(datastring), index = 1;
      if (length > 10)
        flag1 = 1;
      for (int i = length - 1; i >= 0; i--)
      {
        if (datastring[i] - '0' > 9 || datastring[i] - '0' < 0)
        {
          if (i == 0 && datastring[i] == '-')
          {
            carry = 1;
            break;
          }
          flag = 1;
          break;
        }
        target += index * (datastring[i] - '0');
        index *= 10;
      }

      if (flag)
      {
        typeError("int");
        continue;
      }

      if (flag1)
      {
        rangeError2();
        continue;
      }

      if (carry)
        target = -target;
      // check parameter type and range

      delete (ListHead, name, target);
    }
    else if (strcmp(token, "instructions") == 0)
    {
      char *extra;
      extra = strtok(NULL, delim);
      if (extra != NULL)
      {
        parameterError(0);
        continue;
      }
      printf("Total %d times instructions\n", instruction);
    }
    else if (strcmp(token, "time") == 0)
    {
      char *extra;
      extra = strtok(NULL, delim);
      if (extra != NULL)
      {
        parameterError(0);
        continue;
      }
      clock_t end = clock();
      double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
      printf("Time spent: %f seconds\n", time_spent);
    }
    else if(strcmp(token, "clean") == 0)
    {
      char *extra;
      extra = strtok(NULL, delim);
      if (extra != NULL)
      {
        parameterError(0);
        continue;
      }
      system("cls");
    }
    else
    {
      printf("SyntaxError : The command does not exist\n");
    }
  }
}