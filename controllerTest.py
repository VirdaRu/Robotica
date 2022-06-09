# 7 is X 6 is Y
#str = "JS1:40:-40:1#JS2:-1:4:1#BSW1:1#BSW2:0#BSW3:1#BSW4:1#LSW1:1#LSW2:1#LSW3:1#LSW4:1"
joystick1 = "JS1:40:-40:1"
joystick2 = "JS2:7:4:0"
BSWstr = "BSW:0:1:0:1"
LSWstr = "LSW:1:1:0:0"
JS1 = []
JS2 = []

BSW = []
LSW = []


# LSW = LSWstr.split(":")
# LSW.pop(0)
# print(LSW)



if "BSW" in  BSWstr:
    BSW = BSWstr.split(":")
    BSW.pop(0)
    print(BSW)

    for i in range(4):
        print(BSW[i])
        if BSW[i] == "0":
            print("BSW{}".format(i))


# splits de binnengekomen data in een array
# data = str.split("#")

# # ga elk element langs en stop ze in de juiste array
# for i in range(len(data)):
#     if i < 1:
#         JS1 = data[i].split(":")
#         JS1.pop(0)
#     elif i < 2:
#         JS2 = data[i].split(":")
#         JS2.pop(0)
#     elif i < 6:
#         BSW.append(data[i].split(":")[1])
#     elif i < 10:
#         LSW.append(data[i].split(":")[1])

#     # print(data[i].split(":")[1])

# print(JS1)
# print(JS2)
# print(BSW)
# print(LSW)

# # doe dingen afhankelijk van de command
# if int(JS1[1]) > 30:
#     # stuur forwards
#     print("forward")
#     pass
# elif int(JS1[1]) < -30:
#     # stuur reverse
#     print("reverse")
#     pass

# if int(JS1[0]) > 30:
#     # stuur forwards
#     print("right")
#     pass
# elif int(JS1[0]) < -30:
#     # stuur reverse
#     print("left")
#     pass


# sub = "JS1"

# if sub in teststr:
#     JS1 = teststr.split(":")
#     JS1.pop(0)
#     print(JS1)
#     if int(JS1[1]) > 30:
#         # stuur forwards
#         print("forward")
#         pass
#     elif int(JS1[1]) < -30:
#         # stuur reverse
#         print("reverse")
#         pass

#     if int(JS1[0]) > 30:
#         # stuur forwards
#         print("right")
#         pass
#     elif int(JS1[0]) < -30:
#         # stuur reverse
#         print("left")
#         pass
