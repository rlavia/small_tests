
def my_decorator(func):
    def wrapper_my_decorator(*args, **kwargs):
        #decorated
        func(*args, **kwargs)
        #decorated
        return
    return wrapper_my_decorator



