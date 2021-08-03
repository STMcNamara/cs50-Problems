from cs50 import get_int

# Request input from user and check within limits
while True:
    rows = get_int("Please enter number of rows: ")
    if rows >= 0 and rows <= 23:
        break

width = rows * 2 + 2

# Iterate from top down using print and concatination
for row in range(1, rows + 1):
    print(" " * ((width//2) - row - 1) + "#" * row + "  " + "#" * row)