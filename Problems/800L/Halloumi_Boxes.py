# https://codeforces.com/contest/1903/problem/A

t = int(input())
 
while t:
    n, k = list(map(int, input().split()))
    ls = list(map(int, input().split()))
    
    if k > 1:
        print('YES')
    else:
        isSorted = True
        i = 1
        
        while i < len(ls):
            if ls[i] < ls[i-1]: 
                isSorted = False
                break
            i += 1
        
        if isSorted: print('YES')
        else: print('NO')
        
    t -= 1