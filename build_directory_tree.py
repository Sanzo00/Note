import os
root = os.getcwd()
post_path = root + '\\post'


print('start build directory tree...')


def write_to_sidebar(path, files, prefix):
    '''
    write to path/_sidebar.md
    - [file](prefix/file/)
    '''
    file_path = path + '\\_sidebar.md'  #需要写入的_sidebar.md路径
    local_path = os.path.split(path)[1] # 路径的文件名
    print(file_path)
    with open(file_path, 'w', encoding='utf-8') as f:
        if path != root:
            print('- [Back](README.md)')
            f.write('- [Back](README.md)\n')

        for file in files:
            file = file.split('.md')[0]
            if path == root:
                str = "- [{0}]({1}/{2}/)".format(file, prefix, file)
            else:
                str = "- [{0}]({1}/{2})".format(file, prefix, file)
            print(str)
            f.write(str + '\n')


dirs = os.listdir(post_path)
write_to_sidebar(os.getcwd(), dirs, 'post')


for dir in dirs:
    dir_path = post_path + '\\' + dir # 子目录
    md_files = os.listdir(dir_path)
    mds = []
    for md in md_files:
        if '.md' not in md or '_sidebar.md' in md or 'README.md' in md:
            continue
        mds.append(md)
    write_to_sidebar(dir_path, mds, 'post/' + dir)


print('Done!')
