#!/usr/bin/env python
# coding: utf-8


#test-case
import re
import sys

#三角形测试
def triangleTest():
    class TriangleError(Exception): pass
    
    one = input("请输入第一条边：")
    two = input("请输入第二条边：")
    three = input("请输入第三条边：")
    try:
        one = float(one)
        two = float(two)
        three = float(three)
        side = [one, two, three]
        side.sort()
        print("输入数据有效")
        if (side[0] + side[1] <= side[2]):
            raise TriangleError()
        else:
            print ("是三角形")
            if (side[0]**2 + side[1] ** 2 - side[2]**2 < 1e-27):
                print("是直角三角形")
            elif (side[0]**2 + side[1] ** 2 > side[2]**2):
                print("是锐角三角形")
            else:
                 print("是钝角三角形")
    except ValueError as e:
        print(e)
        print("输入无效")
    except TriangleError :
        print("不是三角形")
    
#四则运算测试
def caclulateTest():
    class NullError(Exception): pass
    try:
        with open("testData.txt", "r", encoding="utf-8") as f:
            temp = f.readlines()
            content=[]
            for n in temp:
                content.append(n.replace('\n', ''))
            #print(content)
            rep = re.compile(r"^(-?\d+\.?\d*)[ \t]*(\+|-|\*|/)[ \t]*\(?(-?[0-9]+)\)?[ \t]*=[ \t]*(-?\d+\.?\d*)")
            for n in content:
                data = rep.findall(n)
                if len(data) == 0:
                    print(n)
                    raise NullError()
                else:
                    for x in data:
                        #print (x)
                        one = float(x[0])
                        two = float(x[2])
                        three = float(x[3])
                        if (x[1] == '+'):
                            result = (one + two == three)
                        elif (x[1] == '-'):
                            result = ((one - two - three) < 1e-15)
                        elif (x[1] == '*'):
                            result =  (one * two == three)
                        elif (x[1] == '/'):
                            result =  (one / two == three)
                        if (result):
                            print(one, x[1], two , "==", three)
                        else:
                            print(one, x[1], two , "!=", three)
    except IOError:
        print("文件打开失败")
    except NullError:
        print("以上非法输入")
        
def runnian():
    try:
        year = input("Year:")
        year = int(year)
        print (year % 4 == 0 and year % 100 != 0 or  year % 400 == 0)
    except ValueError as e:
        print(e)
        print("输入无效")

def handlerNum(num):
    # 质数大于 1
    if num > 1:
        # 查看是否有其他因子
        for i in range(2, num//2+1):
            if (num % i) == 0:
                print(num,"不是质数")
                break
        else:
            print(num, "是质数")

    # 如果输入的数字小于或等于 1，不是质数
    else:
        print(num, "不是质数") 

def handel():
    try:
        num = input("输入一个数：")
        num = int(num)
        handlerNum(num)
    except ValueError as e:
        print(e)
        print("输入无效")

def argvError():
    print("Please run testCase.py in correct way:")
    print("python testCase.py <number>\n")
    print("1\ttriangleTest\t三角形测试")
    print("2\tcaclulateTest\t四则运算测试")
    print("3\trunnian\t\t闰年判断")
    print("4\thandlerNum\t素数判断")
    
if __name__ == '__main__':
    if (len(sys.argv) != 2):
        argvError()
    elif (sys.argv[1] == '1'):
        print("开始三角形测试：")
        triangleTest()
    elif (sys.argv[1] == '2'):
        print("开始四则运算测试：")
        caclulateTest()
    elif (sys.argv[1] == '3'):
        print("开始闰年判断：")
        runnian()
    elif (sys.argv[1] == '4'):
        print("开始素数判断：")
        handel()
    else:
        argvError()