/**
 * Google interview question
 *
 * assignment: write a function that, given a list of strings, removes duplicates
 *
 * Lorenzo Grespan
 */

// unit testing
#include "minunit.h"
int tests_run = 0;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define LEN(X) ( sizeof X / sizeof X[0])
#define MIN(X,Y) ( X < Y ? X : Y )

/**
 * removes duplicates. 
 *
 * note: 'newlist' must be already allocated to the maximum length, here will be resized
 *
 * complexity: probably N * N-1 * N-2 * ... ~ N^2
 */
size_t foo(char* strings[], size_t len, char* newlist[]) 
{

    int i, j;
    // start from the first element
    for ( i = 0 ; i < len-1 ; i++ )
    {
        // we don't want to compare the already-voided strings
        if ( strncmp(strings[i], "\0", strlen(strings[i]) ) == 0 )
            continue;
        printf("comparing %s with:\n", strings[i]);
        // check from that one until the end
        for ( j = i+1 ; j < len ; j++ )
        {
            printf("\t %s (pos %d): ", strings[j], j);
            if ( strncmp(strings[i], strings[j], MIN(LEN(strings[i]), LEN(strings[j]))) == 0 )
            {
                printf("match; setting %s to null\n", strings[j]);
                strings[j] = "\0";
            }
            else
            {
                printf("no match\n");
            }
        }
    }

    // now we have a strings array with null strings instead of dups
    size_t newlist_pos = 0;
    for ( i = 0 ; i < len ; i++ )
        // for each element
        if ( strncmp(strings[i], "\0", strlen(strings[i]) ) != 0 )
        {
            // if it is not a null string, copy it onto the new list

            // reserve size for null terminator
            size_t newstring_length = strlen(strings[i])+1;
            newlist[newlist_pos] = malloc(newstring_length);
            bzero(newlist[newlist_pos], newstring_length);
            if ( newlist[newlist_pos] == NULL )
            {
                perror("Cannot allocate substring?");
                return -1;
            }
            strncpy(newlist[newlist_pos], strings[i], newstring_length);
            newlist_pos++;
        }

    // resize it
    realloc(newlist, newlist_pos);
    if ( newlist == NULL )
    {
        perror("Cannot reallocate memory?");
        return -1;
    }
    return newlist_pos;
}

/**
 * compares the outcome of the above function with the expected result
 */
int compare(char* testcase[], char* expected[], size_t testcase_len, size_t expected_len)
{
    int i;

    printf("Received: [");
    for ( i = 0 ; i < testcase_len ; i++ )
        printf(" %s ", testcase[i]);
    printf("]\n");
    // testcase will be modified
    char** newlist;
    // allocate the new container to be at most the length of the original
    newlist = malloc(testcase_len * sizeof &newlist);
    if ( newlist == NULL )
    {
        perror("cannot allocate memory?");
        return -1;
    }
    size_t newlist_len = foo(testcase, testcase_len, newlist);
    if ( newlist_len != expected_len ) 
    {
        fprintf(stderr, "%s:%d\t list length mismatch\n", __FILE__, __LINE__);
        return -1;
    }

    size_t newlist_item_len, expected_item_len;
    // compare every item
    for (i = 0 ; i < MIN(newlist_len, expected_len) ; i++ )
    {
        newlist_item_len = strlen(newlist[i]);
        expected_item_len = strlen(expected[i]);
        
        // item length mismatch, obvious error
        if ( newlist_item_len != expected_item_len )
        {
            fprintf(stderr, "%s:%d\t item length mismatch\n", __FILE__, __LINE__);
            return -1;
        }
        /* compare up to the shortest string anyways*/
        if ( strncmp(newlist[i], expected[i], MIN(newlist_item_len, expected_item_len)) != 0 )
        {
            fprintf(stderr, "%s:%d\t pos %d: %s is not %s\n", __FILE__, __LINE__, i, newlist[i], expected[i]);
            return -1;
        }
    }
    printf("All good; outcome [");
    for ( i = 0 ; i < newlist_len ; i++ )
        printf(" %s ", newlist[i]);
    printf("]\n");
    return 0;
}

/* 
 * test cases 
 * NOTE: outcome list is not sorted, so don't expect it
 */

static char *test_many() 
{
    char* testcase[] = { "a", "b", "c", "c", "c"};
    char* expected[] = { "a", "b", "c"};
    mu_assert("Failed test_many", compare(testcase, expected, LEN(testcase), LEN(expected)) == 0 );
    return 0;
}
static char *test_empty()
{
    char* testcase[] = { "" } ;
    char* expected[] = { } ;
    mu_assert("Failed test empty", compare(testcase, expected, LEN(testcase), LEN(expected)) == 0 );
    return 0;
}
static char *test_one()
{
    char* t[] = { "a" };
    char* e[] = { "a" };
    mu_assert("Failed test one", compare(t, e, LEN(t), LEN(e)) == 0 );
    return 0;
}
static char *test_two() 
{
    char* t[] = { "a", "a" };
    char* e[] = { "a" };
    mu_assert("Failed test_two", compare(t, e, LEN(t), LEN(e)) == 0 );
    return 0;
}
static char *test_many2()
{
    char* t[] = { "a", "a", "b", "b", "b", "c", "c", "c", "d" };
    char* e[] = { "a", "b", "c", "d" };
    mu_assert("Failed test_many2", compare(t, e, LEN(t), LEN(e)) == 0 );
    return 0;
}
static char *test_unsorted()
{
    char* t[] = { "x", "1", "foo", "joe", "2", "1" };
    char* e[] = { "x", "1", "foo", "joe", "2" };
    mu_assert("Failed test_unsorted", compare(t, e, LEN(t), LEN(e)) == 0 );
    return 0;
}

static char * all_tests() 
{
    mu_run_test(test_many);
    mu_run_test(test_empty);
    mu_run_test(test_one);
    mu_run_test(test_two);
    mu_run_test(test_many2);
    mu_run_test(test_unsorted);
    return 0;
}

int main(int argc, char **argv) 
{
    char *result = all_tests();
    if (result != 0) 
    {
        printf("%s\n", result);
    }
    else 
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
