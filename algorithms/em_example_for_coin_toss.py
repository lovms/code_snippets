import sys
import operator
import math

'''
this program implements EM algorithm to calculate probability of toss of two coins,

with data of 5 groups of 10 toss trials without knowing which coin was exactly used for each group.

Data is from the Nature paper : What is the expectation maximization algorithm? Chuong B Do & Serafim
'''
def calc_pb_with_binomial((h, t)):
    return math.factorial(h+t) / (math.factorial(h) * math.factorial(t))

''' 5 group of 10 toss leaves 5 tuples of (count of head, count of tail)'''
trials = [(5, 5), (9, 1), (8, 2), (4, 6), (7, 3)]
#trials_sum = sum(operator.getitem(trials, 0)) + sum(operator.getitem(trials, 1))

#print("trials_sum %d" % (trials_sum))

''' using for calculation probability under  binomial distribution'''
combinatorial_number = map(calc_pb_with_binomial, trials)

#print("combinatorial_Number")
#print combinatorial_number


''' 
initial guess of probability of toss of coin A and B 

We should always try several intial guess which may end with very different convergence
'''
theta_A = 0.6 #
theta_B = 0.5

iters = 100

for it in range(iters):
    ''' E step '''
    pb_tr_A = [combinatorial_number[i] * (theta_A**trials[i][0]) * ((1-theta_A)**trials[i][1]) for i in range(len(trials))]
    pb_tr_B = [combinatorial_number[i] * (theta_B**trials[i][0]) * ((1-theta_B)**trials[i][1]) for i in range(len(trials))]


    #probabilty of A and B for each group
    tmp_pb = map(lambda x:x[0] + x[1], zip(pb_tr_A, pb_tr_B))
    pb_tr_A = [pb_tr_A[i] / tmp_pb[i] for i in range(len(trials))]
    pb_tr_B = [pb_tr_B[i] / tmp_pb[i] for i in range(len(trials))]
    
    ''' M step '''
    x_A = [(pb_tr_A[i] * trials[i][0], pb_tr_A[i] * trials[i][1]) for i in range(len(trials))]
    x_B = [(pb_tr_B[i] * trials[i][0], pb_tr_B[i] * trials[i][1]) for i in range(len(trials))]


    head_A = sum([v[0] for v in x_A])
    tail_A = sum([v[1] for v in x_A])
    head_B = sum([v[0] for v in x_B])
    tail_B = sum([v[1] for v in x_B])

    theta_A_hat = head_A / (head_A + tail_A)
    theta_B_hat  = head_B / (head_B + tail_B)

    print("iter %d: theta_A %.3f - theta_B %.3f" % (it, theta_A_hat, theta_B_hat))
    if abs(theta_A - theta_A_hat) < 1e-6 and abs(theta_B - theta_B_hat) < 1e-6:
        print("EM converged and early stop")
        exit(0)
    theta_A, theta_B = theta_A_hat, theta_B_hat

