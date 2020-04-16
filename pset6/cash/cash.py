# supplementary function to check for float
def is_float(s):
    try:
        float(s)
        return True
    except ValueError:
        return False


# main block
while True:
    inputChange = input("Change owed: ")
    if is_float(inputChange) and float(inputChange) > 0:
        break

change = float(inputChange)
cents = int(change * 100)
quarters = int(cents / 25)
dimes = int((cents % 25) / 10)
nickles = int((cents % 25 % 10) / 5)
pennies = int((cents % 5) / 1)

total = int(quarters + dimes + nickles + pennies)

print(total)