
def snake_to_camel(test_str):
    l = test_str.split('_')
    res = l[0] + ''.join(ele.title() for ele in l[1:])
    return res

snakes = [
    'hello_world',
    'hello_world2',
    'hello_world_2',
    'hello_world_3_3asdf',
    'hello_world_4__asdasdf__222aaa_',
]
for i in snakes:
    camel = snake_to_camel(i)
    print(i + " \t " + camel)



