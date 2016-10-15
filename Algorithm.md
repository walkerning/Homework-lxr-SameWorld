# 以下是算法策略：
当origin只有两个的时候：
随便选取一个origin：
---从该origin开始横平竖直的走（只可走4邻域），递归，选择一个方向（如果发现没有4-邻域点，或者4-邻域点的changed均为true，则return），将该点的changed置为true，并更改该点的color，然后查看目前为止与第二个origin颜色相同的棋子是否只组成一个连通域（4连通），如果不是则继续递归，如果是则
------为所有连通域中的棋子计算属性：num_of_around_pieces，也即他的四邻域中和他同一个颜色的棋子个数。下面从origin2开始走，观察4邻域点中是否有status和它相同的（也即既没有block，颜色也相同，颜色相同的肯定没有change过），如果没有直接return，再观察4邻域中有几个棋子的<该属性>为1，如果>=2个可直接宣布失败，如果=1个，则必往该方向走下一步，否则随便选择一个方向。并将该点的changed置为true，更改该点的color，将他的4邻域点的<该属性>值-1，继续进行。
---------如果以上都失败了，那么
选取另一个origin：（这步可以加一些剪枝，比如如果两个origin是对称的，就可以不用再做这步）
然后重复上面的全部操作

***目前设计的是：找到一条路就退出，这也肯定是最短的一条***

***一些新的想法***
如果两个origin都是黑色，并且最后都是白色，那么可以把路上的棋子分为只走过一次、没走过和走过两次等，然后就可以判断，那些没走过或走过两次的棋子周围如果只有奇数个<只走过一次的棋子>，说明他们没有被经过or他们是某一次笔画的终点

当origin有>=3个的时候：
???

GUI步骤：
常规模式：
自动出现设定好的game，最好鼠标放到球上都会变色，如果企图从非起点出发，则显示“不要调皮啦，必须从起点出发哦”。出发后，每向一个方向走动，都会伸出一条线，需要一直按着鼠标不松手，松手即完成走步。完成走步后，刚才被走过的棋子均反色。两步走完后，如果有颜色不一样的子，则显示“呜哇，失败了”

左上角：重新开始本关
右上角：看解答

自定义模式：
1.height && width，并显示对应多的圆形
2.选取block的方格，click到的该圆形将会消失
3.为剩下的球上色，比如：请选择想填为黑色的球，click到的变为黑色，剩下的自动转为白色（该步骤应该提供撤回一步的选项，很可能选错了一个）
4.请选择起始点（可以限制个数），如果该起始点为被block掉的点不反应
5.检验该设置是否有解（进阶版，如果没解可以给出相应提示，比如更改一下origin的位置就有解了，或者改变一个子的颜色就有解了等等）
6.是否保存此自设关卡？自设关卡将会被单独保留进txt文件，可随时调出查看
下面即转向常规模式进行解密即可


#遇到的有些神奇的bug：
1.一开始qmake编译完使用make怎么都过不了，后来将qmake自动生成的Makefile中的`LFLAGS        = -headerpad_max_install_names -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5`中的10.5改成10.9就解决了，而且网上貌似也有很多人也是用的这种解决方式。。。着实非常神奇。。。
一些解释：-mmacosx-version-min=version
       The earliest version of MacOS X that this executable will run on is
       version.  Typical values of version include 10.1, 10.2, and 10.3.9.

       This value can also be set with the MACOSX_DEPLOYMENT_TARGET environment
       variable.  If both the command-line option is specified and the
       environment variable is set, the command-line option will take precedence.
       参考`http://stackoverflow.com/questions/25352389/difference-between-macosx-deployment-target-and-mmacosx-version-min-compiler-op`

2.rpath问题
问题描述：dyld: Library not loaded: @rpath/./libQtGui.4.dylib
原因：找不到动态链接库（dyld：the dynamic link editor），所以解决这个个问题的方法就是找到这个excutable，也即main所需要的动态链接库。
首先我们要知道他要哪些动态链接库，使用otool -L main来显示，执行命令后的结果如下：
@rpath/./libQtGui.4.dylib (compatibility version 4.8.0, current version 4.8.7)
@rpath/./libQtCore.4.dylib (compatibility version 4.8.0, current version 4.8.7)
/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 120.1.0)
/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1225.1.1)
如上，所以我们需要把libQtGui.4.dylib和libQtCore.4.dylib加到main所在的文件夹中，这两个dylib是在/Users/lu/anaconda/lib下。
下面要把main所在的文件夹的路径加入rpath，就在main.pro中加入:
> QMAKE_LFLAGS += '-Wl,-rpath,@executable_path'
注意：在mac os x下，运行的路径是@executable_path，而在linux下为$ORIGIN
