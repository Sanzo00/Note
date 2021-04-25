import sys, os

print(sys.argv[0])
path = sys.argv[1]
print(path)

if '.md' not in path:
    print('file type error!')
    exit(1)


with open(path, 'r', encoding='utf-8') as f:
    content = f.read()
    content = content.replace('img/', 'https://sanzo.top/usr/uploads/img/')


with open(path, 'w', encoding='utf-8') as f:
    f.write(content)


print(path, 'is done!')
