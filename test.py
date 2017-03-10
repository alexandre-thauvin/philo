#!/usr/bin/python3
import subprocess
import os
import random


def getError(data):
    error = int(data.splitlines()[6].split(':')[1])
    error += int(data.splitlines()[7].split(':')[1])
    return (error)

def loop():
    count = 0
    while (True):
        count += 1
        p = random.randint(2,100)
        e = random.randint(2,1000)
        print("| Test : p="+str(p)+" | e="+str(e))
        args = "./philo -p "+ str(p) +" -e "+str(e)
        data = subprocess.getoutput(args)
        if (getError(data) != 0):
            print("| Loop "+str(count)+": Break!")
            print(data)
            return (True);
        else:
            print("| "+data.splitlines()[-3] + data.splitlines()[-2] + data.splitlines()[-1])
            print("| Loop "+str(count)+": Passed!")
            print("+"+78*'-'+"+")


if __name__ == '__main__':
    cmd = "make re"
    os.system(cmd)
    print("+"+78*'-'+"+")
    loop()
    print("+"+78*'-'+"+")
    cmd = "make fclean"
    os.system(cmd)
