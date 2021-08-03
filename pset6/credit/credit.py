from cs50 import get_int

# Request input from user
num = str(get_int("Number: "))

singles = 0
doubles = 0
length = len(num)

if length != 15 and length != 16:
    print("INVALID")

else:
    # iterate along and sum doubles
    for i in range(length - 2, -1, -2):
        temp = str(int(num[i]) * 2)
        for y in range(len(temp)):
            doubles += int(temp[y])

    # interate along and sum singes
    for i in range(length - 1, -1, -2):
        singles += int(num[i])

    # Store first and first two digits
    first = num[0]
    second = num[0] + num[1]

    # Check if luhn value is is correct
    luhn = str(singles + doubles)
    if luhn[-1] != "0":
        print("INVALID")

    # Figure out what type of card
    elif length == 15 and (second == "34" or second == "37"):
        print("AMEX")

    elif len(num) == 16 and (second == "51" or second == "52" or second == "53" or second == "54" or second == "55"):
        print("MASTERCARD")

    elif (len(num) == 16 or len(num) == 13) and first == "4":
        print("VISA")

    else:
        print("INVALID")