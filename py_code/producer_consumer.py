# -*- coding: UTF-8 -*-
#!/usr/bin/python
print"hello world!"

import threading
import random
import time
global TOTAL_SIZE 
TOTAL_SIZE = 10
global counts
counts = 0
delay = 1
# 只能生产一个苹果的生产者
class ProducerA(threading.Thread):
    def __init__(self, threadId, name):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
    def run(self):
        while 1:
            threadLock.acquire()
            global counts
            if counts < TOTAL_SIZE:
                print "counts:%d"%(counts)
                global counts
                print "生产者Ａ生产１个苹果"
                counts += 1
            time.sleep(delay)
            threadLock.release()
            print "AAAAAA"
#　一次能生产两个苹果的生产者
class ProducerB(threading.Thread):
    def __init__(self, threadId, name):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
    def run(self):
        while 1 :
            threadLock.acquire()
            global counts
            left = TOTAL_SIZE - counts
            if left >1 :
                global counts
                print "生产者B生产2个苹果"
                counts += 2
            elif left == 1:
                print "生产者Ｂ生产１个苹果"
                counts += 1
            time.sleep(delay)
            threadLock.release()
            print "BBBBBBB"
# 生成１个１～５的随机数
def random_1_5():
    return random.randint(1, 5)

class Consumer(threading.Thread):
    def __init__(self, threadId, name):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
    def run(self):
        while 1:
            threadLock.acquire()
            eat = random_1_5()
            global counts
            if counts > eat:
                global counts
                print "消费者吃掉%d个苹果"%(eat)
                counts -= eat
            elif counts > 0:
                global counts
                print "消费者吃掉%d个苹果"%(counts)
                counts = 0
            time.sleep(delay)
            threadLock.release()
            print "consumer"
# 锁
threadLock = threading.Lock()

#创建生产者ＡＢ和消费者
pa = ProducerA(1, "pa")
pb = ProducerB(1, "pc")
cm = Consumer(1, "consumer")

pa.start()
pb.start()
cm.start()
pa.join()
pb.join()
cm.join()







