import random

tx = random.randint(1,30000)
ty = random.randint(1,30000)
tz = 29999
def generateCycle(f):
    x = "A" +" <- " + "M"
    f.write(str(x) + "\n")
    x = "A" +" -> " + "N"
    f.write(str(x) + "\n")
    x = "B" +" <- " + "N"
    f.write(str(x) + "\n")
    x = "B" +" -> " + "K"
    f.write(str(x) + "\n")
    x = "c" +" <- " + "K"
    f.write(str(x) + "\n")
    x = "c" +" -> " + "L"
    f.write(str(x) + "\n")
    x = "r" +" <- " + "L"
    f.write(str(x) + "\n")
    x = "r" +" -> " + "T"
    f.write(str(x) + "\n")
    x = "L" +" <- " + "T"
    f.write(str(x) + "\n")
    x = "L" +" -> " + "F"
    f.write(str(x) + "\n")
    x = "H" +" <- " + "F"
    f.write(str(x) + "\n")
    x = "H" +" -> " + "M"
    f.write(str(x) + "\n")
    
    
with open("test8.txt","w") as f:
    switch = True
    for i in range(30000):
        if i == tx:
            generateCycle(f)
        elif switch:
            x = str(i) +" <- " + str((i+1))
            switch = False
            f.write(str(x) + "\n")
        else:
            x = str(i) +" -> " + str((i+1))
            switch = True
            f.write(str(x) + "\n")
        
            
        
with open("test9.txt","w") as f:
    switch = True
    for i in range(30000):
        if i == ty:
            generateCycle(f)
        elif switch:
            x = str(i) +" <- " + str((i+1))
            switch = False
            f.write(str(x) + "\n")
        else:
            x = str(i) +" -> " + str((i+1))
            switch = True
            f.write(str(x) + "\n")
        
with open("test10.txt","w") as f:
    switch = True
    for i in range(30000):
        if i == tz:
            generateCycle(f)
        elif switch:
            x = str(i) +" <- " + str((i+1))
            switch = False
            f.write(str(x) + "\n")
        else:
            x = str(i) +" -> " + str((i+1))
            switch = True
            f.write(str(x) + "\n")

print("cycle at "+ str(tx)+ "\n")
print("cycle at "+ str(ty)+ "\n")
print("cycle at "+ str(tz)+ "\n")
        

