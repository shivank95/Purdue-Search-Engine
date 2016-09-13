
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"
#include "array-dictionary.h"
#include "avl-dictionary.h"
#include "bsearch-dictionary.h"
#include "hash-dictionary.h"

struct Student {
  const char * name;
  long grade;
};

Student students[] = {
  {"Rachael", 8 },
  {"Monica", 9},
  {"Phoebe", 10},
  {"Joey", 6},
  {"Ross", 8},
  {"Chandler", 7}
};

struct Vars {
  const char * varName;
  const char * value;
};

Vars vars[] = {
  {"a", "abcd"},
  {"b", "efgh"},
  {"c", "defg"}
};

void test1(Dictionary * dict)
{

  bool e;
  e = dict->addRecord("Rachael", (void*) 8);
  assert(e);
  
  e = dict->addRecord("Monica", (void*) 9);
  assert(e);
  
  e = dict->addRecord("Monica", (void *) 10);
  assert(!e);

  printf("Test1 passed\n");
}

void test2(Dictionary * dict)
{
  bool e;
  e = dict->addRecord("Rachael", (void*)8);
  assert(e);
  
  e = dict->addRecord("Monica", (void*)9);
  assert(e);
  
  e = dict->addRecord("Monica", (void*)10);
  assert(!e);

  void * gradev;
  int grade;
  gradev = dict->findRecord("Rachael");
  grade = (long)gradev;
  assert(grade==8);

  gradev = dict->findRecord("Monica");
  grade = (long)gradev;
  assert(grade==10);

  printf("Test2 passed\n");
}

void test3(Dictionary * dict)
{
  for (int i=0; i<sizeof(students)/sizeof(Student);i++) {
    bool e;
    printf("add %s %ld\n", students[i].name, students[i].grade);
    e = dict->addRecord(students[i].name, (void*) students[i].grade);
    assert(e);
  }

  int n = sizeof(students)/sizeof(Student);

  for (int i=0; i<n;i++) {
    int grade;
    void * gradev;
    gradev = dict->findRecord(students[i].name);
    grade = (long)gradev;
    printf("found %s %d\n", students[i].name, grade);
    assert(grade==students[i].grade);
  }

  int grade;
  void * gradev;
  gradev = dict->findRecord("John");
  grade = (long)gradev;

  bool e = dict->removeElement("John");
  assert(!e);

  e = dict->removeElement("Rachael");
  assert(e);

  gradev = dict->findRecord("Rachael");
  grade = (long)gradev;

  printf("Test3 passed\n");
}

void test4(Dictionary * dict)
{
  bool e;
  e = dict->addRecord("Rachael", (void*) 8);
  assert(e);
  
  e = dict->addRecord("Monica", (void*) 9);
  assert(e);
  
  e = dict->addRecord("Monica", (void*) 10);
  assert(!e);

  int n;
  const char ** keys= dict->keys(&n);

  int sum=0;
  const char * key;
  int grade;
  void * gradev;
  for (int i = 0; i < n; i++) {
	  gradev = dict->findRecord(keys[i]);
	  grade = (long)gradev;
	  sum+=grade;
  }
  printf("MY SUM: %d\n", sum);
  assert(sum==18);

  printf("Test4 passed\n");
}

void test5(Dictionary * dict)
{
  int sum = 0;
  for (int i=0; i<sizeof(students)/sizeof(Student);i++) {
    bool e;
    e = dict->addRecord(students[i].name, (void*) students[i].grade);
    assert(e);
    sum+=students[i].grade;
  }

  int n;
  const char ** keys= dict->keys(&n);

  int sum2=0;
  const char * key;
  int grade;
  void * gradev;
  for (int i = 0; i < n; i++) {
	  gradev = dict->findRecord(keys[i]);
	  grade = (long)gradev;
	  sum2+=grade;
  }

  assert(sum2==sum);
  printf("Test5 passed\n");
}

void test6(Dictionary * dict)
{
  for (int i=0; i<sizeof(vars)/sizeof(Vars);i++) {
    bool e;
    e = dict->addRecord(vars[i].varName, (void *) vars[i].value);
    assert(e);
  }

  for (int i=0; i<sizeof(vars)/sizeof(Vars);i++) {
    bool e;
    const char * value;
    void * valuev;
    valuev = dict->findRecord(vars[i].varName);
    value = (const char *)valuev;
    assert(valuev!=NULL);
    assert(!strcmp(value,vars[i].value));
  }

  const char *value;
  void * valuev;
  valuev = dict->findRecord("John");
  value = (const char *)valuev;
  assert(valuev==NULL);

  bool e = dict->removeElement("John");
  assert(!e);

  e = dict->removeElement("a");
  assert(e);

  valuev = dict->findRecord("a");
  value = (const char *)valuev;
  assert(valuev==NULL);

  printf("Test6 passed\n");

}

void
usage()
{
  // Print usage
  fprintf(stderr, "test-dic array|hash|avl|bsearch test1|test2|test3|test4|test5|test6\n");
}

int
main( int argc, char **argv)
{
  if (argc != 3) {
    usage();
    exit(1);
  }

  printf("-----------------------------------------\n");
  printf("test-dict %s %s\n", argv[1], argv[2]);
	 

  char * dictType = argv[1];
  char * testName = argv[2];

  Dictionary * dict = NULL;
  
  if (!strcmp(dictType, "array")) {
	  dict = new ArrayDictionary();
  }
  else if (!strcmp(dictType, "hash")) {
	  dict = new HashDictionary();
  }
  else if (!strcmp(dictType, "avl")) {
	  dict = new AVLDictionary();
  }
  else if (!strcmp(dictType, "bsearch")) {
	  dict = new BinarySearchDictionary();
  }
  else {
	  usage();
	  exit(1);
  }

  if ( !strcmp(testName, "test1")) {
    test1(dict);
  }
  else if ( !strcmp(testName, "test2")) {
    test2(dict);
  }
  else if ( !strcmp(testName, "test3")) {
    test3(dict);
  }
  else if ( !strcmp(testName, "test4")) {
    test4(dict);
  }
  else if ( !strcmp(testName, "test5")) {
    test5(dict);
  }
  else if ( !strcmp(testName, "test6")) {
    test6(dict);
  }
  else {
    usage();
    exit(1);
  }

  exit(0);
  
}
