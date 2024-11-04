import os
import matplotlib.pyplot as plt
import psutil
import Levenshtein
from googletrans import Translator
import re
import sys
import subprocess

label=""

dim=2

datakun0 = dict()
datakun1 = dict()
code = dict()
NoAns = dict()

def is_sp(s):

    sp=0
    
    if s == ".":
        sp=1
    elif s == ",":
        sp=1 
    elif s == "?":
        sp=1            
    elif s == '"':
        sp=1        
    elif s == "'":
        sp=1
    elif s == "[":
        sp=1
    elif s == "]":
        sp=1
    elif s == "(":
        sp=1            
    elif s == ")":
        sp=1            
    elif s == ":":
        sp=1            
    elif s == ";":
        sp=1            
    elif s == "/":
        sp=1
    elif s == "!":
        sp=1
    elif s == "#":
        sp=1            
    elif s == "&":
        sp=1
    elif s == "$":
        sp=1
    elif s == "%":
        sp=1
    elif s == "-":
        sp=1
    elif s == "{":
        sp=1
    elif s == "}":
        sp=1    
    return sp

with open("./label.txt") as f:
    for line in f:
       label=label+line

label=label.split()

counter=0

for l in range(len(label)):
    
    strr=""
    
    title = label[l]
    
    with open("./"+title+".txt") as f:
        for line in f:
            strr=strr+line
    strr2=""

    for k in range(len(strr)):   
        if is_sp(strr[k]) > 0:
            strr2+=" "+strr[k]+" "
        else:
            strr2+=strr[k]
    
    problem = strr2.split()
            
    strr=""
    with open("./"+str(l+1)+".txt") as f:
        for line in f:
            strr=strr+line
            
    program = strr.split('\n')

    for c in range(len(program)):
        if str(program[c]) not in code:
            code[counter]=program[c]
            counter+=1

    for c in range(len(problem)):
        if str(problem[c]) not in NoAns:
            NoAns[problem[c]]=1
        else:
            NoAns[problem[c]]+=1
            
    for c in range(len(problem)):
        for d in range(len(program)):
            tmp = str(problem[c])+","+str(program[d])+","+str(d)+","+str(c)
            if len(program[d])==0:
                continue
            #if str(problem[c])=="Stdout":
                #print(tmp)
            if tmp in datakun0:
                datakun0[tmp]+=2
            else:
                datakun0[tmp]=2
            if tmp in datakun1:
                datakun1[tmp]+=2
            else:
                datakun1[tmp]=2

    if (l+1)%100 == 0 or (l+1)==len(label):
        print("params="+str(len(datakun0)+len(datakun1))+",train="+str(l+1)+"/"+str(len(label)))

def coding(s,quiz3):
    maxscore=0
    ret=""
    ret2=""
    for d in range(counter):
        a=0
        b=0
        sum=0
        hit=0
        if len(code[d])>0:
            for c in range(len(quiz3)):
                if str(quiz3[c]).isalnum()==False:
                    continue
                #if NoAns[quiz3[c]] > 50:
                    #continue
                tmp=str(quiz3[c])+","+str(code[d])+","+str(s)+","+str(c)
                #print(str(tmp))
                if tmp in datakun0:
                    a+=datakun0[tmp]
                    b+=datakun1[tmp]
                    sum=a+b
                    hit+=1
                #if str(code[d])=="//abc201_d":    
                    #print(str(tmp)+",sum="+str(sum)+",tmp="+str(tmp)+",NoAns["+str(quiz3[c])+"]="+str(NoAns[quiz3[c]]))
                if sum>maxscore and hit>=len(quiz3)/2:
                    maxscore=sum
                    ret=str(code[d])
                    ret2=str(quiz3[c])
                    #print("maxscore="+str(maxscore)+",code="+str(ret)+",word="+str(ret2)+",hit="+str(hit))
            #if maxscore>0:
                #print("maxscore="+str(maxscore)+",code="+str(ret)+",problem="+str(ret2))
    return ret,maxscore

quiz=""
with open("./quiz.txt") as f:
    for line in f:
        quiz=quiz+line        
        
quiz3=""

for k in range(len(quiz)):
    if is_sp(quiz[k]) > 0:
        quiz3+=" "+quiz[k]+" "
    else:
        quiz3+=quiz[k]
        

print("\nQuiz:\n"+str(quiz3))

quiz3=quiz3.split()

ans=""
score=0
mainfunc=0
for i in range(100):
    c,s=coding(i,quiz3)
    if "main" in c:
        mainfunc+=1
        if mainfunc >1:
            mainfunc=1
            continue
    if "return 0;" in c:
        if mainfunc==1:
            ans=ans+"return 0;\n}"
            break
    if len(c)==0:
        continue
    ans=ans+c+'\n'
    score+=s        
print("\nAnswer:\n"+ans)
print("\nScore:\n"+str(score))

f = open("gene.cpp", 'w')
f.write(ans)
f.close()
subprocess.call("python3 compile.py", shell=True)
f = open('log.txt', 'r')
num = f.read()
f.close()
if num==0:
    print("failed")
else:
    print("success")
