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
// a为入瞳直径
// nsf为系统面数
// dists为数组，表示当前面到下个面的距离
// r系统中各面的半径
// ns为系统各面到下一面的折射率
```

方法：





### cal_res

输出结果到 vector 。

数组 *res* 的每一位依次为：

```tex
-- 系统参数 --
系统焦距 f', 像方主面位置 lH', 出瞳距 lp',

-- d光出射光参数 --
理想像距 ld0', 全孔径实际像距 ld', 0.7孔径实际像距 lud', 
全视场理想像高 yd0', 0.7视场理想像高 ywd0', 全视场实际像高 yd', 0.7视场实际像高 ywd',


-- F光出射光参数 --
理想像距 lf0', 全孔径实际像距 lf', 0.7孔径实际像距 luf', 
理想像高 yf0', 全视场实际像高 yf', 0.7视场实际像高 ywf',


-- C光出射光参数 --
理想像距 lc0', 全孔径实际像距 lc', 0.7孔径实际像距 luc', 
理想像高 yc0', 全视场实际像高 yc', 0.7视场实际像高 ywc',


-- 像差 --
全孔径球差 SA, 0.7孔径球差 SAu，
全孔径位置色差 LCAx, 0.7孔径位置色差 LCAxu, 0孔径位置色差 LCAxu0，
全视场倍率色差 LCAy, 0.7视场倍率色差 LCAyw,
初级子午场曲 xt', 初级弧矢场曲 xs', 初级像散 xts', 
全视场绝对畸变 adt, 0.7视场绝对畸变 adtw,
全视场相对畸变 rdt, 0.7视场相对畸变 rdtw,
全市场全孔径、全视场0.7孔径、0.7视场全孔径、0.7视场0.7孔径的子午彗差coma1,coma2,coma3,coma4 

```

