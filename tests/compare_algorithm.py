
def compare_dates(s1, m1, h1, d1, n1, y1, s2, m2, h2, d2, n2, y2):
    if y1 > y2:
        return True
    if n1 > n2:
        return True
    if d1 > d2:
        return True
    if h1 > h2:
        return True
    if m1 > m2:
        return True
    if s1 > s2:
        return True

    return False

date1 = input("enter date 1 ==> ")
a = date1.split(" ")

date2 = input("enter date 2 ==> ")
b = date2.split(" ")

print(str(compare_dates(a[0], a[1], a[2], a[3], a[4], a[5],
                        b[0], b[1], b[2], b[3], b[4], b[5])))
