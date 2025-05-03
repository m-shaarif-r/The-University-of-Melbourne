/* Program to perform 1D cellular automaton (CA) computations and to use 1D CA
   to solve the density classification problem.

  Skeleton program written by Artem Polyvyanyy, http://polyvyanyy.com/,
  September 2024, with the intention that it be modified by students
  to add functionality, as required by the assignment specification.
  All included code is (c) Copyright University of Melbourne, 2024.

  Authorship Declaration:

  (1) I certify that except for the code provided in the initial skeleton file,
  the program contained in this submission is completely my own individual
  work, except where explicitly noted by further comments that provide details
  otherwise. I understand that work that has been developed by another student,
  or by me in collaboration with other students, or by non-students as a result
  of request, solicitation, or payment, may not be submitted for assessment in
  this subject. I understand that submitting for assessment work developed by
  or in collaboration with other students or non-students constitutes Academic
  Misconduct, and may be penalized by mark deductions, or by other penalties
  determined via the University of Melbourne Academic Honesty Policy, as
  described at https://academicintegrity.unimelb.edu.au.

  (2) I also certify that I have not provided a copy of this work in either
  softcopy or hardcopy or any other form to any other student, and nor will I
  do so until after the marks are released. I understand that providing my work
  to other students, regardless of my intention or any undertakings made to me
  by that other student, is also Academic Misconduct.

  (3) I further understand that providing a copy of the assignment specification
  to any form of code authoring or assignment tutoring service, or drawing the
  attention of others to such services and code that may have been made
  available via such a service, may be regarded as Student General Misconduct
  (interfering with the teaching activities of the University and/or inciting
  others to commit Academic Misconduct). I understand that an allegation of
  Student General Misconduct may arise regardless of whether or not I personally
  make use of such solutions or sought benefit from such actions.

  Signed by: Mohammad Rehman 1615920
  Dated:     05/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* #DEFINE'S ----------------------------------------------------------------*/
#define SDELIM "==STAGE %d============================\n"   // stage delimiter
#define MDELIM "-------------------------------------\n"    // delimiter of -'s
#define THEEND "==THE END============================\n"    // end message
#define ALL_NBRHDS_IN_ORDER " 000 001 010 011 100 101 110 111\n"

#define CRTRNC '\r'     // carriage return character
#define NBRHDS 8        // number of possible neighborhoods

/* TYPE DEFINITIONS ---------------------------------------------------------*/
typedef char cells_t;            // base type to store states of cells
typedef struct state state_t;           // a cellular automaton state
typedef unsigned char rule_t[NBRHDS];   // an elementary CA update rule function

struct state {                   // a state in a CA is defined by
    cells_t*        clls;        // ... an array of cells and
    state_t*        next;        // ... a link to the next state
};

typedef struct {                 // a run of a CA consists of
    state_t*        init;        // ... the initial state and
    state_t*        curr;        // ... the current state,
} run_t;                         // implemented as a linked list of states


typedef struct {                 // an elementary CA is defined by
    unsigned char   code;        // ... a code of the update rule,
    unsigned int    size;        // ... a number of cells,
    unsigned int    time;        // ... the current time step,
    rule_t          rule;        // ... an update rule function, and
    run_t*          run;         // ... a run of state steps
} CA_t;

/* USEFUL FUNCTIONS ---------------------------------------------------------*/
int             mygetchar(void);                // getchar() that skips
                                                //    carriage returns
void            initialise_automaton(CA_t* automaton, unsigned char codenumb, 
                                     unsigned int numcells);   
int             do_stage0(CA_t* automaton);      //

run_t* insert_at_foot(run_t *run, cells_t* cells_array);

int do_stage1(CA_t* automaton, int num_steps,
              int chosen_cell_pos, int start_state);
              
int run_states(CA_t* automaton, int num_steps, int start_state_count,
               int update_rule_numb, int last_time, int chosen_cell_pos2,
               int start_state2, int* count_on, int* count_off);

int do_stage2(CA_t* automaton, int chosen_cell_pos2, int start_state2);


/* WHERE IT ALL HAPPENS -----------------------------------------------------*/
int main(int argc, char *argv[]) {

    CA_t automaton;

    // Getting the required values from the input for stage 0
    int automaton_size, rule_code, num_time_steps, chosen_cell_pos, start_state,
        chosen_cell_pos2, start_state2;
    scanf("%d", &automaton_size);
    scanf("%d", &rule_code);

    // store the initial state from ilne 3 into an array for later copying
    // into automaton.
    char init_state[automaton_size + 1]; // +1 for the null terminator
    scanf("%s", init_state); // Read the entire line of cell states

    scanf("%d", &num_time_steps);
    scanf("%d,%d", &chosen_cell_pos, &start_state);
    scanf("%d,%d", &chosen_cell_pos2, &start_state2);
    // Initialise automaton
    initialise_automaton(&automaton, rule_code, automaton_size);

    // Copy the initial state to the automaton's first state's cells array
    for (int i = 0; i < automaton_size; i++) {
        automaton.run->init->clls[i] = init_state[i];
    }

    do_stage0(&automaton);

    do_stage1(&automaton, num_time_steps, chosen_cell_pos, start_state);

    do_stage2(&automaton, chosen_cell_pos2, start_state2);

    // Free allocated memory
    free(automaton.run->init->clls);
    free(automaton.run->init);
    free(automaton.run);
    printf(THEEND);
    return EXIT_SUCCESS;
}

/* USEFUL FUNCTIONS ---------------------------------------------------------*/

// An improved version of getchar(); skips carriage return characters.
// NB: Adapted version of the mygetchar() function by Alistair Moffat
int mygetchar() {
    int c;
    while ((c=getchar())==CRTRNC);          // skip carriage return characters
    return c;
}

/*-------------------------- STAGE 0 FUNCTIONS ------------------------------*/

/* Initialise the automaton -------------------------------------------------*/
void initialise_automaton(CA_t* automaton, unsigned char codenumb, 
                          unsigned int numcells) {
    // Allocate memory for the automaton (removed from here)
    automaton->code = codenumb;
    automaton->size = numcells;
    automaton->time = 0;

    // Fill the update rule using bitwise operations
    for (int i = 0; i < NBRHDS; i++) {
        automaton->rule[i] = (codenumb >> i) & 1;
    }

    // Allocate memory for the run
    automaton->run = malloc(sizeof(run_t));
    automaton->run->init = malloc(sizeof(state_t));
    automaton->run->init->clls = malloc(numcells * sizeof(cells_t));
    automaton->run->init->next = NULL;
    
    // Initialize the current state to the first state
    automaton->run->curr = automaton->run->init;

    return;
}

int do_stage0(CA_t* automaton) {
    printf(SDELIM, 0);
    printf("SIZE: %d\n", automaton->size);
    printf("RULE: %d\n", automaton->code);
    printf(MDELIM);
    printf(ALL_NBRHDS_IN_ORDER);

    // Print the next state digits for each neighborhood
    printf(" ");
    for (int i = 0; i < NBRHDS; i++) {
        printf(" %d ", automaton->rule[i]);
        if (i != NBRHDS - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    printf(MDELIM);
    // print automaton at t = 0. CHANGE IF MAGIC NUMBER.
    printf("%4d: ", 0);
    for (int i=0; i < automaton -> size; i++) {
        printf("%c", automaton -> run -> init -> clls[i]);
    }
    printf("\n");
    return 0;
}




/*-------------------------- STAGE 1 FUNCTIONS ------------------------------*/
run_t
*insert_at_foot(run_t *run, cells_t* cells_array) {
	state_t *new;
	new = (state_t*)malloc(sizeof(*new));
	assert(run!=NULL && new!=NULL);
	new->clls = cells_array;
	new->next = NULL;
	run->curr->next = new;
	run->curr = new;
	return run;
}

int do_stage1(CA_t* automaton, int num_steps, 
              int chosen_cell_pos, int start_state) {
    printf(SDELIM, 1);

    // variables to store the number of on and off state
    int count_on = 0;
    int count_off = 0;

    // creating the automaton for the specified number of runs
    for (int state_count = 0; state_count <= num_steps; state_count++) {
        printf("%4d: ", state_count);
        if (state_count == 0) {
        // Printing initial state
            for (int i = 0; i < automaton -> size; i++) {
                printf("%c", automaton->run->curr->clls[i]);
            }
            printf("\n");

            // if the starting state given from the input is 0 (for the stage 1
            // counting stats, then need to include the corresponding cell from
            // this initial state)
            if (start_state == 0) {
                cells_t observed_state =
                                automaton->run->curr->clls[chosen_cell_pos];
                if (observed_state == '*') {
                    count_on++;
                }
                    else {
                        count_off++;
                }
            } 
            continue;
        }

        // Make a new state based on previous state, by working out what each
        // next cell should be
        cells_t* new_state = malloc(automaton -> size * sizeof(cells_t));
        cells_t current_cell, left_cell, right_cell;
        
        for (int cell_numb = 0; cell_numb < (automaton -> size); cell_numb++) {
            cells_t* last_state_cells = (automaton -> run -> curr -> clls);
            current_cell = last_state_cells[cell_numb];
            if (cell_numb == automaton->size - 1) {
                right_cell = last_state_cells[0];
            } else {
                right_cell = last_state_cells[cell_numb + 1];
            }

            if (cell_numb == 0) {
                left_cell = last_state_cells[automaton->size - 1]; 
            } else {
                left_cell = last_state_cells[cell_numb - 1];
            }

            // ---- Convert * and . to 1's and 0's for binary computation ---
            int current_cell_int;
            int left_cell_int;
            int right_cell_int;

            if (left_cell == '*') {
                left_cell_int = 1;
            }
                else {
                    left_cell_int = 0;              // its a '.'
            }
            if (right_cell == '*') {
                right_cell_int = 1;
            }
                else {
                    right_cell_int = 0;
            }
            if (current_cell == '*') {
                current_cell_int = 1;
            }
                else {
                    current_cell_int = 0;
            }
            //---------------------------------------------------------------

            // In the update rule, get the number of the neighborhood for which
            // the current cell is in. THen use this number of the neighborhood
            // to look up the next value of that cell in the update rule array

            // binary number to decimal (maxmimum possible number is 8)
            int nbrhdnumber = 4 * left_cell_int
                            + 2 * current_cell_int
                            + right_cell_int; 
            if (automaton -> rule[nbrhdnumber] == 1) {
                new_state[cell_numb] = '*';
            }
                else {
                   new_state[cell_numb] = '.'; 
            }
        }

        // need to add the newly created state to the run
        insert_at_foot(automaton -> run, new_state);

        //print each new state as well, use the actual automaton run curr value
        // to see if it works.
        for (int i = 0; i < automaton -> size; i++) {
            printf("%c", automaton->run->curr->clls[i]);
        }
        //newline at the end of each new state printed, ready for next state
        printf("\n");
        automaton -> time = state_count;

        // Now to deal with the counting on and off states for a certain
        // cell position

        if (state_count >= start_state) {
            cells_t observed_state =
                                automaton->run->curr->clls[chosen_cell_pos];
            if (observed_state == '*') {
                count_on++;
            }
                else {
                    count_off++;
            }
        }

    }
    printf(MDELIM);
    printf("#ON=%d #OFF=%d CELL#%d START@%d\n", count_on, count_off,
                                                chosen_cell_pos, start_state);


    return 0;
}



/*-------------------------- STAGE 2 FUNCTIONS ------------------------------*/
int run_states(CA_t* automaton, int num_steps, int start_state_count,
               int update_rule_numb, int last_time, int chosen_cell_pos2,
               int start_state2, int* count_on, int* count_off) {
    printf("RULE: %d; STEPS: %d.\n", update_rule_numb, num_steps);
    printf(MDELIM);
    // creating the automaton for the specified number of runs
    for (int state_count = start_state_count;
         state_count <= num_steps + last_time; state_count++) {

        printf("%4d: ", state_count);

        if (state_count == start_state_count) {
        // Printing initial state
            for (int i = 0; i < automaton -> size; i++) {
                printf("%c", automaton->run->curr->clls[i]);
            }
            printf("\n");
                if (start_state2 == 0) {
        cells_t observed_state = automaton->run->curr->clls[chosen_cell_pos2];
                if (observed_state == '*') {
                    count_on++;
                }
                    else {
                        count_off++;
                }
            } 
            continue;
        }

        // Make a new state based on previous state, by working out what each
        // next cell should be
        cells_t* new_state = malloc(automaton -> size * sizeof(cells_t));
        cells_t current_cell, left_cell, right_cell;
        
        for (int cell_numb = 0; cell_numb < (automaton -> size); cell_numb++) {
            cells_t* last_state_cells = (automaton -> run -> curr -> clls);
            current_cell = last_state_cells[cell_numb];
            if (cell_numb == automaton->size - 1) {
                right_cell = last_state_cells[0];
            } else {
                right_cell = last_state_cells[cell_numb + 1];
            }

            if (cell_numb == 0) {
                left_cell = last_state_cells[automaton->size - 1]; 
            } else {
                left_cell = last_state_cells[cell_numb - 1];
            }

            // ---- Convert * and . to 1's and 0's for binary computation ----
            int current_cell_int;
            int left_cell_int;
            int right_cell_int;

            if (left_cell == '*') {
                left_cell_int = 1;
            }
                else {
                    left_cell_int = 0;              // its a '.'
            }
            if (right_cell == '*') {
                right_cell_int = 1;
            }
                else {
                    right_cell_int = 0;
            }
            if (current_cell == '*') {
                current_cell_int = 1;
            }
                else {
                    current_cell_int = 0;
            }
            //---------------------------------------------------------------

            // In the update rule, get the number of the neighborhood for which
            // the current cell is in. THen use this number of the neighborhood
            // to look up the next value of that cell in the update rule array

            // binary number to decimal (maxmimum possible number is 8)
            int nbrhdnumber = 4 * left_cell_int
                            + 2 * current_cell_int
                            + right_cell_int; 
            if (automaton -> rule[nbrhdnumber] == 1) {
                new_state[cell_numb] = '*';
            }
                else {
                   new_state[cell_numb] = '.'; 
            }
        }

        // need to add the newly created state to the run
        insert_at_foot(automaton -> run, new_state);

        //print each new state as well, use the actual automaton run curr value
        // to see if it works.
        for (int i = 0; i < automaton -> size; i++) {
            printf("%c", automaton->run->curr->clls[i]);
        }
        //newline at the end of each new state printed, ready for next state
        printf("\n");
        automaton -> time = state_count;

        if (state_count >= start_state2) {
            cells_t observed_state =
                                automaton->run->curr->clls[chosen_cell_pos2];
            if (observed_state == '*') {
            (*count_on)++;
            }
                else {
                (*count_off)++;
            }
    }


    }
    printf(MDELIM);
    return 0;
}


int do_stage2(CA_t* automaton, int chosen_cell_pos2, int start_state2) {
    printf(SDELIM, 2);
    int count_on = 0;
    int count_off = 0;
    int k = automaton -> size;
    int num_steps_first_rule = (k-2)/2;
    int num_steps_second_rule = (k-1)/2;
    for (int i = 0; i < NBRHDS; i++) {
        automaton->rule[i] = (184 >> i) & 1;
    }
    //pointer to the starting array of stage 2 so that it can be reprinted.
    cells_t start_state2_array[automaton -> size];
    for (int i = 0; i < automaton -> size; i++) {
        start_state2_array[i] = automaton -> run -> curr -> clls[i];
    }
    
    run_states(automaton, num_steps_first_rule, automaton -> time, 184,
              (automaton -> time), chosen_cell_pos2, start_state2,
              &count_on, &count_off);
    for (int i = 0; i < NBRHDS; i++) {
        automaton->rule[i] = (232 >> i) & 1;
    }
    run_states(automaton, num_steps_second_rule, automaton -> time, 232,
              (automaton -> time), chosen_cell_pos2, start_state2,
              &count_on, &count_off);
    printf("#ON=%d #OFF=%d CELL#%d START@%d\n", count_on + 1, count_off,
                                                chosen_cell_pos2, start_state2);
    printf(MDELIM);
    printf("%4d: ", start_state2);
    for (int j=0; j < automaton -> size; j++) {
        printf("%c", start_state2_array[j]);
    }
    printf("\n");
    int number_on_final = 0;
    char comparator;
    // count number of ons in final state
    for (int k = 0; k < automaton -> size; k++) {
        if ((automaton -> run -> curr -> clls[k]) == '*') {
            number_on_final++;
        }
    }
    int half_length = (automaton -> size)/2;
    if (number_on_final < half_length) {
        comparator = '<';
    }
    else if (number_on_final == half_length) {
        comparator = '=';
    }
    else {
        comparator = '>';
    }
    printf("AT T=%d: #ON/#CELLS %c 1/2\n", start_state2, comparator);
    return 0;
}



/* THE END ------------------------------------------------------------------*/

//algorithms are fun










