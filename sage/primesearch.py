from sage.all import *

def check(cof,ell):
    prod = cof
    for l in ell:
        prod *= l
    if is_prime(prod-1):
        print(prod-1)
        print(">>>>>>>>>>>>>>",numerical_approx(log(prod-1, 2),digits=5))
    return is_prime(prod-1)

N = 106 #number of ell's
max_l = 321193
min_l = 83
cof = 4 #cofactor
interval = (max_l - min_l)/N

ell = [min_l]
l = next_prime(min_l)
for i in range(N-1):
    while l < min_l + len(ell)*interval:
        l = next_prime(l)
    ell.append(l)
ell[-1] = max_l

n = len(ell)
print("interval=", interval)

#inflate:
ell = [19, 31]+ell

prod = cof
for l in ell:
    prod*=l
print("prod=",prod)
print("bits=", int(log(prod, 2)))

for i in range(len(ell)):
    ell[i] = next_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = next_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = next_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = next_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = next_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = previous_prime(ell[i])
    ell[i] = previous_prime(ell[i])
    ell[i] = previous_prime(ell[i])
    ell[i] = previous_prime(ell[i])
    ell[i] = previous_prime(ell[i])
    ell[i] = previous_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = previous_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = previous_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = previous_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = previous_prime(ell[i])
    if check(cof, ell):
        print("ell=",ell)
    ell[i] = next_prime(ell[i])
    ell[i] = next_prime(ell[i])
    ell[i] = next_prime(ell[i])
    ell[i] = next_prime(ell[i])
    ell[i] = next_prime(ell[i])
