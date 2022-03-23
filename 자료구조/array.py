a=[]
b=[]
c=[]

p=0

num1=int(input("첫번째 배열의 원소개수를 입력하세요: "))
print("리스트에 넣을",num1,"개의 원소를 입력해주세요:")

for p in range(num1):
    val=int(input())
    a.append(val)
a.sort()
num2=int(input("두번째 배열의 원소개수를 입력하세요: "))
print("리스트에 넣을",num2,"개의 원소를 입력해주세요:")

for p in range(num2):
    val=int(input())
    b.append(val)
b.sort()


i=0
j=0

while i<num1 and j<num2 :
    
    if a[i]<=b[j]:
        c.append(a[i])
        i+=1

    else:
        c.append(b[j])
        j+=1

if i==num1:
    for p in range(j, num2):
        c.append(b[p])

elif j==num2:
    for p in range(i, num1):
        c.append(a[p])
    
print("병합된 리스트의 원소들은 다음과 같습니다.: ")
print(c)

a=input()
