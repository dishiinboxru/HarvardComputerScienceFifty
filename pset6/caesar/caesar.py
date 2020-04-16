# verification and warning block
import sys

if len(sys.argv) != 2:
    print("WARNING ! Usage: ./caesar k\n")
    sys.exit(1)

# taking plaintext
plainText = input("plaintext: ")

# converting key from argc [1] to key int
key = int(sys.argv[1])
print(key)

# actual cyphering

print("ciphertext: ", end='')
for crypto in range(0, len(plainText), 1):
    if plainText[crypto].isalpha():
        if plainText[crypto].islower():
            cipher = chr(((ord(plainText[crypto]) - 97 + key) % 26) + 97)
            print(cipher, end='')

        if plainText[crypto].isupper():
            cipher = chr(((ord(plainText[crypto]) - 65 + key) % 26) + 65)
            print(cipher, end='')

    else:
        print(plainText[crypto], end='')

print('')