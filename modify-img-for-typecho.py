import os

'''
批量处理，修改 img/ => https://sanzo.top/usr/uploads/img/
'''

path = 'C:/Users/na/xx'
dir = os.listdir(path)

mdfiles = []
for root, dirs, files in os.walk(path, topdown=False):
    for name in files:
        if '.md' in name:
            mdfiles.append(os.path.join(root, name))

for md in mdfiles:
    with open(md, 'r', encoding='utf-8') as f:
        content = f.read()
        content = content.replace('img/', 'https://sanzo.top/usr/uploads/img/')

    with open(md, 'w', encoding='utf-8') as f:
        f.write(content)

    print(md, 'is done!')

# print(mdfiles)
