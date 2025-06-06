import random
from random import shuffle

def write1(f, a):
    f.write(str(a) + str("\n"))

def write1_no_lf(f, a):
    f.write(str(a))

def write2(f, a, b):
    f.write(str(a) + str(" ") + str(b) + str("\n"))

def write3(f, a, b, c):
    f.write(str(a) + str(" ") + str(b) +  str(" ") + str(c) + str("\n"))



with open("input.txt", "w") as file:
    file.write(str("20\n"))

    for i in range(20):
        a = random.randint(1, 500)
        b = random.randint(1, 500)
        file.write(str(a) + str(" ") + str(b) + str("\n"))

"""

with open("input.txt", "w") as file:
    file.write(str("250000 5000\n"))

    for i in range(250000):
        a = random.randint(1, 65536)
        file.write(str(a) + str("\n"))




with open("input.txt", "w") as file:
    file.write(str("3\n"))
    file.write(str("5\n"))

    for i in range(5):
        a = random.randint(1, 3)
        b = random.randint(1, 3)
        file.write(str(a) + str(" ") + str(b) + str("\n"))


with open("input.txt", "w") as file:
    file.write(str("1\n"))
    file.write(str("20 100\n"))
    for i in range(100):
        n = random.randint(1,150)
        if n > 100:
            n = 100
        file.write(str(n) + str(" "))
    file.write("\n")

    for i in range(100):
        n = random.randint(1,150)
        if n > 100:
            n = 100
        file.write(str(n) + str(" "))
    file.write("\n")



# 1에서 10 사이의 숫자 리스트 생성
numbers = list(range(1, 11))

# 모든 가능한 쌍을 생성 (순서가 중요하지 않도록 중복 쌍 제외)
pairs = [(i, j) for i in numbers for j in numbers if i != j]

# 쌍을 랜덤하게 섞음
random.shuffle(pairs)



with open("input.txt", "w") as file:
    file.write(str("10 30\n"))
    for pair in pairs[:30]:  # 5쌍만 출력하고 싶다면 [:5]
        file.write(str(pair[0]) + str(" "))
        file.write(str(pair[1]) + str(" "))
        file.write("1000000")
        file.write("\n")




dataCnt = 50
queryCnt = 50
arr = []

with open("input.txt", "w") as file:
    file.write(str(1) + str("\n"))
    file.write(str(dataCnt) + str(" ") + str(dataCnt) + str("\n"))
    for i in range(dataCnt):
        k = random.randint(1, 20)
        file.write(str(k) + str(" "))
    file.write("\n")
    for i in range(queryCnt):
        q = random.randint(1, 5)
        file.write(str(q) + str(" "))
    file.write("\n")

    for i in range(queryCnt):
        q = random.randint(1, dataCnt)
        file.write(str(q) + str(" "))
    file.write("\n")

    for i in range(queryCnt):
        q = random.randint(1, 100)
        file.write(str(q) + str(" "))
    file.write("\n")



datacnt = 10
repCnt = 4
arr = []

with open("input.txt", "w") as file:
    file.write(str("10 5\n"))
    for i in range(repCnt):
        a = random.randint(1, datacnt)
        b = random.randint(1, datacnt)
        file.write(str(1) + str(" ") + str(a) + str(" ") + str(b) + str("\n"))
    c = random.randint(1, 5)
    file.write(str(2) + str(" ") + str(c) + str("\n"))








locx = 1
locy = 1


dataLim = 10
with open("input.txt", "w") as file:
    x = random.randint(1, dataLim)
    y = random.randint(1, dataLim)
    write2(file,x,y)

dataLim = 5
valRange = 50
with open("input.txt", "w") as file:
    write1(file, dataLim)
    for i in range(dataLim):
        x = random.randint(1, valRange)
        y = random.randint(1, valRange)
        if x == y:
            y = x+1
        write2(file, x,y)
    a = random.randint(1, valRange)
    write1(file, a)
    
"""

len = 200
str1 = []
str2 = []

for i in range(len):
    str1.append('R')
    str2.append('R')

for i in range(len):
    str1.append('U')
    str2.append('U')

shuffle(str1)
shuffle(str2)



with open("input.txt", "w") as file:
    write1(file, len)
    for i in range(len*2):
        write1_no_lf(file, str1[i])
    write1_no_lf(file, '\n')

    for i in range(len*2):
        write1_no_lf(file, str2[i])
    write1_no_lf(file, '\n')
    