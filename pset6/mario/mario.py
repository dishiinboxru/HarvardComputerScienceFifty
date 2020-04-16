while True :
    inputHeight = input ("Height : ")
    if inputHeight.isdigit():
        height = int(inputHeight)
        if height < 24 and height > -1 :
            break

for line in range(0 , height , 1) :
    spaceline = ' ' *(height - line - 1)
    print (spaceline, end ='')
    hasline = '#' * (line+2)
    print (hasline)