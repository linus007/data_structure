# -*- coding: UTF-8 -*-
#!/usr/bin/python

import threading
import random
import time
global TOTAL_SIZE 
#总共允许苹果的个数
TOTAL_SIZE = 10
global counts
#当前拥有的苹果的个数
counts = 0
#进程间隔时间
delay = 1
#条件变量
con = threading.Condition()

# 只能生产一个苹果的生产者
class ProducerA(threading.Thread):
    def __init__(self, threadId, name):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
    def run(self):
        while 1:
            if con.acquire():
                global counts
                if counts < TOTAL_SIZE:
                    counts += 1
                    print "生产者Ａ生产１个苹果, 总共有苹果%d个苹果"%(counts)
                    con.notify()
                else:
                    con.wait()
                time.sleep(delay)
                con.release()
#　一次能生产两个苹果的生产者
class ProducerB(threading.Thread):
    def __init__(self, threadId, name):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
    def run(self):
        while 1 :
            if con.acquire():
                global counts
                left = TOTAL_SIZE - counts
                if left >1 :
                    counts += 2
                    print "生产者B生产2个苹果, 总共有苹果%d个苹果"%(counts)
                    con.notify()
                elif left == 1:
                    counts += 1
                    print "生产者B生产1个苹果, 总共有苹果%d个苹果"%(counts)
                    con.notify()
                else :
                    con.wait()
                time.sleep(delay)
                con.release()

# 生成１个１～５的随机数`
def random_1_5():
    return random.randint(1, 5)

#消费者
class Consumer(threading.Thread):
    def __init__(self, threadId, name):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
    def run(self):
        while 1:
            if con.acquire():
                eat = random_1_5()
                global counts
                if counts > eat:
                    counts -= eat
                    print "消费者吃掉%d个苹果, 还剩%d个苹果"%(eat, counts)
                    con.notify()
                elif counts > 0:
                    print "消费者吃掉%d个苹果, 还剩%d个苹果"%(counts, 0)
                    counts = 0
                    con.notify()
                else :
                    con.wait()
                time.sleep(delay)
                con.release()
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






