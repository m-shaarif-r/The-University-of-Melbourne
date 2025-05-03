def longest_prefix_suffix(sa,sb):
    []
    if sa == '' or sb == '':
        return ''
    else:
        while sa:
            if sb.endswith(sa):
                return(sa)
            else:
                sa[:] = sa[:-1]
        return ""
    
longest_prefix_suffix("bababab", "abababa")