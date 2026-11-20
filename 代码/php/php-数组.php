<?php

// 一、索引数组（Indexed Array）
// 索引数组：键名是从 0 开始的连续整数，由 PHP 自动分配
$arr = [1, 2, 3];        // 短数组语法，等价于 array(1, 2, 3)
                         // 结果：$arr[0]=1, $arr[1]=2, $arr[2]=3
$a = [1,2,3]; $b = [4,5,6];
$arr[] = 4;
// 追加元素：方括号内不写下标,PHP 自动取"当前最大整数键 + 1"作为新键，
// 即 $arr[3] = 4，结果变为 [1, 2, 3, 4];
//注意：该操作直接修改原数组；
// 若数组为空或没有整数键，则从 0 开始分配

// 二、关联数组（Associative Array）
// 关联数组：键名是自定义的字符串（或整数），形成"键 => 值"的映射
$user = ["name" => "Tom", "age" => 20 , "love" => "PHP"];
// "name" 是字符串键，值为 "Tom"；"age" 键，值为整数 20
// 注意：纯数字字符串键（如 "123"）会被 PHP 自动转成整数键 123

echo $user["name"];// 通过键名取值，输出 Tom
    // 坑：访问不存在的键会触发 Warning 并返回 null
    // 安全写法：$user["name"] ?? "默认值"（PHP 7+）
    // 或先用 isset($user["name"]) 判断是否存在
echo "\n";

// 三、多维数组（Multidimensional Array）
// 数组的元素本身也可以是数组，层层嵌套即形成多维数组
// 这里外层是索引数组，内层是关联数组（很常见的"列表 + 字段"结构）
$list = [
    ["id" => 1, "name" => "A"],   // $list[0] 是一个关联数组
    ["id" => 2, "name" => "B"],   // $list[1] 是一个关联数组
];
echo $list[0]['id'] . "\n";   // 访问：$list[0]["id"] 得到 1
echo $list[0]["name"] . "\n"; // 访问：$list[0]["name"] 得到 "A"
echo $list[1]["id"] . "\n";   // 访问：$list[1]["id"] 得到 2
echo $list[1]["name"] . "\n"; // 访问：$list[1]["name"] 得到 "B"

// 访问：$list[0]["name"] 得到 "A"
// 遍历：foreach ($list as $item) { echo $item["id"], $item["name"]; }

// 四、常用数组函数

count($arr);
// 统计数组元素个数，返回 int
// 例：[1,2,3,4] → 4；空数组 → 0
// 第二个参数可选 COUNT_RECURSIVE（或 1），会递归统计多维数组的所有元素
// 非数组/不可数对象在 PHP 8 会抛 TypeError
// 别名：sizeof()，完全等价
// （此处仅演示，返回值未被使用）
echo "arr的元素个数：" . count($arr) . "\n";

array_push($arr, 5);
// 向数组末尾压入一个或多个元素
// 语法：array_push(数组, 值1, 值2, ...)
// 返回值：压入后数组的新长度（int）
// 注意：该函数直接修改原数组（按引用传参）
// 性能提示：只追加 1 个元素时，用 $arr[] = 5 更快（省去函数调用开销）
echo "array_push后数组长度：" . array_push($arr, 5) . "\n"; // 输出新长度

array_keys($user);
// 返回数组中所有"键名"组成的索引数组
// 例：["name"=>"Tom","age"=>20] → ["name", "age"]
// 扩展用法：array_keys($arr, $搜索值, $strict)
//   → 只返回"值等于搜索值"的那些键；$strict 为 true 时用 === 比较
echo "array_keys返回的键名数组：" . implode(", ", array_keys($user)) . "\n";

array_values($user);
// 返回数组中所有"值"组成的索引数组，键被重置为 0,1,2...
// 例：["name"=>"Tom","age"=>20] → ["Tom", 20]
// 常用于把关联数组"拍平"为普通列表
echo "array_values返回的值数组：" . implode(", ", array_values($user)) . "\n";

in_array(2, $arr);
// 判断某个"值"是否存在于数组中（只比值，不关注键）
// 返回值：bool，存在为 true，不存在为 false
// 第三个参数 $strict：为 true 时用 === 严格比较（类型也必须相同）
// 坑：默认是松散比较，in_array("2", [2]) 会返回 true；
//     in_array(0, ["a"]) 在旧版本也可能误判为 true
// 建议：处理用户输入、类型敏感场景时，务必传 true
echo "in_array(2, \$arr)：" . (in_array(2, $arr) ? "true" : "false") . "\n";

array_merge($a, $b);
// 合并一个或多个数组，返回新数组，不修改原数组
// （$a、$b 为示例变量，需事先定义）
// 合并规则：
//   - 字符串键：后面的覆盖前面的
//   - 数字键：不覆盖，而是重新从 0 开始连续编号后追加
// 若要保持数字键不变，改用 $a + $b（并集运算符，前者优先，且只做一层）
echo "array_merge(\$a, \$b)：" . implode(", ", array_merge($a, $b)) . "\n";

sort($arr);
// 对数组按"值"进行升序排序
// 重要：直接修改原数组（按引用传参），成功返回 true，失败返回 false
// 副作用：会丢弃原来的键，重新从 0 开始建立索引
//         （所以别用 sort 排关联数组，会丢键）
// 第二个参数可选排序标志：SORT_REGULAR（默认）、SORT_NUMERIC、
//   SORT_STRING、SORT_FLAG_CASE 等
// 相关函数：
//   rsort()  按值降序
//   asort()  按值升序，保留键
//   arsort() 按值降序，保留键
//   ksort()  按键升序
//   krsort() 按键降序
//   usort()  用自定义回调函数排序
echo "sort(\$arr)：" . implode(", ", $arr) . "\n";

?>