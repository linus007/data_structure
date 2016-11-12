# -*- coding: UTF-8 -*-

#!/usr/bin/python

from multiprocessing import Process, Manager, Lock
import os
import random
import time

lock = Lock()
manager = Manager()

#当前拥有的苹果个数
counts = manager.Value("counts", 0)


global TOTAL_SIZE
#总共允许苹果的个数
TOTAL_SIZE = 10

def factory(kinds, lock):
    while 1:
        with lock:
            if kinds == 1:
                if counts.value < TOTAL_SIZE:
                    counts.value += 1
                    print "生产者Ａ生产１个苹果, 总共有苹果%d个苹果"%(counts.value)
            elif kinds == 2: 
                left = TOTAL_SIZE - counts.value
                if left >1 :
                    counts.value += 2
                    print "生产者B生产2个苹果, 总共有苹果%d个苹果"%(counts.value)
                elif left == 1:
                    counts.value += 1
                    print "生产者B生产1个苹果, 总共有苹果%d个苹果"%(counts.value)
            elif kinds == 3:
                eat = random.randint(1, 5)
                if counts.value > eat:
                    counts.value -= eat
                    print "消费者吃掉%d个苹果, 还剩%d个苹果"%(eat, counts.value)
                elif counts.value > 0:
                    print "消费者吃掉%d个苹果, 还剩%d个苹果"%(counts.value, 0)
                    counts.value -= counts.value
if __name__ == '__main__':
    process = []
    pa = Process(target=factory, args=(1, lock))
    pb = Process(target=factory, args=(2, lock))
    consumer = Process(target=factory, args=(3, lock))
    process.append(pa) 
    process.append(pb)
    process.append(consumer)
    for i in range (3):
        process[i].daemon = True

    for j in range(3):
        process[j].start()
    for k in range(3):
        process[k].join()
