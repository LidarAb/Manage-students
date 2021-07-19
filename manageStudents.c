#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_LEN 60
#define MAX_AGE 120
#define MIN_AGE 18
#define MAX_GRADE 100
#define MIN_GRADE 0
#define ID_LEN 10
#define BASE 10
#define ARGC_NUM 2
#define ZERO 0
#define ONE 1
#define COMMAND_1 "best"
#define COMMAND_2 "bubble"
#define COMMAND_3 "quick"
#define NUM_OF_S_MSG "Enter number of students. Then enter\n"
#define NUM_ERROR "ERROR: Number of students should be an integer.\n"
#define EXIT_MSG "USAGE: the given command is invalid.\n"
#define INFO_S_MSG "Enter student info. Then enter\n"
#define ID_ERROR "ERROR: Id must have 10 digits and can not start with 0.\n"
#define GRADE_ERROR "ERROR: grade should be an integer between 0 and 100.\n"
#define AGE_ERROR "ERROR: age should be integer between 18 and 120, include.\n"
#define BEST_MSG "best student info is: %ld,%d,%d\n"

typedef struct Student {
    int age;
    int grade;
    long int id;
} Student;

int check_is_digits (const char *ptr, int n)
/// this function checks if all the chars in the given string are digits.
/// \param ptr pointer to thr string
/// \param n the length of the string
/// \return zero if all digits, and 1 if not.
{
  for (int i = ZERO; i < n; i++)
    {
      if (!(isdigit(ptr[i])))
        return ONE;
    }
  return ZERO;
}

int get_num_of_s ()
/// this function gets from the user the number of students.
/// the function checks the validity of the input and keep asking the user for
/// number until he enter valid one.
/// \return int - the number of students
{
  char cnt[MAX_LINE_LEN];
  int num;
  while (ONE)
    {
      fprintf (stdout, NUM_OF_S_MSG);
      if (fgets (cnt, MAX_LINE_LEN, stdin) == NULL)
        {
          return -ONE;
        }

      num = (int) strtol (cnt, NULL, BASE);
      // check if the number is all digits and if it is an integer.
      if ((check_is_digits (cnt, (int) strlen (cnt) - 1) != 0) || num == 0)
        {
          fprintf (stdout, NUM_ERROR);
          continue;
        }
      else // means the number is valid
        break;
    }
  return num;
}

int check_input_validity (Student *ptr_s, int i)
/// this function ask the user for student info and checks it's validity.
/// \param ptr_s pointer to the array of students
/// \param i int represents the i'th student in the array
/// \return EXIT_FAILURE if was a problem, and zero if not.
{
  while (1) // "endless" loop until er get valid input
    {
      int age, grade;
      long int id;
      char info[MAX_LINE_LEN];
      char new_info[MAX_LINE_LEN];

      fprintf (stdout, INFO_S_MSG);
      if (fgets (info, MAX_LINE_LEN, stdin) == NULL)
        {
          free (ptr_s);
          ptr_s = NULL;
          return EXIT_FAILURE;
        }

      strcpy (new_info, info);
      char split[] = ",";
      char *ptr = strtok (new_info, split);
      // check if the id is all digits and do not start with '0'.
      if ((((int) strlen (ptr)) != ID_LEN) || ptr[0] == '0'
          || (check_is_digits (ptr, (int) strlen (ptr)) != 0))
        {
          fprintf (stdout, ID_ERROR);
          continue;
        }

      ptr = strtok (NULL, split);
      // check if the grade is all digits.
      if (check_is_digits (ptr, (int) strlen (ptr)) != 0)
        {
          fprintf (stdout, GRADE_ERROR);
          continue;
        }
      // check if the grade is in the range.
      grade = (int) strtol (ptr, NULL, BASE);
      if (!(grade <= MAX_GRADE && grade >= MIN_GRADE))
        {
          fprintf (stdout, GRADE_ERROR);
          continue;
        }

      ptr = strtok (NULL, split);
      // check if the age is all digits.
      if (check_is_digits (ptr, (int) strlen (ptr) - ONE) != ZERO)
        {
          fprintf (stdout, AGE_ERROR);
          continue;
        }
      // check if the age is in the range.
      age = (int) strtol (ptr, NULL, BASE);
      if (!(age <= MAX_AGE && age >= MIN_AGE))
        {
          fprintf (stdout, AGE_ERROR);
          continue;
        }
      int n = sscanf (info, "%ld,%d,%d", &id, &grade, &age);
      if (n == EOF)
        {
          free (ptr_s);
          ptr_s = NULL;
          return EXIT_FAILURE;
        }
      ptr_s[i].id = id;
      ptr_s[i].age = age;
      ptr_s[i].grade = grade;
      break;
    }

  return ZERO;
}

Student *execute_input (Student *ptr, int n)
/// this function ask from the user the information for n students,
/// according to the number of students he chose.
/// \param ptr pointer to the array of students
/// \param n number of students
/// \return pointer to the array
{
  int i = ZERO;
  while (i < n)
    {
      if (check_input_validity (ptr, i) == EXIT_FAILURE)
        {
          return NULL; // happens when fgetf or sscanf fails.
        }
      i++;
    }
  return ptr;
}

void best_student (Student *start, Student *end)
/// this function calculate the best student from the array according to
/// the result of grade/age. the function prints the info of the best student.
/// \param start pointer to the start of the array
/// \param end pointer to the end of the array
{
  long int best_id;
  int best_grade;
  int best_age;
  float temp = -ONE; // for the first iteration
  float cur;
  while (start < end)
    {
      cur = (float) (*start).grade / (float) (*start).age;
      if (cur > temp)
        {
          temp = cur;
          best_id = (*start).id;
          best_grade = (*start).grade;
          best_age = (*start).age;
        }
      start++;
    }
  fprintf (stdout, BEST_MSG, best_id, best_grade, best_age);
}

void bubble_sort (Student *start, Student *end)
/// this function execute the bubble sort algorithm using pointers only.
/// the function sort the array of the students according to their grade and
/// prints the sorted list.
/// \param start pointer to the start of the array
/// \param end pointer to the end of the array
{

  Student *j = start;

  for (; start < end - ONE; start++)
    {
      for (int i = ZERO; i < (end - start - ONE); i++)
        {
          if ((j + i)->grade > (j + i + ONE)->grade)
            {
              Student temp = *(j + i);
              *(j + i) = *(j + i + ONE);
              *(j + i + ONE) = temp;
            }
        }
    }
  for (int i = ZERO; i < (end - j); i++)
    printf ("%ld,%d,%d\n", (j + i)->id, (j + i)->grade, (j + i)->age);

}

Student *partition (Student *start, Student *end)
/// this function sorts the array in a way that all the item that smaller
/// then the pivot will be in the left side, and all the bigger will be in the
/// right side. returns the pointer to the pivot,
/// (the separator between ths sides)
/// \param start pointer to the start of the array
/// \param end pointer to the end of the array
/// \return pointer to the pivot
{
  int pivot = (end - ONE)->age;
  Student *i = start - ONE;
  for (; start < end - ONE; start++)
    {
      if (start->age <= pivot)
        {
          i++;
          Student temp = *i;
          *i = *start;
          *start = temp;
        }
    }
  // in the end, replace the pivot to be in the middle between the smaller and
  // the bigger side.
  Student temp = *(i + ONE);
  *(i + 1) = *(end - ONE);
  *(end - 1) = temp;
  return i + 1;
}

void quick_sort (Student *start, Student *end)
/// this function execute the quick sort algorithm using pointers only.
/// the function sort the array of the students according to their age and
/// use partition function.
/// \param start pointer to the start of the array
/// \param end pointer to the end of the array
{
  if (start < end - ONE)
    {
      // sorts the array to half smaller half bigger from the pivot and returns
      // pointer to the pivot.
      Student *n = partition (start, end);

      // sort the right side (right to the pivot) and the left side
      quick_sort (start, n);
      quick_sort (n + ONE, end);
    }

}

void print_arr (Student *ptr, int num)
/// prints the sorted array.
/// \param ptr pointer to the array
/// \param num the length of the array
{
  for (int i = ZERO; i < num; i++)
    printf ("%ld,%d,%d\n", ptr[i].id, ptr[i].grade, ptr[i].age);
}

int main (int argc, char *argv[])
{
  if ((argc != ARGC_NUM) || ((strcmp (argv[1], COMMAND_1) != 0)
                             && (strcmp (argv[1], COMMAND_2) != 0)
                             && (strcmp (argv[1], COMMAND_3) != 0)))
    {
      printf (EXIT_MSG);
      return ONE;
    }

  int num = get_num_of_s ();
  if (num == -ONE) // happens if fgets fails
    return EXIT_FAILURE;
  Student *ptr_s = (Student *) malloc (num * sizeof (Student));
  if (ptr_s == NULL)
    return EXIT_FAILURE;

  if (execute_input (ptr_s, num) == NULL)
    return EXIT_FAILURE; // happens if fgets or sscanf fails

  if (strcmp (argv[1], COMMAND_1) == ZERO)
    {
      best_student (ptr_s, ptr_s + num);
    }

  else if (strcmp (argv[1], COMMAND_2) == ZERO)
    {
      bubble_sort (ptr_s, ptr_s + num);
    }

  else if (strcmp (argv[1], COMMAND_3) == ZERO)
    {
      quick_sort (ptr_s, ptr_s + num);
      print_arr (ptr_s, num);
    }

  free (ptr_s);
  ptr_s = NULL;
  return EXIT_SUCCESS;
}