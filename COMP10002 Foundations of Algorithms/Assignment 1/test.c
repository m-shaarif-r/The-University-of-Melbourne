void
do_stage3(field_t sorted_array[][MAXNUMCOLS], int argc, char* argv[], int num_rows){
   printf("Stage 3\n");
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
            if (strcmp(sorted_array[i][curr_attr],current_vals[argvpos-1])!=0){
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
            else {
               printf("%*s%s", 4 * (argvpos - 1), "", sorted_array[1][curr_attr]);
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
             
         }
         
         
         
      }

   }

}