/* Program to generate hierarchical reports from TSV structured data

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2024, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.
   All included code is (c) Copyright University of Melbourne, 2024

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Mohammad Rehman 1615920
   Dated:     08/09/2024

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CHAR_CR '\r'	     /* CR character, in PC-format text files */
#define CHAR_NL '\n'         /* newline character, ends each input line */
#define CHAR_TB '\t'         /* tab character, ends each TSV field */

#define STATUS_EOL 1         /* return value for end of line field */
#define STATUS_EOF 2         /* return value for end of file field */
#define STATUS_NML 3         /* return value if neither of previous two */

#define MAXFIELDLEN 50       /* maximum field length */
#define MAXNUMLINES 1000     /* maxmimum number of lines */
#define MAXNUMCOLS 30        /* maximum number of columns*/
/* one tsv field, stored within a fixed-length character string */
typedef char field_t[MAXFIELDLEN+1];


/**************************************************************/
// PROTOTYPES

int  mygetchar(void);
int  getfield(field_t dest);
int do_stage1(field_t A[][MAXNUMCOLS], int* total_num_cols);
void print_table(field_t A[][MAXNUMCOLS], int nrows);
void do_stage2(field_t A[][MAXNUMCOLS], int argc, char* argv[],
               int line_n, int total_num_cols);
void do_stage3(field_t sorted_array[][MAXNUMCOLS], int argc,
               char* argv[], int num_rows);
void row_swap(field_t A[][MAXNUMCOLS], int row_num1, int row_num2);
void row_print(field_t A[][MAXNUMCOLS], int row_numb, int num_cols);
void insertion_sort(field_t A[][MAXNUMCOLS], int tot_num_rows,
                     int argc, char* argv[]);


/**************************************************************/

/* main program provides traffic control
*/
int
main(int argc, char* argv[]) {
   field_t table_array[MAXNUMLINES][MAXNUMCOLS];
   int tot_columns;
   // fill in table and assign return value to total number of lines (include
   // header row)
   int tot_lines = do_stage1(table_array, &tot_columns);
   //total_columns updated via a pointer in stage_1 program

   //TO CHECK: print_table(table_array, n); 

   //check if command line args have been input, and commence this if so.
   if (argc > 1) {
      do_stage2(table_array, argc, argv, tot_lines, tot_columns);
      //print_table(table_array, 34);
      printf("\n");
      do_stage3(table_array, argc, argv, tot_lines);
   }


	/* all done, time to go home */
	
	return 0;
}

/**************************************************************/

/* read characters and build a string, stopping when a tab or newline
   as encountered, with the return value indicating what that
   terminating character was
*/
int
getfield(field_t dest) {

	int ch, nchs=0;
	int status=STATUS_NML;

	dest[0] = '\0';
	while ((ch=mygetchar())
		&& (ch != CHAR_TB) && (ch != CHAR_NL) && (ch != EOF)) {

		if (nchs < MAXFIELDLEN) {
			/* ok to save this character */
			dest[nchs++] = ch;
			dest[nchs] = '\0';
		} else {
			/* silently discard extra characters if present */
		}
	}

	/* return status is defined by what character stopped the loop */
	if (ch == EOF) {
		status = STATUS_EOF;
	} else if (ch == CHAR_NL) {
		status = STATUS_EOL;
	} else if (ch == CHAR_TB) {
		status = STATUS_NML;
	}
	return status;
}

/**************************************************************/

/* read a single character, bypassing any CR characters encountered,
   so as to work correctly with either PC-type or Unix-type input
 */
int
mygetchar(void) {
	int c;
	while ((c=getchar()) == CHAR_CR) {
		/* empty loop body */
	}
	return c;
}



/**************************************************************/

/**************************************************************/
/* Completes stage 1 by taking in a pointer to the array table_array,
   and inserting field values for its entries (rows). Returns the number of
   rows (entries) read into array.
 */
int
do_stage1(field_t A[][MAXNUMCOLS], int* total_num_cols) {

   int line_n = 0, col_n = 0, tot_col_n = 0;
   int current_state;
   /*assigns the next word to the next field, checking if new line has begun,
   hence adding in fields from next line.
   
   */ 
   
   while ((current_state = getfield(A[line_n][col_n])) != STATUS_EOF) {
      if (current_state == STATUS_EOL) {
         line_n += 1;
         col_n = 0;
      }
      else {
         col_n += 1;
         if (col_n > tot_col_n) {
            tot_col_n = col_n;
         }
      }
      
      }
   /* To take care of the offset of 1 in total num of cols*/
   tot_col_n += 1;
   *total_num_cols = tot_col_n;
   printf("Stage 1\n");
   printf("input tsv data has %d rows and %d columns\n",
           line_n - 1, tot_col_n);

   /*print last row*/
   printf("row %d is:\n", line_n - 1);
   for (int i = 1; i <= tot_col_n; i++) {
      printf("%4d: %-10s %s\n", i, A[0][i-1], A[line_n - 1][i-1]);
   }
   printf("\n");
   return line_n;
   }
   

/**************************************************************/

/**************************************************************/
/* FUNCTION SPECS
 */
void
print_table(field_t A[][MAXNUMCOLS], int nrows) {
	int i, j;
	for (i=0; i<nrows; i++) {
		for (j=0; j<MAXNUMCOLS; j++) {
			printf("%4s ", A[i][j]);
		}
		printf("\n");
	}
}
/**************************************************************/

/**************************************************************/
/* FUNCTION SPECS
 */
void
do_stage2(field_t A[][MAXNUMCOLS], int argc, char* argv[], int line_numb,
            int total_num_cols) {
   // line numb is number of lines

   //loop sorting over every c.l.arg
   printf("Stage 2\n");
   for (int i = 1; i < argc; i++) {
      if (i == 1) {
         printf("sorting by \"%s\"", A[0][atoi(argv[1])-1]);
         if (argc > 2) {
            printf(",");
         }
         printf("\n");
      }
         else {
            printf("%*sthen by \"%s\"\n", 3*(i-1), "", A[0][atoi(argv[i])-1]);
            if (i + 1 < argc) {
               printf(",\n");
            }
      }

   }
   insertion_sort(A, line_numb, argc, argv);
   int values[3];
   values[0] = 1;
   values[1] = (int)ceil((double)(line_numb-1) / 2);
   //printf("values[1] is %d\n", values[1]);
   //printf("line_numb is %d\n", line_numb);
   //MUST CHECK THIS LINENUMB VARIABLE FOR WHAT IT REALLY IS AND USE CEIL PROPS
   values[2] = line_numb-1;
   for (int j = 0 ; j < 3; j++) {
      row_print(A, values[j], total_num_cols);
   }
}
/**************************************************************/


/**************************************************************/
void
insertion_sort(field_t A[][MAXNUMCOLS], int tot_num_rows,
               int argc, char* argv[]) {
   int i, j;


   for (i = 1; i < tot_num_rows; i++) {
      for (j = i - 1; j >= 1; j--) {
         int argvpos = 1;
         int col_num = atoi(argv[argvpos]) - 1;
         while (strcmp(A[j+1][col_num], A[j][col_num]) == 0
                  && argvpos < argc - 1){
            argvpos++;
            col_num = atoi(argv[argvpos]) - 1;
         }
         if (strcmp(A[j+1][col_num], A[j][col_num]) < 0){
            //printf("Comparing %s and %s\n", A[j+1][col_num], A[j][col_num]);
            row_swap(A, j, j+1);
         }
      }
   }
}
	/* and that's all there is to it! */

/**************************************************************/

/**************************************************************/
/* exchange the values of the two variables indicated 
	by the arguments */
void
row_swap(field_t A[][MAXNUMCOLS], int row_num1, int row_num2) {
    field_t tmp;
    for (int i = 0; i < MAXNUMCOLS; i++) {
        strcpy(tmp, A[row_num1][i]);
        strcpy(A[row_num1][i], A[row_num2][i]);
        strcpy(A[row_num2][i], tmp);
    }
}
/**************************************************************/

/**************************************************************/
/* FUNCTION SPECS
 */
void
row_print(field_t A[][MAXNUMCOLS], int row_numb, int num_cols) {
   printf("row %d is:\n", row_numb);
   for (int i=1; i <= num_cols; i++) {
      printf("%4d: %-10s %s\n", i, A[0][i-1], A[row_numb][i-1]);
   }
}
/**************************************************************/

/**************************************************************/
/* FUNCTION SPECS
 */
void
do_stage3(field_t sorted_array[][MAXNUMCOLS],
          int argc, char* argv[], int num_rows){
   printf("Stage 3\n");
   printf("--------------------------\n");
   for (int j = 1; j < argc; j++) {
      if (j == 1) {
         printf("%s\n", sorted_array[0][atoi(argv[j])-1]);
      }
         else if (j == argc - 1) {
            printf("%*s%-13s", 4 * (j - 1), "",
            sorted_array[0][atoi(argv[j])-1]);
            printf("Count\n");
      }
         else {
            printf("%*s%s\n", 4 * (j - 1), "",
            sorted_array[0][atoi(argv[j])-1]);
      }
   }
   printf("--------------------------\n");
   //keeps track of the field values currently being assessed.
   field_t current_vals[argc - 1];
   //for each entry
   int count = 1;
   for (int i = 1; i < num_rows; i++) {
      //printf("row number is now %d\n", i);
      for (int argvpos = 1; argvpos < argc; argvpos++) {
         int curr_attr = atoi(argv[argvpos]) - 1; //-1 because used as index.
         //add this row's field value for this column into current_vals.
         if (i != 1) {
            if (strcmp(sorted_array[i][curr_attr],
                       current_vals[argvpos-1])!=0) {
               printf("%d\n", count);
               printf("    %s", sorted_array[i][curr_attr]);
            }
         }
         strcpy(current_vals[argvpos-1], sorted_array[i][curr_attr]);
         // in the case that you are checking the first row (i == 1)
         if (i == 1) {
            //printf("argv pos is %d\n", argvpos);
            if (argvpos == 1) {
               printf("%s", current_vals[0]);
            }
            else if (argvpos == argc - 1) {
               printf("%*s%-17s", 4 * (argvpos - 1), "",
                     sorted_array[1][curr_attr]);
            }
            else {
               printf("%*s%s", 4 * (argvpos - 1), "",
                        sorted_array[1][curr_attr]);
            }
            if (argvpos != (argc - 1)){
               printf("\n");
               //don't print out a newline if its the last specified column
               // because count is required to be stated next to that one.
            }
            
         }
         int is_same_as_prev;
         if (i != 1) {
            is_same_as_prev = strcmp(current_vals[argvpos - 1],
            sorted_array[i-1][curr_attr]);
         }
         if ((is_same_as_prev == 0) && (i != 1)) {
            //printf("      same value as in previous row\n");
            if (argvpos == argc-1) {
               count += 1;
               //printf("The count is: %d\n", count);
            }
         }
         else if ((is_same_as_prev == 0) && (i = 1)) {
             //
         }
         
         
         
      }

   }
   printf("ta daa!");

}
/**************************************************************/

//algorithms are fun

/*Function Template*/
/**************************************************************/
/* FUNCTION SPECS
 */

/**************************************************************/
