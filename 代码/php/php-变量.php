<?php
$name = "Tom";
$age  = 20;
$pi   = 3.14;
$isOk = true;

echo "$name, $age, $pi, $isOk\n"; // 输出变量

// 可变变量
$$name = "Jerry";  // 相当于 $Tom = "Jerry"

echo "$$name\n"; // 输出变量名为 $name 的变量的值，即输出 $Tom 的值

// 常量
define("SITE", "MySite");
const VERSION = "1.0";
echo SITE;
?>