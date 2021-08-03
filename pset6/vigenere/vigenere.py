import sys
from cs50 import get_string

# Define a main function to allow returns


def main():
    # Return 1 if incorrect number of arguments provided
    if len(sys.argv) != 2:
        print("Please provide one command line argument only")
        sys.exit(1)

    # Return 1 if the key is not letters ony
    key = sys.argv[1]
    if not key.isalpha():
        print("Please provide only alphabetical characters")
        sys.exit(1)

    # Convert key to list of shifts
    key = key.lower()
    keylist = []
    for i in key:
        keylist.append(ord(i) - 97)

    # Get string of plain text from the user
    plaintext = get_string("plaintext: ")
    ciphertext = ""
    shiftpos = 0
    shiftlen = len(keylist)

    # For each i in plaintext:
    for i in plaintext:

        # If a letter:
        if i.isalpha():
            # Calculate the shift
            shift = keylist[shiftpos]
            # Check if shift needs to loop back
            if ord(i.lower()) + shift > 122:
                ciphertext += chr(ord(i) + shift - 26)
            else:
                ciphertext += chr(ord(i) + shift)
            # Increment shift position
            if shiftpos + 1 == shiftlen:
                shiftpos = 0
            else:
                shiftpos += 1
        # If not a letter append the symbol
        else:
            ciphertext += i

    # Print the ciphertext
    print(f"ciphertext: {ciphertext}")


if __name__ == "__main__":
    main()