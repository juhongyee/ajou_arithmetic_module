import random
import math
random_list = []

MAKE_NUM = 10000000
for i in range(MAKE_NUM):
    random_list.append(random.uniform(0,65))

f = open("/Users/juhong/Library/CloudStorage/OneDrive-아주대학교/대학교/3학년 겨울방학/실전코딩2_2020212223_이주홍/data/random_list2.txt",'w')

for i in range(MAKE_NUM):
    f.write("{0}\n".format(random_list[i]))

f.close()

f = open("/Users/juhong/Library/CloudStorage/OneDrive-아주대학교/대학교/3학년 겨울방학/실전코딩2_2020212223_이주홍/data/plus_answer2.txt",'w')
g = open("/Users/juhong/Library/CloudStorage/OneDrive-아주대학교/대학교/3학년 겨울방학/실전코딩2_2020212223_이주홍/data/product_answer2.txt",'w')
h = open("/Users/juhong/Library/CloudStorage/OneDrive-아주대학교/대학교/3학년 겨울방학/실전코딩2_2020212223_이주홍/data/divide_answer2.txt",'w')

for i in range(MAKE_NUM-1):
    f.write("{0}\n".format(random_list[i]+random_list[i+1]))
    g.write("{0}\n".format(random_list[i]*random_list[i+1]))
    h.write("{0}\n".format(random_list[i]/random_list[i+1]))
    

f.close()
g.close()
h.close()
