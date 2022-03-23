
mat1 = [[0]*3 for i in range(3)]
mat2 = [[0]*3 for i in range(3)]


j=0
print("첫번째 행렬을 입력하세요:")
for i in range(3):
    line = input()
    for j in range(3):
        mat1[i][j]=int(line.split()[j])
       
print("\n두번째 행렬을 입력하세요:")

for i in range(3):
    line = input()
    for j in range(3):
        mat2[i][j]=int(line.split()[j])

print("행렬간의 합을 원하시면 1, 차를 원하시면 2, 곱을 원하시면 3을 입력해주세요")
select=int(input())

if select==1:

    print("행렬의 합:\n")
    for i in range(3):
        for j in range(3):
            print(mat1[i][j]+mat2[i][j]," ",end="")
        print("\n")
elif select==2:
    
    print("행렬의 차:\n")
    for i in range(3):
        for j in range(3):
            print(abs(mat1[i][j]-mat2[i][j])," ",end="")
        print("\n")
elif select==3:
    print("행렬의 곱:\n")
    for i in range(3):
        for j in range(3):
            tmp=0
            for k in range(3):
                tmp+=mat1[k][j]*mat2[i][k]
            print(tmp," ",end="")
        print("\n")
else :
    print("1, 2, 3중의 숫자를 입력해주세요")

        
    
a=input()
