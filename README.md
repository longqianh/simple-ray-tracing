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







## 测试程序输出

```tex
Optical System Parameters:
Surface Parameters:
1 th surface: radius -- 62.5 , distance to the next surface -- 4 , diffraction index -- 1.5168
2 th surface: radius -- -43.65 , distance to the next surface -- 2.5 , diffraction index -- 1.6727
3 th surface: radius -- -124.35 , distance to the next surface -- 60 , diffraction index -- 1
Effective Focal Length -- 99.7197
Main Surface Distance -- -2.88613
Exit Pupil Distance -- -4.20044

First Paraxial Ray:
Ray Information : FPR,rayout,inf
Aperture Angle U -- 5.745683
Distance l -- 96.83357
Ray Information : FPR,rayout,finite
Aperture Angle U -- 4.614059
Distance l -- 121.596

Second Paraxial Ray:
Ray Information : SPR,rayout,inf 
Aperture Angle U -- -2.959621
Distance l -- -4.200444
Ray Information : SPR,rayout,inf,0.7W 
Aperture Angle U -- -2.072218
Distance l -- -4.200444
Ray Information : SPR,rayout,finite
Aperture Angle U -- -2.936655
Distance l -- -4.200444

First Actual Ray:
Ray Information : FAR,rayout,inf 
Aperture Angle U -- 5.754339
Distance l -- 96.82104
Ray Information : FAR,rayout,inf,0.7U 
Aperture Angle U -- 4.025652
Distance l -- 96.80548
Ray Information : FAR,rayout,finite 
Aperture Angle U -- 4.639631
Distance l -- 121.3194
Ray Information : FAR,rayout,finite,0.7U 
Aperture Angle U -- 3.239016
Distance l -- 121.4342

Second Actual Ray
Ray Information : SAR
Aperture Angle U -- 2.844034
Distance l -- 201.0755
Ray Information : SAR
Aperture Angle U -- -2.960881
Distance l -- -4.197346
Ray Information : SAR
Aperture Angle U -- -8.691386
Distance l -- 62.29972

Ray Information : SAR
Aperture Angle U -- -7.545585
Distance l -- 72.58265
Ray Information : SAR
Aperture Angle U -- -2.937885
Distance l -- -4.197394
Ray Information : SAR
Aperture Angle U -- 1.76631
Distance l -- 326.7311

Exit Ray :
Ideal image height -- inf -- nd -- 5.226088
Ideal image height -- inf -- nd -- 0.7W --  3.656555
Ideal image height -- finite -- nd -- 6.456318
Ideal image height -- finite -- nd -- 0.7W --  4.519422
Actual image height -- inf -- nd -- 5.225639
Actual image height -- inf -- nd -- 0.7W -- 3.656402
Actual image height -- inf -- nf -- 5.225244
Actual image height -- inf -- nf -- 0.7W -- 3.656124
Actual image height -- inf -- nc -- 5.225876
Actual image height -- inf -- nc -- 0.7W -- 3.656568
Actual image height -- finite -- nd -- 6.45581
Actual image height -- finite -- nd -- 0.7W -- 4.519248
Actual image height -- finite -- nf -- 6.455613
Actual image height -- finite -- nf -- 0.7W -- 4.519109
Actual image height -- finite -- nc -- 6.455979
Actual image height -- finite -- nc -- 0.7W -- 4.519367

Aberrations : 
Absolute Distortion -- inf -- -0.0004486989
Relative Distortion -- inf -- -8.585751e-05
Absolute Distortion -- inf -- 0.7W -- -0.0001537026
Relative Distortion -- inf -- -4.203481e-05
Absolute Distortion -- finite -- -0.0005073707
Relative Distortion -- finite -- -7.858514e-05
Absolute Distortion -- finite -- 0.7W -- -0.000174036
Relative Distortion -- finite -- -3.850847e-05
Spheroical Aberration -- inf -- -0.01253009
Spheroical Aberration -- inf -- 0.7U -- -0.02809146
Spheroical Aberration -- finite -- -0.2765279
Spheroical Aberration -- finite -- 0.7U -- -0.1617486
Lateral Chromatic Aberration -- inf -- Aperture 0 -- -0.04096055
Lateral Chromatic Aberration -- inf -- Aperture 0.7 -- 0.01286803
Lateral Chromatic Aberration -- inf -- Aperture 1 -- 0.07395561
Lateral Chromatic Aberration -- finite -- Aperture 0 -- -0.06903013
Lateral Chromatic Aberration -- finite -- Aperture 0.7 -- 0.003522433
Lateral Chromatic Aberration -- finite -- Aperture 1 -- 0.08525612
Longitudinal Chromatic Aberration -- inf -- Aperture 0 -- nan
Longitudinal Chromatic Aberration -- inf -- Aperture 0.7 -- -0.0004433292
Longitudinal Chromatic Aberration -- inf -- Aperture 1 -- -0.0006317205
Longitudinal Chromatic Aberration -- finite -- Aperture 0 -- nan
Longitudinal Chromatic Aberration -- finite -- Aperture 0.7 -- -0.0002580625
Longitudinal Chromatic Aberration -- finite -- Aperture 1 -- -0.0003662791
Coma -- inf -- 0.003210993
Coma -- finite -- 0.04666277
Coma -- inf -- 0.7W -- 0.002170287
Coma -- finite -- 0.7W -- 0.03272396
Coma -- inf -- 0.7U -- 0.002666861
Coma -- finite -- 0.7U -- 0.02143544
Coma -- inf -- 0.7U&0.7W -- 0.001826581
Coma -- finite -- 0.7U&0.7W -- 0.01503701
Field Curvature -- inf -- xt-- -0.4833388 xs-- -0.2273949
Astigmatism -- inf -- -0.2559439
Field Curvature -- finite -- xt-- -0.7486103 xs-- -0.3508126
Astigmatism -- finite -- -0.3977977
[Finished in 0.9s]
```

