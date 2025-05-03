#zbinis = [("a", 1), ("b", 2), ("c", 3), ("d", 4)]

#print([zbinis[zbini_num] for zbini_num in (2, 3)])






#        not_allsame = True
 #       not_alldiff = True
#
 #       while not_allsame and not_alldiff:
  #          for zbini in zbinis[1:]:
   #             id_num = zbini[0]
    #            if id_num != first_id:    
     #               # Then check if they are all different
      #              
       #     not_allsame = False   

#from itertools import combinations
# print(list(combinations([((0, 1, 2, 3), 5), ((0, 1, 2), 4), ((0, 1, 3), 4), ((0, 2, 3), 4), ((1, 2, 3), 4)], 2)))

def grp_comb_valid(n_grps_comb):
    '''
    Inputs: a list of combinations of tuples (groups of zbinis + pts)
    This is one of many n-grp combinations possible.

    Returns: validates the combination of groups so that there aren't any
    duplicate zbinis. If there are, it returns false (not valid group),
    otherwise, it returns True
    '''
    all_grped_zbinis = []
    for grp in n_grps_comb:
        all_grped_zbinis += list(grp[0])
    gross_num_zbinis = len(all_grped_zbinis)
    net_num_zbinis = len(set(all_grped_zbinis))
    # if gross and net numbers are not the same, then that means there were
    # duplicate zbinis, rendering the grouping invalid as a whole
    if gross_num_zbinis == net_num_zbinis:
        return True
    else:
        return False

print(grp_comb_valid((((0, 3, 4, 5), 8), ((0, 3, 5), 7))))