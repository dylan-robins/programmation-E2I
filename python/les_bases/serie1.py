def is_even_and_div_3(n):
    return (n % 2 == 0) and (n % 3 == 0)

def is_between_0_20(n):
    return 0 <= n <= 20

def str_is_div_3(arr):
    n = int(arr)
    return n % 3 == 0

def question4():
    x = input("Enter the value of x : >>> ")
    y = input("Enter the value of Y : >>> ")

    print("x =", x, ", y =", y)

    x, y = y, x

    print("x =", x, ", y =", y)

def question5():
    PI = 3.141592653589793
    r = 20
    d = 2 * r
    p = 2 * PI * r
    s = PI * (r ** 2)
    print(f"Un cercle de rayon {r} a pour diamètre {d}, pour circonférence {p} et pour surface {s}")

if __name__ == "__main__":
    assert(is_even_and_div_3(6))
    assert(not is_even_and_div_3(2))
    assert(not is_even_and_div_3(3))
    assert(not is_even_and_div_3(15))

    assert(is_between_0_20(0))
    assert(is_between_0_20(20))
    assert(is_between_0_20(10))
    assert(not is_between_0_20(-1))
    assert(not is_between_0_20(25))

    assert(str_is_div_3("6"))
    assert(str_is_div_3("15"))
    assert(not str_is_div_3("4"))

    question4()
    question5()