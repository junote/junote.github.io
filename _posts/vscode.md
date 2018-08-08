

##  Win7 
1. 安装 mingw，添加gcc相关的软件。
2. 在c_cpp_properties.json里修改头文件地址，具体参照vscode的[cpptools](https://github.com/Microsoft/vscode-cpptools/blob/master/Documentation/LanguageServer/MinGW.md)。
3. 使用msys做shell，在配置里设置

```
"terminal.integrated.shell.windows": "F:\\MinGW\\msys\\1.0\\bin\\sh.exe ",
"terminal.integrated.shellArgs.windows": ["--login","-i"]
```




