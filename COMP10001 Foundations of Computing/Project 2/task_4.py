from task_3 import possible_study_groups
from itertools import combinations

def alloc_study_groups(zbinis):
    '''
    
    '''
    
    poss_grps = possible_study_groups(zbinis)
    # maximum number of groups is 3 (i.e. worst case is 3 groups each
    # with 3 zbinis), because max number of zbinis is 10 so only have
    # to check up to combinations of 3 groups from `possible_groups`

    #num_poss_grps = len(poss_grps)
    three_grp_combs = list(combinations(poss_grps, 3))
    two_grp_combs = list(combinations(poss_grps, 2))
    # group combinations of size 1 also count, just each group in `poss_grps`
    #print(two_grp_combs)
    # Only leave all combinatinos that don't have a zbini repeated in the
    # combination's groups.
    valid_two_grp_combs = []
    valid_three_grp_combs = []
    for comb in two_grp_combs:
        if grp_comb_valid(comb):
            valid_two_grp_combs.append(comb)
        
    for comb in three_grp_combs:
        if grp_comb_valid(comb):
            valid_two_grp_combs.append(comb)


    all_valid_combs = [[grp] for grp in poss_grps] + valid_two_grp_combs + valid_three_grp_combs
    try:
        required_valid_comb = sorted(all_valid_combs, key = decider_key)[-1]
    except IndexError:
        return []
    
    return [i[0] for i in required_valid_comb]

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
    
def decider_key(valid_comb):
    if len(valid_comb) == 3:
        zbinis_in_comb = sorted(set(valid_comb[0][0]) | set(valid_comb[1][0]) | set(valid_comb[2][0]))
        num_zbinis_in_comb = len(zbinis_in_comb)
        combined_score = valid_comb[0][1] + valid_comb[1][1] + valid_comb[2][1]
        
    if len(valid_comb) == 2:
        zbinis_in_comb = sorted(set(valid_comb[0][0]) | set(valid_comb[1][0]))
        num_zbinis_in_comb = len(zbinis_in_comb)
        combined_score = valid_comb[0][1] + valid_comb[1][1]
    else:
        zbinis_in_comb = valid_comb[0][0]
        combined_score = valid_comb[0][1]
        num_zbinis_in_comb = len(zbinis_in_comb)
    
    return (num_zbinis_in_comb, combined_score, -(zbinis_in_comb[0]), -(zbinis_in_comb[1]), -(zbinis_in_comb[2]))

    

#alloc_study_groups([(198, ['FoC']), (138, ['Calc 1']), (14, ['Calc 1']), (66, ['FoC'])])
#print(alloc_study_groups([(198, ['FoC']), (198, ['FoC']), (138, ['FoC']), (14, ['FoC'])]))