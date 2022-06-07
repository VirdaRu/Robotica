

str = "JS1:7:6:1#JS2:-1:4:1#BSW1:1#BSW2:0#BSW3:1#BSW4:1#LSW1:1#LSW2:1#LSW3:1#LSW4:1"

data = str.split("#")

for i in range(len(data)):
    if i < 2:
        print(data[i].split(":"))
    # print(data[i].split(":")[1])
