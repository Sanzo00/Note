# Atom配置

[Atom官网](https://atom.io/)

## 插件

C++插件：

- linter
- linter-gcc
- gcc-make-run



Python插件：

- atom-python-run



其他插件：

- minimap



## 快捷键

markdown实时预览：ctrl + shift + m



自定义快捷键：

可以在`setting`中的`Keybindings`查看当前所有的快捷键。

在`setting`中点击`Open Config Folder`，把自定义快捷键添加到`keymap.cson`中。

```bash
'atom-text-editor':
  'f5': 'Python run: run-f5'

'.platform-win32 atom-workspace, .platform-linux atom-workspace':
  'f6': 'gcc-make-run:compile-run'
```



