start_val = 0
num_row = 16
num_col = 16
for x in range(num_row):
    for y in range(num_col):
        print(2*(hex(start_val + y)[2:].zfill(2)),' ',end='')
    print('\n')
    start_val += 16


