def make_move(world, direction):
    '''
    !!!DOCSTRING!!!
    '''
    DIR_UP = "u"
    DIR_DOWN = "d"
    DIR_LEFT = "l"
    DIR_RIGHT = "r"
    # Find row and column numbers of Vacuuminator position
    found_x = False
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == "X":
                vac_row, vac_col = row_num, col_num
                found_x = True
                break
        if found_x:
            break
    
    # Determine final grid position of Vacuuminator
    if direction == DIR_UP:
        vac_row_final, vac_col_final = vac_row - 1, vac_col
    elif direction == DIR_RIGHT: 
        vac_row_final, vac_col_final = vac_row, vac_col + 1
    elif direction == DIR_DOWN:
        vac_row_final, vac_col_final = vac_row + 1, vac_col
    else:
        vac_row_final, vac_col_final = vac_row, vac_col - 1

    # Check if it goes off the world or hits a wall, and don't move if so
    if (vac_row_final not in range(len(world))) or (vac_col_final not in range(len(world[vac_row]))):
        return world
    elif world[vac_row_final][vac_col_final] == "W":
        return world

    # Move Vacuuminator to new position and leave original position empty.
    else:
        world[vac_row_final][vac_col_final] = "X"
        world[vac_row][vac_col] = "E"
        return world