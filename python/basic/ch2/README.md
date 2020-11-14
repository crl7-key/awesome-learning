# python的类型与运算-数字


## 目录
* [数字](#数字)
    - [整数](#整数)
    - [整数-二进制，八进制，十六进制](#整数-二进制，八进制，十六进制)
- [浮点数](#浮点数)
* [复数](#复数)
* [其它](#其它)
    - [分数](#分数)
    - [无穷大，无穷小](#无穷大，无穷小)
* [运算符](#运算符)
* [基本数学函数](#基本数学函数)



## 数字
数字类型:
<table class="MsoTableGrid" border="1" cellspacing="0" cellpadding="0" width="709" style="width:531.6pt;margin-left:-42.8pt;border-collapse:collapse;border:none">
 <tbody><tr style="height:3.2pt">
  <td width="95" rowspan="5" valign="top" style="width:70.9pt;border:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">整数</span></p>
  <p class="MsoNormal" align="center" style="text-align:center"><span lang="EN-US">&nbsp;</span></p>
  </td>
  <td width="147" valign="top" style="width:110.15pt;border:solid windowtext 1.0pt;
  border-left:none;padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black;position:relative;top:1.0pt">2.x</span><span style="font-size:20.0pt;font-family:&quot;PMingLiU&quot;,serif;color:black">版本</span></p>
  <p class="MsoNormal" align="center" style="text-align:center;text-indent:10.5pt"><span lang="EN-US">&nbsp;</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border:solid windowtext 1.0pt;
  border-left:none;padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">0</span><span style="font-size:20.0pt;
  color:black">，<span lang="EN-US">-1234</span>，<span lang="EN-US"> 5678</span></span></p>
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">9223372036854775807 9223372036854775808L</span></p>
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">-9223372036854775807</span></p>
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">-9223372036854775808L</span></p>
  </td>
 </tr>
 <tr style="height:3.2pt">
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black;position:relative;top:1.0pt">3.x</span><span style="font-size:20.0pt;font-family:&quot;PMingLiU&quot;,serif;color:black">版本</span></p>
  <p class="MsoNormal" align="center" style="text-align:center"><span lang="EN-US">&nbsp;</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">0</span><span style="font-size:20.0pt;
  color:black">，<span lang="EN-US">-1234</span>，<span lang="EN-US"> 5678
  9223372036854775808</span></span></p>
  </td>
 </tr>
 <tr style="height:3.2pt">
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">十六进制</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">0x9a</span><span style="font-size:20.0pt;
  color:black">，<span lang="EN-US">0XFF</span></span></p>
  </td>
 </tr>
 <tr style="height:3.2pt">
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">八进制</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">0o73</span><span style="font-size:20.0pt;
  color:black">，<span lang="EN-US">0O35</span></span></p>
  </td>
 </tr>
 <tr style="height:3.2pt">
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">二进制</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:3.2pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">0b100100</span><span style="font-size:
  20.0pt;color:black">，<span lang="EN-US">0B101100</span></span></p>
  </td>
 </tr>
 <tr>
  <td width="241" colspan="2" valign="top" style="width:181.05pt;border:solid windowtext 1.0pt;
  border-top:none;padding:0cm 5.4pt 0cm 5.4pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">浮点数</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;color:black">1.23</span><span style="font-size:20.0pt;
  color:black">，<span lang="EN-US">1.</span>，<span lang="EN-US">3.45e-10</span>，<span lang="EN-US">4E100</span></span></p>
  </td>
 </tr>
 <tr>
  <td width="241" colspan="2" valign="top" style="width:181.05pt;border:solid windowtext 1.0pt;
  border-top:none;padding:0cm 5.4pt 0cm 5.4pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">复数</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;font-family:Consolas;color:black">complex(real,imag),
  3+5j</span><span style="font-size:20.0pt;color:black;position:relative;
  top:2.0pt">，</span><span lang="EN-US" style="font-size:20.0pt;font-family:Consolas;
  color:black">4J</span></p>
  </td>
 </tr>
 <tr style="height:36.0pt">
  <td width="95" rowspan="3" valign="top" style="width:70.9pt;border:solid windowtext 1.0pt;
  border-top:none;padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">其他</span></p>
  </td>
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">分数</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;font-family:Consolas;color:black">Fraction(4,5),
  Fraction(7,8)</span></p>
  </td>
 </tr>
 <tr style="height:36.0pt">
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">无穷大</span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;font-family:Consolas;color:black">float('inf'),
  float('-inf')</span></p>
  </td>
 </tr>
 <tr style="height:36.0pt">
  <td width="147" valign="top" style="width:110.15pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span style="font-size:20.0pt;color:black">非数字<span lang="EN-US">NaN</span></span></p>
  </td>
  <td width="467" valign="top" style="width:350.55pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  padding:0cm 5.4pt 0cm 5.4pt;height:36.0pt">
  <p align="center" style="text-align:center;background:white"><span lang="EN-US" style="font-size:20.0pt;font-family:Consolas;color:black">float('nan')</span></p>
  </td>
 </tr>
</tbody></table>




### 整数
在`Python 2.x`版本中整数分为一般整数和长整数
```sh
>>> 2**63 
9223372036854775808L
>>> 2**62-1+2**62 
9223372036854775807
``` 
这个是在`Python 2.7.10`版本的结果。每个版本会有一些不同。 在这个版本中一般整数是`64bit`的(符号位占`1bit`)。当超过`64bit`，会在后面加`L`  
之前的一些版本有可能是`32bit`，这个看具体的版本。 但是在`Python 3.x`就没有这种区分，整数只有一个类型。

#### 整数-二进制，八进制，十六进制
在`Python`里整数可以输入或输出成二进制，八进制或者十六进制数。    
二进制数表示方式为`0b`或者`0B`开头。例如:`0b10110010`，`0B11001001`    
八进制数表述方式为`0o`或者`0O`开头。例如:`0o632765`，`0O223174`   
十六进制数表述方式为`0x`或者`0X`开头。例如:`0xff`，`0X3A`，`0xAC`，`0Xb7` 需要把整数输出成非十进制数的时候，需要使用一下函数:  
`bin(i)`,` oct(i)`,` hex(i) `在这里`i`是十进制数字，输出的是文本形式。  
 我们需要把一个非十进制数的文本转化为整数:
`int(str,base)`在这里，`str`是文本形式的数字，`base`为`2`，`8`，`16` 数字。各自代表 二进制，八进制，十六进制。  
注:`Python`提供从`2`进制到`36`进制数的输入。  


### 浮点数
在`Python`里浮点数是用`64bit`来存储的。精度大约能达到`17`位。 在这里两个版本的显示也是有点区别。
```sh
 Python 2.x版本
>>> print(1.0/6.0) 
0.166666666667
>>> 1.0/6.0 
0.16666666666666666 
>>> repr(1.0/6.0) 
'0.16666666666666666'

python 3.x 版本
>>> print(1.0/6.0)
0.16666666666666666
```
从上面的结果看出默认输出的精度是有区别的。`repr`模式就是交互模式时的显示模式


### 复数
在`Python`里复数的现实方式跟现实稍微有点区别:   
现实:`3+5i` - 在这里`3`是实数部分，`5i`为虚数部分  
`Python`:`3+5j` - 现实里的`i`换成`“j”`或者`“J”`来表示。   
在`Python`里还有一种表示方式是函数格式:`complex(3,5)`
```sh
>>> a=3+5j
>>> b=3+5J
>>> c=complex(3,5) 
>>> a==b
True
>>> c==b
True
>>> c==a
True
```

### 其它
在一些特殊场景，我们会需要特殊的数字类型:
#### 分数
在`Python`里使用`Fraction`函数来表示分数:
```sh
from fractions import *
Fraction(4, 5)
>>> print(Fraction(4,5))
4/5
```

#### 无穷大，无穷小
```sh 
float('inf')是无穷大
float('-inf')是无穷小
 >>> 1/float( inf )
```

### 运算符
- 算数运算符:`+`,`-`,`*`,`/`,`%`,`//`,`**` 
- 比较运算符:`==`,`!=`,`>`,`<`,`>=`,`<=` 
- 赋值运算符:`=`,`+=`,`-=`,`*=`,`/=`,`%=`,`//=`,`**=` 
- 位运算符:`&`,`|`,`^`,`~`,`<<`,`>>` 
- 逻辑运算符:`and`,`or`,`not` 
- 成员运算符:`in`,` not in` 
- 身份运算符:`is`, `is not`

**运算符优先级**:
- `**`
- `~`,`+`,`-` #这里的加和减是一元运算符
- `*`,`/`,`%`,`//`
- `+`,`-`
- `<<`,`>>`
- `&`
- `^`,`|`
- `<=`,`>=`,`<`,`>`
- `==`,`!=`
- `=`,`+=`,`-=`,`*=`,`/=`,`%=`,`//=`,`**=`
- `is`, `is not`
- `in`,` not in`
- `and`, `or`, `not`

### 基本数学函数
- `pow`:幂函数
- `abs`:绝对值 
- `fabs`:绝对值(与`abs`稍微有区别)(`math`) 
- `round`:四舍五入(`2.x`和`3.x`结果略不同) 
- `ceil`，`floor`:取整(`math`)
- `int`,`bin`,`oct`,`hex`,`float`等:格式转换 
- `random`:随机函数(`random`)
- `cmp`:比较函数(`*2.x`)
- `log`:算出自然对数(`math`) 
- `log10`:算出底数为`10`的对数(`math`)
- `max`，`min`:选出最大，最小值
- `modf`:对浮点数分成小数部分和整数部分(`math`) 
- `sqrt`:算出平方根

在使用浮点数的时候，因为计算机里是使用二进制来表示，所以会出现精度问题， 当金融行业等不许出现一丝问题的时候，我们会使用`Decimal`模块来解决精度问题。
```sh
>>> a=2.1
>>> b=4.2
>>> a+b 6.300000000000001 
>>> a=Decimal('2.1') 
>>> b=Decimal('4.2') 
>>> a+b 
Decimal('6.3')
```

**[⬆ 返回顶部](#目录)**