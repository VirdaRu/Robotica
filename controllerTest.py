
# 7 is X 6 is Y
str = "JS1:40:9:1#JS2:-1:4:1#BSW1:1#BSW2:0#BSW3:1#BSW4:1#LSW1:1#LSW2:1#LSW3:1#LSW4:1"
JS1 = []
JS2 = []

BSW = []
LSW = []
# splits de binnengekomen data in een array
data = str.split("#")

# ga elk element langs en stop ze in de juiste array
for i in range(len(data)):
    if i < 1:
        JS1 = data[i].split(":")
        JS1.pop(0)
    elif i < 2:
        JS2 = data[i].split(":")
        JS2.pop(0)
    elif i < 6:
        BSW.append(data[i].split(":")[1])
    elif i < 10:
        LSW.append(data[i].split(":")[1])

    # print(data[i].split(":")[1])

print(JS1)
print(JS2)
print(BSW)
print(LSW)

# doe dingen afhankelijk van de command
if int(JS1[1]) > 30:
    # stuur forwards
    print("forward")
    pass
elif int(JS1[1]) < -30:
    # stuur reverse
    print("reverse")
    pass

if int(JS1[0]) > 30:
    # stuur forwards
    print("right")
    pass
elif int(JS1[0]) < -30:
    # stuur reverse
    print("left")
    pass
