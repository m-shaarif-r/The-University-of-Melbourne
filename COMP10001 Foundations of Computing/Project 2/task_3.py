from task_2 import valid_study_group
from itertools import combinations

def possible_study_groups(zbinis):
    '''
    
    '''
    index_pool = [i for i in range(len(zbinis))]
    possible_groups = []
    for group_size in [3, 4]:
        possible_groups.append(list(combinations(index_pool, group_size)))

    possible_groups = possible_groups[0] + possible_groups[1]

    final_list = []
    for group in possible_groups:
        if valid_study_group(zbinis, group)[0]:
            points = 3 * valid_study_group(zbinis, group)[1] + len(group)//2
            final_list.append((group, points))
    final_list = sorted(final_list, key = lambda x: x[1], reverse = True)
    return final_list

#print(possible_study_groups([(198, ['FoC']), (198, ['FoC']), (138, ['FoC']), (14, ['FoC'])]))