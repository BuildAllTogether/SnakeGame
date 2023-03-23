#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <curses.h>

#include "snakes.h"
#include "food.h"
#include "board.h"



void runShiftLocationTwoSegments(void);
void runShiftLocationThreeSegments(void);
void runShiftLocationNotTail(void);

void test00(void) { runShiftLocationTwoSegments(); }
void test01(void) { runShiftLocationThreeSegments(); }
void test02(void) { runShiftLocationNotTail(); }



void runShiftLocationTwoSegments() {
  struct snakeNode *head = malloc(sizeof(struct snakeNode));
  struct snakeNode *tail = malloc(sizeof(struct snakeNode));
  head->x = 2;
  head->y = 2;
  tail->x = 1;
  tail->y = 2;
  head->next = tail;

  // Snake is moving right
  
  int nextX = 3;
  int nextY = 2;

  ShiftLocation(head, nextX, nextY);

  printf("\n	Input: %d Expected: %d Output: %d \n", 2, 3, head->x);
  printf("	Input: %d Expected: %d Output: %d \n", 2, 2, head->y);
  printf("	Input: %d Expected: %d Output: %d \n", 1, 1, tail->x);
  printf("	Input: %d Expected: %d Output: %d \n", 2, 2, tail->y);

  CU_ASSERT_EQUAL(head->x, nextX);
  CU_ASSERT_EQUAL(head->y, nextY);
  CU_ASSERT_EQUAL(tail->x, 2);
  CU_ASSERT_EQUAL(tail->y, 2);
  
}

void runShiftLocationThreeSegments() {
  struct snakeNode *head = malloc(sizeof(struct snakeNode));
  struct snakeNode *mid = malloc(sizeof(struct snakeNode));
  struct snakeNode *tail = malloc(sizeof(struct snakeNode));
  head->x = 5;
  head->y = 5;
  mid->x = 5;
  mid->y = 4;
  tail->x = 5;
  tail->y = 3;
  head->next = mid;
  mid->next = tail;

  // Snake is moving right
  
  int nextX = 6;
  int nextY = 5;

  ShiftLocation(head, nextX, nextY);

  printf("\n	Input: %d Expected: %d Output: %d \n", 5, 6, head->x);
  printf("	Input: %d Expected: %d Output: %d \n", 5, 5, head->y);
  printf("	Input: %d Expected: %d Output: %d \n", 5, 5, mid->x);
  printf("	Input: %d Expected: %d Output: %d \n", 4, 5, mid->y);
  printf("	Input: %d Expected: %d Output: %d \n", 5, 5, tail->x);
  printf("	Input: %d Expected: %d Output: %d \n", 3, 4, tail->y);

  CU_ASSERT_EQUAL(head->x, nextX);
  CU_ASSERT_EQUAL(head->y, nextY);
  CU_ASSERT_EQUAL(mid->x, 5);
  CU_ASSERT_EQUAL(mid->y, 5);
  CU_ASSERT_EQUAL(tail->x, 5);
  CU_ASSERT_EQUAL(tail->y, 4);
  
}

void runShiftLocationNotTail() {
  struct snakeNode *head = malloc(sizeof(struct snakeNode));
  struct snakeNode *mid = malloc(sizeof(struct snakeNode));
  struct snakeNode *tail = malloc(sizeof(struct snakeNode));
  head->x = 5;
  head->y = 5;
  mid->x = 5;
  mid->y = 4;
  tail->x = 5;
  tail->y = 4;
  head->next = mid;
  mid->next = tail;

  // Snake is moving right
  
  int nextX = 6;
  int nextY = 5;

  ShiftLocation(head, nextX, nextY);

  printf("\n	Input: %d Expected: %d Output: %d \n", 5, 6, head->x);
  printf("	Input: %d Expected: %d Output: %d \n", 5, 5, head->y);
  printf("	Input: %d Expected: %d Output: %d \n", 5, 5, mid->x);
  printf("	Input: %d Expected: %d Output: %d \n", 4, 5, mid->y);
  printf("	Input: %d Expected: %d Output: %d \n", 5, 5, tail->x);
  printf("	Input: %d Expected: %d Output: %d \n", 3, 4, tail->y);

  CU_ASSERT_EQUAL(head->x, nextX);
  CU_ASSERT_EQUAL(head->y, nextY);
  CU_ASSERT_EQUAL(mid->x, 5);
  CU_ASSERT_EQUAL(mid->y, 5);
  CU_ASSERT_EQUAL(tail->x, 5);
  CU_ASSERT_EQUAL(tail->y, 4);
  
}
  

int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry()) { return CU_get_error(); }

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if (
          (NULL == CU_add_test(pSuite, "test00", test00)) ||
	  (NULL == CU_add_test(pSuite, "test01", test01)) ||
	  (NULL == CU_add_test(pSuite, "test02", test02))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   //   CU_basic_show_failures(CU_get_failure_list());
   CU_cleanup_registry();
   return CU_get_error();
}
