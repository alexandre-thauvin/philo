#!/usr/bin/python3
import subprocess
import os
import random

class TEST:
    def __init__(self):
        self.sleep = 0
        self.eat = 0
        self.think = 0
        self.count = 0

    def getError(self, data):
        error = int(data.splitlines()[6].split(':')[1])
        error += int(data.splitlines()[7].split(':')[1])
        return (error)

    def loop(self):
        count = 0
        while (True):
            count += 1
            p = random.randint(2,100)
            e = random.randint(2,10000)
            print("| Test : p="+str(p)+" | e="+str(e))
            args = "./philo -p "+ str(p) +" -e "+str(e)
            data = subprocess.getoutput(args)
            if (self.getError(data) != 0):
                print("| Loop "+str(count)+": Break!")
                print(data)
                return (True);
            else:
                print("| "+data.splitlines()[-3] + data.splitlines()[-2] + data.splitlines()[-1])
                print("| Loop "+str(count)+": Passed!")
                print("+"+78*'-'+"+")
                self.sleep += int(data.splitlines()[-3].split(' ')[1])
                self.eat += int(data.splitlines()[-2].split(' ')[1])
                self.think += int(data.splitlines()[-1].split(' ')[1])
                self.count += e*p
    def result(self):
        print("Result: " +str(self.count) + ' | ' +str(self.sleep) + ' | ' + str(self.eat) + ' | ' + str(self.think))
        print("Ratio: " +str(self.sleep/self.count * 100) + ' | ' + str(self.eat/self.count * 100) + ' | ' + str(self.think/self.count * 100))


if __name__ == '__main__':
    a = TEST()
    cmd = "make re"
    os.system(cmd)
    print("+"+78*'-'+"+")
    try:
        a.loop()
    except KeyboardInterrupt:
        pass
    print(77*'-'+"+")
    cmd = "make fclean"
    os.system(cmd)
    a.result()
