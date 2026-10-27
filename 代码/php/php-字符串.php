<?php

$a = 'single';    // 单引号：不解析变量，速度快
$b = "double $a"; // 双引号：解析变量

// 常用函数
echo strlen($b);                 // 长度
echo "\n";
echo strtoupper($b);             // 大写
echo "\n";
echo trim("  x  ");              // 去空格
echo "\n";
echo str_replace("a","b",$b);    // 替换
echo "\n";
echo substr("hello",1,3);        // 截取
echo "\n";
echo implode(",", [1,2,3]);      // 数组转字符串
echo "\n";
 explode(",", "a,b,c");          // 字符串转数组
echo "\n";
sprintf("%s-%d", "x", 1);        // 格式化

?>