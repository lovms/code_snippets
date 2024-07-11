'''
Codes here refer to : https://www.freecodecamp.org/news/python-decorators-explained-with-examples/

It may help to view: https://www.freecodecamp.org/news/the-python-decorator-handbook/, where more examples will be found.

遗留问题：对同一个函数使用多个decorator时，调用顺序以及需要注意避免的问题有哪些？？
'''
from datetime import datetime

'''
Example 1:
解释 decorator 的实现原理。

另外，为什么要包两/三层?? 其实 wrapper 是实际增加装饰内容的封装, 

1) 针对装饰器本身不带参数的情形，增加外一层 log_datetime，实际上可以将func 的参数 和装饰函数的参数 分开, 从而通过技巧“ daily_backup = log_datetime(daily_backup)”，
实现被装饰函数“无变化地”被调用，不会因为增加decorator改变原有的调用方式。
否则，不增加外一层的封装，就只能是“ wrapper(func, a, b)”， 这样就会改变原有函数func的调用方式了！！！

2) 针对装饰带参数的情形，还需要再增加外一层，专门接收装饰器的参数。这里并没有将`func`参数和装饰器参数放在一层传入，
   从使用上讲，使用@symbol时，会提前传入装饰器参数，比传入`func`更早，所以，装饰器参数放在外一层。
   可以参考我写的不使用@symbol时的等价调用。归根结底，使用装饰器是不影响原始函数的调用方式的！！！
'''
###  装饰器本身不带参数  ###
def log_datetime(func):
    def wrapper(a, b):   # arguments for functions being decorated
        print(f'Function: {func.__name__}\nRun on : {datetime.today().strftime("%Y-%m-%d %H:%M:%S")}')
        print(f'{"-"*30}')
        func(a, b)
    return wrapper

@log_datetime
def daily_backup(a: int, b: int):
    print(f'Daily backup job has finished @ {a} : {b}')

#daily_backup = log_datetime(daily_backup)   # 不使用@symbol的等价调用

daily_backup(1, 2)    # equivalent

###  装饰器本身带参数  ###
def log_datetime(log_level):  # decorators' arguments
    def decorator(func):
        def wrapper(a, b):   # arguments for functions being decorated
            print(f'{log_level}| Function: {func.__name__}\nRun on : {datetime.today().strftime("%Y-%m-%d %H:%M:%S")}')
            print(f'{"-"*30}')
            func(a, b)
        return wrapper
    return decorator

@log_datetime(log_level='Debug')
def daily_backup(a: int, b: int):
    print(f'Daily backup job has finished @ {a} : {b}')

# 不使用@symbol的等价调用
#daily_backup_decorator = log_datetime(log_level='Debug')
#daily_backup = daily_backup_decorator(daily_backup)    

# 或者直接 daily_backup = log_datetime(log_level='Debug')(daily_backup)

daily_backup(1, 2)    # equivalent


'''
Example 2:
decorators 会隐藏被装饰函数的属性。这里可以提供使用 wraps装饰器来缓解这一问题。
'''
from functools import wraps

def my_decorator_func(func):

    @wraps(func)
    def wrapper_func(*args, **kwargs):
        func(*args, **kwargs)
    return wrapper_func

@my_decorator_func
def my_func(my_args):
    ''' Example docstring for function'''
    pass

print(my_func.__name__)
print(my_func.__doc__)


'''
Example 3:
use decorators to measure functions' performance
'''
import tracemalloc
from time import perf_counter

def measure_performance(func):
    '''Measure performance of a function'''

    @wraps(func)
    def wrapper(*args, **kwargs):
        tracemalloc.start()
        start_time = perf_counter()
        func(*args, **kwargs)
        current, peak = tracemalloc.get_traced_memory()
        finish_time = perf_counter()
        print(f'Function: {func.__name__}')
        print(f'Method: {func.__doc__}')
        print(f'Memory usage:\t\t {current / 10**6:.6f} MB \n'
              f'Peak Memory usage:\t {peak / 10**6:.6f} MB ')
        print(f'Time elapsed is seconds: {finish_time - start_time:.6f}')
        print(f'{"-"*40}')
        tracemalloc.stop()
    return wrapper

@measure_performance
def make_list1():
    ''' Range '''
    my_list = list(range(100000))

@measure_performance
def make_list2():
    ''' List comprehension '''
    my_list = [1 for i in range(100000)]

@measure_performance
def make_list3():
    ''' Append '''
    my_list = []
    for item in range(100000):
        my_list.append(item)

@measure_performance
def make_list4():
    ''' Concatenation '''
    my_list = []
    for item in range(100000):
        my_list = my_list + [item]


print(make_list1())
print(make_list2())
print(make_list3())
print(make_list4())


'''
Example 4:
use decorators with Python classes.

a decorator class initializes with __init__ by using `func` as an argument.

With __call__()  method the decorator is executed when an instance of the class is created. 

functions being decorated can be passed through __call__ method. 
'''

import requests

class LimitQuery:
    def __init__(self, func):
        self.func = func
        self.count = 0
    
    def __call__(self, *args, **kwargs):
        self.limit = args[0]
        if self.count < self.limit:
            self.count += 1
            return self.func(*args, **kwargs)
        else:
            print(f'No queries left. All {self.count} queries used.')
            return   #  直接return是不是会有点问题，返回值类型不一致啊！！！

@LimitQuery
def get_coin_price(limit):
    ''' View the Bitcoin Price index (BPI)'''
    url = requests.get('https://api.coindesk.com/v1/bpi/currentprice.json')

    if url.status_code == 200:
        text = url.json()
        return f"${float(text['bpi']['USD']['rate_float']):.2f}"


print(get_coin_price(5))
print(get_coin_price(5))
print(get_coin_price(5))
print(get_coin_price(5))
print(get_coin_price(5))
print(get_coin_price(5))