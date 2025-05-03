def distance_to_wall(world):
    '''
    Args:
        Accepts a list of lists 'world made up of the strings 'X','W','E','D'
        representing a world grid
    Returns:
        Returns an integer equal to closest distance from 'X' to any 'W'
        Returns 'None' if no 'W' present
    '''
    closest_dist = None
    # Find row and column numbers of Vacuuminator position
    found_x = False
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == 'X':
                vac_row, vac_col = row_num, col_num
                found_x = True
                break
        if found_x:
            break

    # Check in each row and in each grid value for a wall 
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == 'W':
                # FINISH THE COMMENT
                dist_from_vac = abs(row_num - vac_row) + abs(col_num - vac_col)
                if closest_dist is None or dist_from_vac < closest_dist:
                    closest_dist = dist_from_vac

    return closest_dist

    

#original submission without found_x
"""     def distance_to_wall(world):
    '''
    Args:
        Accepts a list of lists 'world made up of the strings 'X','W','E','D'
        representing a world grid
    Returns:
        Returns an integer equal to closest distance from 'X' to any 'W'
        Returns 'None' if no 'W' present
    '''
    closest_dist = None
    # Find row and column positions of Vacuuminator
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == 'X':
                vac_row, vac_col = row_num, col_num

    # Check in each row and in each grid value for a wall 
    for row_num, row in enumerate(world):
        for col_num, grid_value in enumerate(row):
            if grid_value == 'W':
                # FINISH THE COMMENT
                dist_from_vac = abs(row_num - vac_row) + abs(col_num - vac_col)
                if closest_dist is None or dist_from_vac < closest_dist:
                    closest_dist = dist_from_vac

    return closest_dist """