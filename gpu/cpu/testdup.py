
f = open("../256-badkeys.txt", "r")

content = f.read()
content = content.split("\n")

f2 = open("256-badKeys.txt", "r")

content2 = f2.read()
content2 = content2.split("\n")

print len(content)
print len(content2)
    
for con in content:
    if con not in content2:
        print con

for con in content2:
    if con not in content:
        print con
