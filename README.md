# simple-ray-tracing



## 光路追迹程序说明

### OpticalDesign.cpp





### Ray.h

光线类。

包含四种：

- 第一近轴光 FPR 
- 第二近轴光 SPR
- 第一实际光 FPR
- 第二实际光 SPR

#### 基类 Ray

定义了光线最基本的性质 $l$ （物距/像距）和 $U$ （入射/出射孔径角），以及一些备注信息 *rayinfo* 。

声明基本光线 ray 有四种方式：

```c++
Ray ray1;
Ray ray2(l); // l为物距/mm
Ray ray3(rayinfo); // rayinfo 为字符串，可以根据需要传入
Ray ray4(l,rayinfo); // 同时输入物距和光线信息，但必须先输入物距
```

可以通过 *set_* 和 *get_* 方法对光线参数进行设置和取出。

#### 第一近轴光 FPR

First Paraxial Ray 的缩写。

声明时必须提供物距 $l$ , 可选参数为 *rayinfo*。 若物距为无穷远则 $l=-INF$, 其中 INF 设为了 1E15。

特有性质：$U=0$。



#### 第二近轴光 SPR

Second Paraxial Ray 的缩写。



 



### utils.h





### Lens.h

### OptSys.h

光学系统类。

声明：

```c++
Optsys(a,nsf,dists[],rs[],ns[]); 
//a为入瞳直径
// nsf为系统面数
// dists为数组，表示当前面到下个面的距离
// r系统中各面的半径
// ns为系统各面到下一面的折射率
```

方法：

