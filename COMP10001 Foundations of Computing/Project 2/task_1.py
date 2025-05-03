from math import log

ALL_VALS = [["wavy","curly","beanie","cap"],
            ["red","blue","yellow","green"],
            ["sneakers","bowtie","sunglasses","scarf"],
            ["tiktok","instagram","discord","snapchat"]]


def zbini_attrs(id_num):
    '''
    Args: An int `idnum` between 0 and 255 inclusive (Zommerbini ID number)
    Returns: a tuple `final_vals` of 4 different attribute values in the 
    following order: [Hair/hat, Colour, Accessory, Social]
    '''
    
    final_vals = []
    num_in_range = id_num in range(256)
    
    # for each digit in `new_id_num`, check what attribute option is 
    # represented, and append this to the 'final_vals'
    if num_in_range:
        new_id_num = convert_base(id_num, 4)
        for attr_num in range(len(new_id_num)):
            option_num = int(new_id_num[attr_num])
            final_vals.append(ALL_VALS[attr_num][option_num])
        return tuple(final_vals)
    else:
        return None

def convert_base(number, base):
    '''
    Args: Takes ints `number` and `base`
    Returns: `number` in base `base` as the string `converted`
    '''
    # Get the highest power of the base by which `number` can be divided by
    if number != 0:
        max_power = int(log(number,base))

        converted = ""
        # Calculate new digits for each power of the base.
        for power in range(max_power,-1,-1):
            converted += str(number // base**power)
            number %= base**power

        converted = converted.zfill(4)
        return converted
    else:
        return "0000"
