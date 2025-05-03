DIR_UP = "u"
DIR_DOWN = "d"
DIR_LEFT = "l"
DIR_RIGHT = "r"

def path_to_next(world):
    '''
    DOCSTRING
    '''

    moves_list = []
    # find Vacuuminator's original position
    found_x = False
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == "X":
                vac_row, vac_col = row_num, col_num
                found_x = True
                break
        if found_x:
            break
    
    seq_dirt_up = check_up(world, vac_row, vac_col)
    seq_dirt_right = check_right(world, vac_row, vac_col)
    seq_dirt_down = check_down(world, vac_row, vac_col)
    seq_dirt_left = check_left(world, vac_row, vac_col)
    if vac_row == 0:
        seq_dirt_up = []
    if vac_row == len(world):
        seq_dirt_down = []
    if vac_col == 0:
        seq_dirt_left = []
    if vac_col == len(world[0]):
        seq_dirt_right = []
    possible_sequences = [seq_dirt_left, seq_dirt_down, seq_dirt_right, seq_dirt_up]
    non_zero_len_seqs = []
    for seq in possible_sequences:
        if len(seq) != 0:
            non_zero_len_seqs.append(seq)

    if len(non_zero_len_seqs) == 0:
        shortest_seq = []
    else:
        shortest_seq = non_zero_len_seqs[0]
        for seq in non_zero_len_seqs:
            if len(seq) <= len(shortest_seq):
                shortest_seq = seq


    return shortest_seq
    
# NEW FUNCTION: Checking with UP sensor within the same column as Vacuuminator
def check_up(world, vac_row, vac_col):
    '''
    Inputs: The world grid and the position of the vacuum in terms of rows and columns
    Returns: returns a list indicating grids moved up towards dirt if fuond FINSIFDISJFHDDSJFDSF
    '''
    rows_gone_up = 1
    # Start checking up the Vac's column starting from one above the Vac
    # Keep increasing number of rows gone up for every iteration
    for row in world[vac_row - 1::-1]:
        if row[vac_col] == "D":
            return ['u'] * rows_gone_up
        elif row[vac_col] == "W":
            return []
        else:
            rows_gone_up += 1
    # If no dirt or wall encountered:
    return []


# NEW FUNCTION: Checking with RIGHT sensor within the same row as Vacuuminator
def check_right(world, vac_row, vac_col):
    '''
    '''
    cols_gone_right = 1
    for grid_square in world[vac_row][vac_col + 1:]:
        if grid_square == "D":
            return ['r'] * cols_gone_right
        elif grid_square == "W":
            return []
        else:
            cols_gone_right += 1
    #If no dirt or wall encountered:
    return []


# NEW FUNCTION: Checking with DOWN sensor within the same column as Vacuuminator
def check_down(world, vac_row, vac_col):
    '''
    '''
    rows_gone_down = 1
    for row in world[vac_row + 1:]:
        if row[vac_col] == "D":
            return ['d'] * rows_gone_down
        elif row[vac_col] == "W":
            return []
        else:
            rows_gone_down += 1
    # If no dirt or walls encountered
    return []


# NEW FUNCTION: Checking with left sensor within the same row as Vacuuminator
def check_left(world, vac_row, vac_col):
    '''
    '''
    cols_gone_left = 1
    for grid_square in world[vac_row][vac_col - 1::-1]:
        if grid_square == "D":
            return ['l'] * cols_gone_left
        elif grid_square == "W":
            return []
        else:
            cols_gone_left += 1
    # If no dirt or walls encountered
    return []