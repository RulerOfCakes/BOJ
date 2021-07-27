#standard_input='1000'
N=int(input())
zeros=0
ones=1
for i in range(N-1):
    tmpzeros=zeros+ones
    if i&1:
        tmpzeros-=1
    tmpones=zeros+ones
    ones=tmpones
    zeros=tmpzeros
print(zeros)