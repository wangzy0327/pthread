# Windows下使用多线程

Windows 开发人员研发出了支持 POSIX 标准的多线程库，起名为 Pthreads-win32。

Visual Studio（简称 VS）是微软发布的一款 IDE，有关 VS 编译器，读者可前往[C语言编译器](http://c.biancheng.net/compiler/)页面进行下载和安装。

VS 默认是不支持使用 Pthreads-win32 库的，接下来我们就以 VS 2017 为例，给大家讲解如何配置 VS 2017 使其能够使用 Pthreads-win32 库。

首先，打开官方提供的 [Pthreads-win32下载页面](http://www.mirrorservice.org/sites/sourceware.org/pub/pthreads-win32/)，下载pthread-win32-xxx-release.zip压缩包，并进行解压。

解压后得到如下三个文件夹：

Pre-built.2 （真正需要的文件）

pthreads.2

QueueUserAPCEx


整个配置 VS2017 的过程中，我们只需要使用 Pre-built.2 文件夹中的资源。配置过程如下：

1) 找到 VS2017 的安装路径（比如笔者电脑上 VS2017 的安装路径为 `E:\VS2017`），将 `Pre-built.2\include`文件夹的所有 .h 文件移动到 `E:\VS2017\VC\Tools\MSVC\14.16.27023\include\`路径下（注意，笔者这里 MSVC 文件夹下保存的是 14.16.27023 文件夹，不同机器上的文件夹名称可能不同）。
2) 将 `Pre-built.2\lib\x86\`文件夹中的所有文件全部移动到 `E:\VS2017\VC\Tools\MSVC\14.16.27023\lib\x86`文件夹中；将 `Pre-built.2\lib\x64\`文件夹中的所有文件全部移动到 `E:\VS2017\VC\Tools\MSVC\14.16.27023\lib\x64`文件夹中。
3) 将 `Pre-built.2\dll\x86\`文件夹中的所有文件移动到 `C:\Windows\SysWOW64\`文件夹中；将 `Pre-built.2\dll\x64\`文件夹中的所有文件移动到 `C:\Windows\System32`文件夹中。

完成以上 3 步操作后，我们就可以在 VS2017 中使用 Pthreads 多线程库了。需要注意的是，程序中引入 <pthread.h> 头文件进行多线程编程时，程序开头还必须添加如下语句：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode" shownum="false"><ul class="snippet-no-num"><li><p><span class="sh_preproc">#pragma</span> <span class="sh_function">comment</span><span class="sh_symbol">(</span>lib<span class="sh_symbol">,</span><span class="sh_string">"pthreadVC2.lib"</span><span class="sh_symbol">)</span></p></li></ul></pre>

由此，VS2017 才能正常地编译程序。

注：编译程序过程中，如果 VS2017 提示 `“timespec”:“struct”类型重定义`错误，解决方案如下：

* 菜单栏中依次选择“项目->属性”；
* 打开的对话框中依次选择“C/C++ -> 预处理器”，然后右侧窗口中点击“预处理器定义”一行的下拉按钮，再点击 `<编译....>`选项；
* 弹出的“预处理定义”窗口中，手动输入 `HAVE_STRUCT_TIMESPEC`然后点击确定；

由此，编译器报 `“timespec”:“struct”类型重定义`错误的问题即可解决。
