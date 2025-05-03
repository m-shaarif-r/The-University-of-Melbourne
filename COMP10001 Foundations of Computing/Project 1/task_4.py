from task_3 import path_to_next

DIR_UP = "u"
DIR_DOWN = "d"
DIR_LEFT = "l"
DIR_RIGHT = "r"
net_path = []
gross_path = []

def clean_path(world):
    '''
    
    '''
    

    # Find Vacuuminator's original position----------------------
    found_x = False
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == "X":
                vac_row, vac_col = row_num, col_num
                found_x = True
                break
        if found_x:
            break
    # Initiate first search cycle and set net path and gross path to empty lists
    world_new, vac_row_new, vac_col_new, net_path, gross_path = new_search_cycle(world, vac_row, vac_col, [], [])
    # No more dirt can be found when this ends, so start backtracking
    # Will be used to check if 
    more_dirt_found = True
    while more_dirt_found:
        for move in net_path[::-1]:
            if move == DIR_UP:
                move_reverse = 'd'
            elif move == DIR_RIGHT:
                move_reverse = 'l'
            elif move == DIR_DOWN:
                move_reverse = 'u'
            else:
                move_reverse = 'r'
            # backtrack one step
            world_new[vac_row_new][vac_col_new] = 'E'
            vac_row_new_2, vac_col_new_2 = vac_new_pos([move_reverse], vac_row_new, vac_col_new)
            world_new[vac_row_new_2 - 1][vac_col_new_2] = 'X'
            gross_path.append(move_reverse)
            #remove the move from net_path that was just reversed, so that it doesn't get backtracked onto again
            net_path.remove(move)
            #This will determine the length of the path after having reversed that move
            current_net_path = net_path
            # Start a new search cycle after backtracking a step
            world_new, vac_row_new, vac_col_new, net_path, gross_path = new_search_cycle(world_new, vac_row_new_2, vac_col_new_2, net_path, gross_path)
            # Net path length changes if more dirt found, restarts backtracking on current net path
            if len(current_net_path) < len(net_path):
                break    
        # Finished backtracking and scanning and no more dirt found
        more_dirt_found = False
                
    
    print(gross_path)

# FUNCTIONS
def vac_new_pos(path, vac_row, vac_col):    
    '''
    2 possible types of paths: path to next, or total_path
    Gives final position depending on path in rows and cols
    '''
    new_vac_row = vac_row
    new_vac_col = vac_col
    for move in path:
        if move == DIR_UP:
            new_vac_row -= 1
        elif move == DIR_RIGHT:
            new_vac_col += 1
        elif move == DIR_DOWN:
            new_vac_row += 1
        else:
            new_vac_col -= 1
    
    return new_vac_row, new_vac_col

def new_search_cycle(world, vac_row_origin, vac_col_origin, net_path, gross_path):  
    '''
    Inputs: 
    Outputs: Moves Vac to where nearest dirt is, leaves original square it was on
            as empty. Ends when no more dirt can be found in the cycle.
    '''     
    vac_row_final = vac_row_origin
    vac_col_final = vac_col_origin
    vac_row_now = vac_row_origin
    vac_col_now = vac_col_origin
    world_new = world
    # Keep moving Vac and cleaning dirt as long as you keep finding it
    next_path = path_to_next(world)
    #vac_row_original = vac_row
    #vac_col_original = vac_col
    # Run the next bit of code only if a new dirt was found (i.e. there is a path to another dirt)
    while next_path != []:
        # Record path to next dirt, keeping previous moves as well
        net_path += next_path
        gross_path += next_path
        vac_row_final, vac_col_final = vac_new_pos(next_path, vac_row_now, vac_col_now)
        world_new[vac_row_now][vac_col_now] = 'E'
        world_new[vac_row_final][vac_col_final] = 'X'
        vac_row_now, vac_col_now = vac_row_final, vac_col_final
        # Look for more dirt after finding one with new world configuration
        next_path = path_to_next(world_new)
    return world_new, vac_row_final, vac_col_final, net_path, gross_path

clean_path([['E', 'D', 'D'], ['D', 'E', 'E'], ['D', 'E', 'X']])
