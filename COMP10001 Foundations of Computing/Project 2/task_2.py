from task_1 import zbini_attrs

def valid_study_group(zbinis, group):
    '''
    Args: a list of tuples `zbinis`, tuples which represent (id, [subjects]).
    Returns:
    '''

    # Check for appropriate group size and if there are duplicates, then
    # determine whether all attribute values are the same (same id), or
    # if all attribute values are different
    if (len(group) == 3 or len(group) == 4) and (len(group) == len(set(group))):
        chosen_zbinis = [zbinis[zbini_num] for zbini_num in group]
        chosen_zbinis_attrs = [zbini_attrs(zbini[0]) for zbini in chosen_zbinis]
        
        for i in range(4):
            my_list = [zbini[i] for zbini in chosen_zbinis_attrs]
            if len(set(my_list)) != 1 and len(set(my_list)) != len(chosen_zbinis):
                return (False, None)

        subjs = [set(zbini[1]) for zbini in chosen_zbinis]
        intersection_subjs = set.intersection(*subjs)
        if len(intersection_subjs) == 0:
            return (False, None)
        else:
            return (True, len(intersection_subjs))
    else:
        return (False, None)


example_zbinis = [(0, ['FoC', 'Calc 1', 'Logic']), (108, ['FoA', 'Calc 2', 'Logic']), (148, ['FoC', 'Calc 1', 'Logic']), (248, ['FoC', 'Calc 1', 'Logic']), (0, ['Calc 2', 'History', 'Politics']), (108, ['FoC', 'Calc 1', 'Logic'])]
